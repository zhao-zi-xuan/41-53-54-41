#include "loginwindow.h"
#include <QApplication>
#include "../../../Controlers/Controler_QT/controler_qt.h"

int main(int argc, char *argv[])
{
    qputenv("QT_MAC_WANTS_LAYER", "1");
    QApplication a(argc, argv);

    //Create controler by Fan Jingtao
    //NEED EDIT FILE NAMES, IN YOUR OWN COMPUTER
    Controler_QT Controler(
         "/Users/jingtaofan/Desktop/2021OOP/DEMO/EEE_Demo_by_fan/Users.txt",
         "/Users/jingtaofan/Desktop/2021OOP/DEMO/EEE_Demo_by_fan/Messages.txt");

    //Added constroler reference as parameter by Fan Jingtao
    LoginWindow w(Controler);

    w.show();
    return a.exec();
}
