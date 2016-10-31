#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "przeliczwalute.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <string>
#include <QTextStream>
#include <QFile>
#include<QPrintDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Licznik Godzin Pracy");
    QTableWidget*  timeTable = ui->tablicaGodzin;

    QFont czcionkaMiesiacaIRoku ("Arial", 15, QFont::Bold);
    ui->miesiacLabel->setFont(czcionkaMiesiacaIRoku);
    ui->rokLabel->setFont(czcionkaMiesiacaIRoku);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ustawWielkoscTablicy(int iloscDni)
{
    ui->tablicaGodzin->setRowCount(iloscDni);
}

void MainWindow::on_przelicz_walute_button_clicked()
{
    PrzeliczWalute noweOkno (this);
    noweOkno.PrzekazIloscGodzin(Czas::FromString(ui->GodzinaTotal->text()));
    noweOkno.exec();
}

void MainWindow::ustawDniTygodnia(QString pierwszyDzien, int iloscDni)
{
    int kolumnaDni = 0;

    int iterator;

    if(pierwszyDzien == "Poniedziałek")
    {
        iterator = 1;
    }
    else if(pierwszyDzien == "Wtorek")
    {
        iterator = 2;
    }
    else if(pierwszyDzien == "Środa")
    {
        iterator = 3;
    }
    else if(pierwszyDzien == "Czwartek")
    {
        iterator = 4;
    }
    else if(pierwszyDzien == "Piątek")
    {
        iterator = 5;
    }
    else if(pierwszyDzien == "Sobota")
    {
        iterator = 6;
    }
    else if(pierwszyDzien == "Niedziela")
    {
        iterator = 7;
    }

    int iloscWykonanychDni = 0;

    for(iloscWykonanychDni; iloscWykonanychDni < iloscDni; iloscWykonanychDni++)
    {
        QTableWidget* tablica = ui->tablicaGodzin;

        if(iterator == 1)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Poniedziałek"));
        }
        else if (iterator == 2)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Wtorek"));
        }
        else if (iterator == 3)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Środa"));
        }
        else if (iterator == 4)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Czwartek"));
        }
        else if (iterator == 5)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Piątek"));
        }
        else if (iterator == 6)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Sobota"));
        }
        else if (iterator == 7)
        {
            tablica->setItem(iloscWykonanychDni, kolumnaDni, new QTableWidgetItem("Niedziela"));
        }

        ++iterator;

        if(iterator > 7)
        {
            iterator = 1;
        }
    }
}

void MainWindow::ustawMiesiacIRok(QString miesiac, QString rok)
{
    this->miesiac = miesiac;
    this->rok = rok;

    ui->miesiacLabel->setText(this->miesiac);
    ui->rokLabel->setText(this->rok);
}

Czas MainWindow::zczytajCzasZTablicy(int wiersz, int kolumna)
{
    if(ui->tablicaGodzin->item(wiersz, kolumna) && !ui->tablicaGodzin->item(wiersz, kolumna)->text().isEmpty() && (sprawdzFormatGodziny(ui->tablicaGodzin->item(wiersz, kolumna)->text().toStdString())))
    {
        return Czas::FromString(ui->tablicaGodzin->item(wiersz, kolumna)->text());
    }
    else
    {
        Czas temp (0,0);
        return temp;
    }
}

bool MainWindow::sprawdzFormatGodziny (string text)
{
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] < 48 || text[i] > 58)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::obliczSume(int wiersz)
{
    Czas pracaR = zczytajCzasZTablicy(wiersz, kolumnaPracaR);
    Czas pracaZ = zczytajCzasZTablicy(wiersz, kolumnaPracaZ);
    Czas sniadanieR = zczytajCzasZTablicy(wiersz, kolumnaSniadanieR);
    Czas sniadanieZ = zczytajCzasZTablicy(wiersz, kolumnaSniadanieZ);
    Czas obiadR = zczytajCzasZTablicy(wiersz, kolumnaObiadR);
    Czas obiadZ = zczytajCzasZTablicy(wiersz, kolumnaObiadZ);

    Czas czasPracy = pracaZ - pracaR;
    Czas czasSniadania = sniadanieZ - sniadanieR;
    Czas czasObiadu = obiadZ - obiadR;

    Czas przerwy = czasSniadania + czasObiadu;

    Czas wynik = czasPracy - przerwy;

    //Czas wynik = czasPracy - (czasSniadania + czasObiadu);

    ui->tablicaGodzin->setItem(wiersz, kolumnaSuma, new QTableWidgetItem (wynik.ToString()));
}

void MainWindow::OknoZapisz()
{
    QString filtr = "Pliki txt (*.txt)";

    sciezkaZapisanegoPliku = QFileDialog::getSaveFileName(
                                this,
                                tr("Zapisz plik"),
                                "C://",
                                filtr,
                                &filtr);
}

void MainWindow::Zapisz()
{
    fstream plik;
    plik.open(QStringToChar(sciezkaZapisanegoPliku), ios::out);
    ProcesZapisu(plik);
    plik.close();
}

void MainWindow::ProcesZapisu(fstream& plik)
{
           //zapisanie rozmiaru tablicy. Najpierw wiersze, potem kolumny
   plik << ui->tablicaGodzin->rowCount()
        << nowaKolumna
        << ui->tablicaGodzin->columnCount()
        << nowaKolumna
        << miesiac.toStdString()
        << nowaKolumna
        << rok.toStdString()
        << nowyWiersz;

   for(int i = 0; i < ui->tablicaGodzin->rowCount(); i++)
   {
       for(int j = 0; j < ui->tablicaGodzin->columnCount(); j++)
       {
           if(ui->tablicaGodzin->item(i,j) && !ui->tablicaGodzin->item(i,j)->text().isEmpty())
           {
               plik << QStringToChar(ui->tablicaGodzin->item(i,j)->text());
           }
           else
           {
               plik << pustePole;
           }
           plik << nowaKolumna;
       }
       plik << nowyWiersz;
   }
}

void MainWindow::OknoWczytaj()
{
    sciezkaWczytanegoPliku = QFileDialog::getOpenFileName(
                this,
                tr("Otwórz plik"),
                "C://",
                "Pliki txt (*.txt)");
    //QMessageBox::information(this, tr("Nazwa pliku"), filename);
    //on_Sumuj_Godziny_Button_clicked();
}

void MainWindow::Wczytaj()
{
    QFile plik (sciezkaWczytanegoPliku);
    plik.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream wczytywanie (&plik);
    wczytywanie.setCodec("UTF-8");

    int iteratorZnakow = 0;

    //Wczytywanie ilosci wierszy
    QString wczytanyWiersz = wczytywanie.readLine();
    int iloscWierszy = OdczytajNastepnyWyraz(wczytanyWiersz, iteratorZnakow).toInt();
    DopasujWielkoscTablicy(iloscWierszy);

    int iloscKolumn = OdczytajNastepnyWyraz(wczytanyWiersz, iteratorZnakow).toInt();

    miesiac = OdczytajNastepnyWyraz(wczytanyWiersz, iteratorZnakow);

    rok = OdczytajNastepnyWyraz(wczytanyWiersz, iteratorZnakow);

    ui->miesiacLabel->setText(miesiac);
    ui->rokLabel->setText(rok);


    QString obecnyWiersz;
    iteratorZnakow = 0;
    QString odczytywanyWyraz;
    bool wyrazOdczytany = false;

    for(int i = 0; i < iloscWierszy; i++)
    {
    obecnyWiersz = wczytywanie.readLine();

        for(int j = 0; j < 8; j++)
        {
            while(!wyrazOdczytany)
            {
                if(obecnyWiersz[iteratorZnakow] != nowaKolumna)
                {
                    odczytywanyWyraz.append(obecnyWiersz[iteratorZnakow]);
                }

                if(obecnyWiersz[iteratorZnakow] == nowaKolumna)
                {
                    wyrazOdczytany = true;
                }

                else if(obecnyWiersz.isEmpty())
                {
                    break;
                }
                ++iteratorZnakow;
            }
            if(odczytywanyWyraz[0] != pustePole)
            {
                ui->tablicaGodzin->setItem(i, j, new QTableWidgetItem (odczytywanyWyraz));
            }
            else
            {
                ui->tablicaGodzin->setItem(i, j, new QTableWidgetItem (""));
            }

            wyrazOdczytany = false;
            odczytywanyWyraz.clear();
        }
        iteratorZnakow = 0;
        if(obecnyWiersz.isEmpty())
        {
            break;
        }
    }

    wyrazOdczytany = false;

    odczytywanyWyraz.clear();

    plik.close();
}

void MainWindow::ProcesWczytywaniaStandard (fstream &plik)
{
    QString ObecnyZnak;
    QString tempWyraz;
    string ObecnyWiersz;
    bool pelnyWyraz = false;
    int licznikZnakow = 0;
    const char* nowaKolumnaWsk = &nowaKolumna;
    const char* nowyWierszWsk = &nowyWiersz;

    for(int i = 0 ; i < ui->tablicaGodzin->rowCount() ; i++)
    {
        getline(plik, ObecnyWiersz);
        for(int j = 0 ; j < ui->tablicaGodzin->columnCount() ; j++)
        {
            while(!pelnyWyraz)
            {
                ObecnyZnak = ObecnyWiersz[licznikZnakow];

                tempWyraz.append(ObecnyZnak);

                if(ObecnyZnak == nowaKolumnaWsk || ObecnyZnak == nowyWierszWsk)
                {
                    pelnyWyraz = true;
                }
                ++licznikZnakow;
            }
        }
    }
    ui->tablicaGodzin->setItem(1,1,new QTableWidgetItem (QString::fromStdString(ObecnyWiersz)));
}

QString MainWindow::OdczytajNastepnyWyraz(QString odczytanyWiersz, int &iteratorZnakow)
{
    QString odczytywanyWyraz;
    bool wyrazOdczytany = false;

    while(!wyrazOdczytany)
    {
        odczytywanyWyraz.append(odczytanyWiersz[iteratorZnakow]);

        if(odczytanyWiersz[iteratorZnakow] == nowaKolumna)
        {
            wyrazOdczytany = true;
        }
        else if(odczytanyWiersz[iteratorZnakow] == nowyWiersz || odczytanyWiersz[iteratorZnakow] == '\000')
        {
            break;
        }
        ++iteratorZnakow;
    }
    return odczytywanyWyraz;
}

void MainWindow::DopasujWielkoscTablicy(int iloscWierszy)
{
    int duplikatWierszy = ui->tablicaGodzin->rowCount();
    if(iloscWierszy < ui->tablicaGodzin->rowCount())
    {
        for(int i = 0; i < duplikatWierszy - iloscWierszy; i++)
        {
            ui->tablicaGodzin->removeRow(1);
        }
    }

    else if(iloscWierszy > ui->tablicaGodzin->rowCount())
    {
        for(int i = 0; i <  iloscWierszy - duplikatWierszy; i++)
        {
            ui->tablicaGodzin->insertRow(ui->tablicaGodzin->rowCount());
        }
    }
}

const char *MainWindow::QStringToChar(QString value)
{
    QByteArray ba = value.toUtf8();
    const char *nowyChar = ba.data();
    return nowyChar;
}

void MainWindow::oblGodzinyLacznie()
{
    Czas suma(0, 0);
    int nrKolumny = 7;

    for(int i = 0; i < ui->tablicaGodzin->rowCount(); i++)
    {
        Czas temp = zczytajCzasZTablicy(i, nrKolumny);
        suma = suma + temp;
    }
    ui->GodzinaTotal->setText(suma.ToString());
}

void MainWindow::eksportujTabliceDoPDF()
{
    /*QTextDocument doc;
    QString text = "druga kolumna";
    doc.setHtml(ui->tablicaGodzin->item(0,0)->text() + " " + ui->tablicaGodzin->item(0,1)->text());

     QPrinter printer(QPrinter::HighResolution);
     printer.setOutputFileName("../out.pdf");
     printer.setOutputFormat(QPrinter::PdfFormat);
     doc.print(&printer);
     printer.newPage();*/

    QString strStream;
    QTextStream out(&strStream);

    QString strTitle = "Godziny pracy - " + ui->miesiacLabel->text() + " - " + ui->rokLabel->text();

    const int rowCount = ui->tablicaGodzin->rowCount();
    const int columnCount = ui->tablicaGodzin->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg(strTitle)
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        <<  QString("<font size=25 padding=30>%1</font>").arg(strTitle)
        <<  "<table width=100% border=1 cellspacing=0 cellpadding=4>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tablicaGodzin->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tablicaGodzin->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tablicaGodzin->isColumnHidden(column)) {
                QString data = ui->tablicaGodzin->model()->data(ui->tablicaGodzin->model()->index(row, column)).toString().simplified();
                out << QString("<td align=center height=150 bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        << QString ("<font size=5 align=right>Godziny w sumie %1</p>").arg(ui->GodzinaTotal->text())
        << "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QString filtr = "Pliki PDF (*.pdf)";

    QString sciezkaPliku = QFileDialog::getSaveFileName(
                                this,
                                tr("Wyeksportuj do PDF"),
                                "C://",
                                filtr,
                                &filtr);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName(sciezkaPliku);
    printer.setOutputFormat(QPrinter::PdfFormat);
    document->print(&printer);

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void MainWindow::on_Sumuj_Godziny_Button_clicked()
{
    for(int i = 0; i < ui->tablicaGodzin->rowCount(); i++)
    {
        obliczSume(i);
    }
    oblGodzinyLacznie();
}

void MainWindow::on_actionZamknij_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionWczytaj_triggered()
{
    OknoWczytaj();
    if(!sciezkaWczytanegoPliku.isEmpty())
    {
        Wczytaj();
    }
    else
    {
       QMessageBox::warning(this, tr("Wczytywanie pliku"),"Nie udało się wczytać pliku.");
    }
}

void MainWindow::on_actionZapisz_2_triggered()
{
    OknoZapisz();
    if(!sciezkaZapisanegoPliku.isEmpty())
    {
        Zapisz();
    }
    else
    {
        QMessageBox::warning(this, tr("Zapisywanie pliku"),"Nie udało się zapisać pliku.");
    }
}

void MainWindow::on_exoprtButton_clicked()
{
    eksportujTabliceDoPDF();
}
