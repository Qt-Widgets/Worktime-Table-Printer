#ifndef PRZELICZWALUTE_H
#define PRZELICZWALUTE_H

#include <QDialog>
#include "czas.h"

namespace Ui {
class PrzeliczWalute;
}

class PrzeliczWalute : public QDialog
{
    Q_OBJECT

public:
    explicit PrzeliczWalute(QWidget *parent = 0);
    ~PrzeliczWalute();
    void PrzekazIloscGodzin(Czas godzinyTotal);
    Czas godzinyPracyCalkowite;
    float stawkaGodzinowa = 6.2;

private slots:
    void on_pushButton_clicked();


private:
    Ui::PrzeliczWalute *ui;
};

#endif // PRZELICZWALUTE_H
