//
// Created by luca on 18/12/17.
//

#ifndef KALK_C_POLARE_H
#define KALK_C_POLARE_H

#include "Complesso.h"

class C_cartesiano;

class C_polare: public Complesso {
private:
    double modulo;
    double fase;

public:
    C_polare(double =0, double =0);
    C_polare(const C_polare&);
    ~C_polare();

    C_polare* operator+ (const Numero*)const;
    C_polare* operator- (const Numero*)const;
    C_polare* operator* (const Numero*)const;
    C_polare* operator/ (const Numero*)const;

    Complesso* converti() const;
    C_polare* coniugato() const;
    double getModulo() const;
    double getFase() const;
    void stampa(std::ostream&)const ;
};

std::ostream& operator<<(std::ostream&, const C_polare&);

#endif //KALK_C_POLARE_H