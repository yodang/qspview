#ifndef QSP_GUI_H
#define QSP_GUI_H
#include<QMainWindow>
#include<QHBoxLayout>
#include<QListView>
#include<QTextEdit>
#include<memory>

#include "qsp.hpp"
#include "searchdialog.hpp"

class MainFrame: public QMainWindow{
Q_OBJECT
public:
    MainFrame(QWidget* parent=nullptr);
private:
    QSPGame game{};
    SearchDialog* searchDial;
    QListView* locsList;
    QTextEdit* textArea;

private slots:
    void search(QString str);
};

#endif