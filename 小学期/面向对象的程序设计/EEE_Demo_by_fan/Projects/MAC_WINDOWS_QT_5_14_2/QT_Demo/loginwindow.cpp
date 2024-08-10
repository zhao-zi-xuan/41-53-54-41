#include <QMessageBox>
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "adminwindow.h"
#include "userwindow.h"

//Added constroler reference as parameter by Fan Jingtao
LoginWindow::LoginWindow(Controler_QT& controler, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::LoginWindow),
      Controler(controler)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_pushButton_clicked()
{
    ControlerRet Res = Controler.Login(ui->edtUsername->text().toStdString(),
                                       ui->edtPassword->text().toStdString());
    if(Res == RES::ADMIN_LOGINED) {
        //new Administrator's GUI
        shared_ptr<AdminWindow> Ptr(new AdminWindow(Controler));
        Ptr->exec();
    }
    else if (Res == RES::USER_LOGINED){
        //new Administrator's GUI
        shared_ptr<UserWindow> Ptr(new UserWindow(Controler));
        Ptr->exec();
    }
    else {
        QMessageBox::critical(NULL, "Error", ResStr[static_cast<int>(Res)].c_str(), QMessageBox::Ok);
    }

}
