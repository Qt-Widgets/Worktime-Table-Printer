#include "przeliczwalute.h"
#include "ui_przeliczwalute.h"

PrzeliczWalute::PrzeliczWalute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrzeliczWalute)
{
    ui->setupUi(this);

    setWindowTitle("Przelicznik");
}

PrzeliczWalute::~PrzeliczWalute()
{
    delete ui;
}

void PrzeliczWalute::PrzekazIloscGodzin(Czas godzinyTotal)
{
    godzinyPracyCalkowite = godzinyTotal;
    ui->label_Godziny->text() = godzinyTotal.ToString();
}

void PrzeliczWalute::on_pushButton_clicked()
{
    float kursEuro = ui->Euro_lineEdit->text().toFloat();
    float wynik = kursEuro * stawkaGodzinowa * Czas::doDziesietnych(godzinyPracyCalkowite);
    ui->label_Kwota->text() = wynik;
}
