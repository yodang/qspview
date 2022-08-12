#include "gui.hpp"
#include<QTextEdit>
#include<QDockWidget>
#include<QStringListModel>
#include<QMenuBar>
#include<QFileDialog>

#include<fstream>
#include<algorithm>
#include<iostream>

MainFrame::MainFrame(QWidget* parent)
:QMainWindow(parent)
{
    auto menu=new QMenuBar(this);
    auto list=new QListView(this);
    auto text=new QTextEdit(this);
    auto dock=new QDockWidget(this);
    auto file=new QMenu(this);
    auto model=new QStringListModel();
    list->setModel(model);

    auto open=file->addAction("Open");
    auto searchAct=file->addAction("Search");
    file->setTitle("File");
    menu->addMenu(file);
    connect(open, &QAction::triggered, this, [=](bool c){
        auto path=QFileDialog::getOpenFileName().toStdString();
        std::ifstream in{path};
        std::vector<std::vector<char>> strings{};
        while(!in.eof())
        {
            auto string=readNextQSPString(in);
            strings.push_back(string);
        }
        game=buildGame(strings);
        QStringList locs{};
        for(const auto& loc: game.locs)
        {
            locs.push_back(QString::fromStdString(loc.name));
        }
        model->setStringList(locs);
    });

    connect(list->selectionModel(), &QItemSelectionModel::currentChanged, this, [=](auto current, auto prev){
        std::cout<<"triggered"<<"\n";
        if(current.data().canConvert(QVariant::String))
        {
            auto name=current.data().toString().toStdString();
            std::cout<<"convertible "<<name<<"\n";
            for(const auto& loc: game.locs)
            {
                if( std::equal(loc.name.begin(), loc.name.end(), name.begin(), name.end()) )
                {
                    std::cout<<"equal"<<"\n";
                    text->setText(QString::fromStdString(loc.lines));
                }
            }
        }
    });

    dock->setWidget(list);

    setMenuBar(menu);
    setCentralWidget(text);
    //list->model().
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,dock);

    searchDial=new SearchDialog(this);
    connect(searchAct, &QAction::triggered, this, [=](bool c){searchDial->show();});
    connect(searchDial, &SearchDialog::next_search, this, &MainFrame::search);
    locsList=list;
    textArea=text;
}

QModelIndex findIndexInModel(QAbstractItemModel* model, const QString& str)
{
    auto rows=model->rowCount();
    for(int i=0; i<rows; i++)
    {
        auto index=model->index(i, 0);
        if(model->data(index).toString()==str)
            return index;
    }
    std::cout<<"shouldn't happen\n";
    return model->index(-1,-1);
}

void MainFrame::search(QString str)
{
    auto selectedLoc=locsList->currentIndex().data().toString();//FIXME might throw or crash
    auto cursor=textArea->textCursor().position();

    auto pos=std::find_if(game.locs.begin(), game.locs.end(),[&selectedLoc](auto e){
        return std::equal(selectedLoc.begin(), selectedLoc.end(), e.name.begin(), e.name.end());
    });
    do{
        auto cur=pos->lines.find(str.toStdString(), cursor);
        std::cout<<"Looking in "<<pos->name<<"\n";
        if(cur!=std::string::npos)
        {
            std::cout<<"found at "<<pos->name<<" index "<<cur<<"\n";
            auto index=findIndexInModel(locsList->model(), QString::fromStdString(pos->name));
            //locsList->selectionModel()->select(index,QItemSelectionModel::SelectionFlag::SelectCurrent);
            locsList->selectionModel()->setCurrentIndex(index,QItemSelectionModel::SelectionFlag::SelectCurrent);
            auto newCursor=textArea->textCursor();
            newCursor.setPosition(cur);
            newCursor.movePosition(QTextCursor::MoveOperation::Right, QTextCursor::KeepAnchor, str.length());
            textArea->setTextCursor(newCursor);
            break;
        }
        cursor=0;
    }while(++pos!=game.locs.end());
}
