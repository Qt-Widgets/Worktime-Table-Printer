#include "startdialog.h"
#include "ui_startdialog.h"
#include "mainwindow.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

    setWindowTitle("Start");
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::on_utworzProjekt_Button_clicked()
{
    ui->IloscDni_label->setEnabled(true);
    ui->IloscDni_lineEdit->setEnabled(true);
    ui->pierwszyDzien__label->setEnabled(true);
    ui->pierwszyDzien_comboBox->setEnabled(true);
    ui->rozpocznij_Button->setEnabled(true);

    ui->rokLabel->setEnabled(true);
    ui->rokLineEdit->setEnabled(true);

    ui->miesiacLabel->setEnabled(true);
    ui->miesiacLineEdit->setEnabled(true);

    ui->utworzProjekt_Button->setEnabled(false);
}

void StartDialog::on_rozpocznij_Button_clicked()
{
    iloscDniMiesiaca = ui->IloscDni_lineEdit->text().toInt();
    pierwszyDzienMiesiaca = ui->pierwszyDzien_comboBox->currentText();
    rok = ui->rokLineEdit->text();
    nazwaMiesiaca = ui->miesiacLineEdit->text();
    QDialog::accept();
}
QString StartDialog::getPierwszyDzienMiesiaca() const
{
    return pierwszyDzienMiesiaca;
}

int StartDialog::getIloscDniMiesiaca() const
{
    return iloscDniMiesiaca;
}


void StartDialog::on_wczytaj_pushButton_clicked()
{
    wczytajNaStart = true;
    QDialog::accept();
}
QString StartDialog::getRok() const
{
    return rok;
}

void StartDialog::setRok(const QString &value)
{
    rok = value;
}

QString StartDialog::getNazwaMiesiaca() const
{
    return nazwaMiesiaca;
}

void StartDialog::setNazwaMiesiaca(const QString &value)
{
    nazwaMiesiaca = value;
}

