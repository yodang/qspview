#include<QApplication>
#include "gui.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("QspGui");

    MainFrame frame{};

    frame.show();

    app.exec();

    return 0;
}