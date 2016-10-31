#include "czas.h"

Czas::Czas()
{
}

Czas::Czas(int godzina, int minuta)
{
    this->godzina = godzina;
    this->minuta = minuta;
}

Czas& operator+ (Czas &czas1, Czas &czas2)
{
    Czas temp;
    temp.setMinuta(czas1.getMinuta() + czas2.getMinuta());
    temp.setGodzina(czas1.getGodzina() + czas2.getGodzina());

    if(temp.getMinuta() >= 60)
    {
        temp.setGodzina(temp.getGodzina() + 1);
        temp.setMinuta(temp.getMinuta() - 60);
    }

    if(temp.getGodzina() < 0)
    {
        temp.setGodzina(0);
        temp.setMinuta(0);
    }

    return temp;
}

Czas& operator- (Czas &czas1, Czas &czas2)
{
    Czas temp;
    temp.setMinuta(czas1.getMinuta() - czas2.getMinuta());
    temp.setGodzina(czas1.getGodzina() - czas2.getGodzina());


    if(temp.getMinuta() < 0)
    {
        temp.setGodzina(temp.getGodzina() - 1);
        temp.setMinuta(60 - (czas2.getMinuta() - czas1.getMinuta()));
    }

    if(temp.getGodzina() < 0)
    {
        temp.setGodzina(0);
        temp.setMinuta(0);
    }

    return temp;
}

QString Czas::ToString()
{
    QString temp;

    return temp = this->getGodzinaString() + ":" + this->getMinutaString();
}

Czas Czas::FromString(QString odczyt)
{
    if(!odczyt.isEmpty())
    {
        QString godzina;
        QString obecnyZnak = "x";
        QString minuta;

        int iterator = 0;
        while (obecnyZnak != ":" && iterator < odczyt.length())
        {
            obecnyZnak = odczyt [iterator];

            if(obecnyZnak != ":")
            {
                godzina += obecnyZnak;
            }

            ++iterator;
        }

        while (iterator < odczyt.length())
        {
            obecnyZnak = odczyt [iterator];

            minuta += obecnyZnak;

            ++iterator;
        }

        Czas temp (godzina.toInt(), minuta.toInt());

        return temp;
    }
    else
    {
        Czas temp (0, 0);
        return temp;
    }
}

float Czas::doDziesietnych(Czas czas)
{
    int calosci = czas.getGodzina();
    float ulamek = czas.getMinuta() / 60.0;

    float temp = (float) calosci + ulamek;

    return temp;
}

int Czas::getGodzina() const
{
    return godzina;
}

QString Czas::getGodzinaString() const
{
    return QString::number(godzina);
}

void Czas::setGodzina(int value)
{
    godzina = value;
}
int Czas::getMinuta() const
{
    return minuta;
}

QString Czas::getMinutaString() const
{
    QString temp = QString::number(minuta);

    if(minuta < 10)
    {
        temp = "0" + temp;
    }

    return temp;
}

void Czas::setMinuta(int value)
{
    minuta = value;
}

