#ifndef CZAS_H
#define CZAS_H

#include <QString>

class Czas
{
public:
    Czas ();
    Czas(int godzina, int minuta);
    QString ToString();

    static Czas FromString(QString odczyt);
    static float doDziesietnych (Czas czas);

    int getGodzina() const;
    QString getGodzinaString() const;
    void setGodzina(int value);

    int getMinuta() const;
    QString getMinutaString() const;
    void setMinuta(int value);

    friend Czas& operator + (Czas &czas1, Czas &czas2);
    friend Czas& operator - (Czas &czas1, Czas &czas2);

private:
    int godzina;
    int minuta;
};

#endif // CZAS_H
