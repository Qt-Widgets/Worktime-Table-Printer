#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "czas.h"
#include <QFile>

#include "tableprinter.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPainter>
#include <QTextDocument>
#include <iostream>

using namespace std;

class QPrinter;
class QSqlTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ustawWielkoscTablicy(int iloscDni);
    void ustawDniTygodnia (QString pierwszyDzien, int iloscDni);
    void ustawMiesiacIRok(QString miesiac, QString rok);
    Czas zczytajCzasZTablicy(int wiersz, int kolumna);
    bool sprawdzFormatGodziny (string text);

    void obliczSume (int wiersz);

    void OknoZapisz();
    void Zapisz();
    void ProcesZapisu(std::fstream &plik);

    void OknoWczytaj();
    void Wczytaj();
    void ProcesWczytywaniaStandard (std::fstream &plik);
    void ProcesWczytywania (QFile plik);
    QString OdczytajNastepnyWyraz(QString odczytanyWiersz, int &iteratorZnakow);
    void DopasujWielkoscTablicy(int iloscWierszy);

    const char* QStringToChar(QString value);

    void oblGodzinyLacznie();

    void eksportujTabliceDoPDF();

private slots:
    void on_pushButton_clicked();

    void on_przelicz_walute_button_clicked();

    void on_Sumuj_Godziny_Button_clicked();

    void on_actionZamknij_triggered();

    void on_actionWczytaj_triggered();

    void on_actionZapisz_2_triggered();

    void on_exoprtButton_clicked();

private:
    Ui::MainWindow *ui;
    QString sciezkaZapisanegoPliku;
    QString sciezkaWczytanegoPliku;

    QString miesiac;
    QString rok;

    const int kolumnaPracaR = 1;
    const int kolumnaPracaZ = 2;
    const int kolumnaSniadanieR = 3;
    const int kolumnaSniadanieZ = 4;
    const int kolumnaObiadR = 5;
    const int kolumnaObiadZ = 6;
    const int kolumnaSuma = 7;

    const char nowyWiersz = '\n';
    const char nowaKolumna = ' ';
    const char pustePole  = '*';
};

#endif // MAINWINDOW_H
