#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "../../../Controlers/Controler_QT/controler_qt.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    //Added constroler reference as parameter by Fan Jingtao
    explicit AdminWindow(Controler_QT& controler, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_btnAdd_clicked();

private:
    Ui::AdminWindow *ui;
    //constroler reference
    Controler_QT& Controler;
};

#endif // ADMINWINDOW_H
