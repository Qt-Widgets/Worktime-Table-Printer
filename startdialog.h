#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QApplication>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);

    ~StartDialog();

    int getIloscDniMiesiaca() const;

    QString getPierwszyDzienMiesiaca() const;

private slots:
    void on_utworz_Button_clicked();

    void on_utworzProjekt_Button_clicked();

    void on_rozpocznij_Button_clicked();

    void on_pushButton_2_clicked();

    void on_wczytaj_pushButton_clicked();

private:
    Ui::StartDialog *ui;    
    int iloscDniMiesiaca;
    QString pierwszyDzienMiesiaca;    
    QString nazwaMiesiaca;
    QString rok;

public:
    bool wczytajNaStart = false;
    QString getNazwaMiesiaca() const;
    void setNazwaMiesiaca(const QString &value);
    QString getRok() const;
    void setRok(const QString &value);
};

#endif // STARTDIALOG_H
