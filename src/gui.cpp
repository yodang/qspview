#include "gui.hpp"
#include<QTextBrowser>
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
    auto text=new QTextBrowser(this);
    auto dock=new QDockWidget(this);
    auto file=new QMenu(this);
    auto model=new QStringListModel();
    list->setModel(model);

    auto open=file->addAction("Open");
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
}