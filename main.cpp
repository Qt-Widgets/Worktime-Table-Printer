#include "mainwindow.h"
#include <QApplication>
#include "startdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    StartDialog startDialog;

    if(startDialog.exec() == QDialog::Accepted)
    {
        if(startDialog.wczytajNaStart)
        {
            mw.show();
            mw.OknoWczytaj();
            mw.Wczytaj();
        }
        else
        {
            mw.show();
            mw.ustawWielkoscTablicy(startDialog.getIloscDniMiesiaca());
            mw.ustawDniTygodnia(startDialog.getPierwszyDzienMiesiaca(), startDialog.getIloscDniMiesiaca());
            mw.ustawMiesiacIRok(startDialog.getNazwaMiesiaca(),startDialog.getRok());
        }
    }

    return a.exec();
}


