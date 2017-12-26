//
// Created by luca on 07/12/17.
//

#ifndef KALK_RAZ_H
#define KALK_RAZ_H

#include "Numero.h"

class Raz : public Numero {
private:
    long num;
    long den;
public:
    Raz (int);
    Raz (long, long);
    Raz (double);

    explicit operator double () const;
    Raz *operator+ (const Numero &) const;
    Raz *operator- (const Numero &) const;
    Raz *operator* (const Numero &) const;
    Raz *operator/ (const Numero &) const;
    Raz *operator^ (int) const;

    long getNum () const { return num; }
    long getDen () const { return den; }
    int getMCD (long, long) const;
    Raz *reciproco () const;
    void semplifica ();
    long double radice_quadrata () const;
    long double radice_cubica () const;
};

std::ostream &operator<< (std::ostream &, const Raz &);

#endif //KALK_RAZ_H
