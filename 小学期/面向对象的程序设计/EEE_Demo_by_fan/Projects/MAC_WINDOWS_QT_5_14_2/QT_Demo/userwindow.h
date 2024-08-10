#ifndef USERWINDOWS_H
#define USERWINDOWS_H

#include <QDialog>
#include "../../../Controlers/Controler_QT/controler_qt.h"

namespace Ui {
class UserWindows;
}

class UserWindow : public QDialog
{
    Q_OBJECT

public:
    //Added constroler reference as parameter by Fan Jingtao
    explicit UserWindow(Controler_QT& controler, QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_btnSearch_clicked();
    void on_btnSumit_clicked();

private:
    Ui::UserWindows *ui;
    //constroler reference
    Controler_QT& Controler;
};

#endif // USERWINDOWS_H
