#ifndef SEARCHDIALOG_HPP
#define SEARCHDIALOG_HPP

#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QLayout>

class SearchDialog: public QDialog
{
Q_OBJECT
public:
    SearchDialog(QWidget* parent=nullptr)
    :QDialog(parent)
    {
        auto line=new QLineEdit(this);
        auto next=new QPushButton(this);
        next->setText("Find Next");

        connect(next, &QPushButton::clicked, this, [=](bool checked){emit next_search(line->text());});

        auto content=new QHBoxLayout(this);

        content->addWidget(line);
        content->addWidget(next);

        setLayout(content);
    }
signals:
    void next_search(QString str);
};

#endif