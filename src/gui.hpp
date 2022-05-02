#ifndef QSP_GUI_H
#define QSP_GUI_H
#include<QMainWindow>
#include<QHBoxLayout>
#include<QListView>
#include<memory>

#include "qsp.hpp"

class MainFrame: public QMainWindow{
Q_OBJECT
public:
    MainFrame(QWidget* parent=nullptr);
private:
    QSPGame game{};
};

#endif