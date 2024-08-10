#include <QMessageBox>
#include "adminwindow.h"
#include "ui_adminwindow.h"

//Added constroler reference as parameter by Fan Jingtao
AdminWindow::AdminWindow(Controler_QT& controler,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow),
    Controler(controler)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_btnAdd_clicked()
{
    ControlerRet Res = Controler.CreateNewUser(ui->edtUsername->text().toStdString(),
                                       ui->edtPassword->text().toStdString());
    ui->edtUsername->clear();
    ui->edtPassword->clear();
    QMessageBox::information(NULL, "Error", ResStr[static_cast<int>(Res)].c_str(), QMessageBox::Ok);

}
