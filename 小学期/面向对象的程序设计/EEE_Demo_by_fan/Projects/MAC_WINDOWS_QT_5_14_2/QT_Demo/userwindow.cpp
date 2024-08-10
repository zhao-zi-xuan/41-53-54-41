#include <QMessageBox>
#include "userwindow.h"
#include "ui_userwindow.h"

//Added constroler reference as parameter by Fan Jingtao
UserWindow::UserWindow(Controler_QT& controler,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserWindows),
    Controler(controler)
{
    ui->setupUi(this);
    //From Min Datetime
    ui->dtFrom->date().setDate(1752, 12, 31);
    ui->dtFrom->time().setHMS(0, 0, 0);
    //To now
    ui->dtTo->setDateTime(QDateTime::currentDateTime());

    //submit now
    ui->dtSumbit ->setDateTime(QDateTime::currentDateTime());
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_btnSearch_clicked()
{
    SearchRes SRes;
    ControlerRet Res = Controler.SearchMessageBetween(
                ui->dtFrom->date().year(),
                ui->dtFrom->date().month(),
                ui->dtFrom->date().day(),
                ui->dtFrom->time().hour(),
                ui->dtFrom->time().minute(),
                ui->dtFrom->time().second(),
                ui->dtTo->date().year(),
                ui->dtTo->date().month(),
                ui->dtTo->date().day(),
                ui->dtTo->time().hour(),
                ui->dtTo->time().minute(),
                ui->dtTo->time().second(),
                SRes
                );
    if (Res == RES::SEARCH_OK) {
        //clear message list
        ui->lstMessages->clear();
        //insert new ones
        auto Insertor = [&](const string& MessageStr){ui->lstMessages->addItem(QString::fromStdString(MessageStr));};
        for_each(SRes.Messages.begin(), SRes.Messages.end(), Insertor);
        //display count
        ui->nbWords->display(QString::number(SRes.CountOfWords));
        ui->nbActions->display(QString::number(SRes.CountOfActions));
        ui->nbThoughts->display(QString::number(SRes.CountOfThoughts));
    }

}

void UserWindow::on_btnSumit_clicked()
{
    ControlerRet Res = Controler.SumbitMessage(
                ui->dtSumbit->date().year(),
                ui->dtSumbit->date().month(),
                ui->dtSumbit->date().day(),
                ui->dtSumbit->time().hour(),
                ui->dtSumbit->time().minute(),
                ui->dtSumbit->time().second(),
                ui->edtTitle->text().toStdString(),
                ui->edtContent->text().toStdString(),
                ui->cbTypes->currentText().toStdString()
                ) ;
    if (Res == RES::MESSAGE_SUBMIT_OK) {
        //update datetime to now
        ui->dtSumbit ->setDateTime(QDateTime::currentDateTime());
        //clear display
        ui->edtTitle->clear();
        ui->edtContent->clear();
        //reset type
        ui->cbTypes->setCurrentIndex(0);
    }
    QMessageBox::information(NULL, "Error", ResStr[static_cast<int>(Res)].c_str(), QMessageBox::Ok);
}
