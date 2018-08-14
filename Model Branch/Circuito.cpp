//
// Created by luca on 14/01/18.
//

#include "Circuito.h"

double Circuito::freq=0;
double Circuito::volt=0;

Circuito::Circuito(std::string s){
  circuit=new parser<Componente>(s);
}

Circuito::~Circuito () {
  delete circuit.getStart();
}

C_cartesiano Circuito::impEquivalente () const {
    return dynamic_cast<Componente*>(parser<Componente>::resolve(circuit.getStart()))->impedenza();
}

C_cartesiano Circuito::Corrente_totale() const{
    if(volt != 0){
        C_cartesiano v=C_cartesiano(volt);
        C_cartesiano impEq=impEquivalente();
        return *((&impEq)->operator/(&v));
    }
    return 0;
}

void Circuito::setVolt(double v){
  if(v>=0)
    volt=v;
  else
    throw(0); //gestire eccezione invalid value
}
void Circuito::setFreq(double f){
  if(f>=0)
    freq=f;
  else
    throw(0); //gestire eccezione invalid value
}
