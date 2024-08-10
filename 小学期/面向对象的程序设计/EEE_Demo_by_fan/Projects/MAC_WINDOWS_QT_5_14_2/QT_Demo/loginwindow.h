#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "../../../Controlers/Controler_QT/controler_qt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Added constroler reference as parameter by Fan Jingtao
    LoginWindow(Controler_QT& controler, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    //Added constroler reference by Fan Jingtao
    Controler_QT& Controler;
};
#endif // LOGINWINDOW_H
