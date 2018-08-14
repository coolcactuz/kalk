//
// Created by luca on 10/01/18.
//

#include "Induttore.h"

Induttore::Induttore(double i):Componente(),induttanza(i){
  Componente::setImp(impedenza());
}

Induttore::Induttore(std::string s):Componente(){
  auto pos=s.find('L');
  if(pos==0){
    induttanza=std::stod(s.substr(1));
    Componente::setImp(impedenza());
  }
  else
    throw(0); //gestire eccezione errore di sintassi
}

Induttore::Induttore():Componente(),induttanza(0){}

Induttore::~Induttore(){}

C_cartesiano Induttore::impedenza() const{
    double xl=2*Numero::pi*Circuito::freq*induttanza;
    return C_cartesiano(0,xl);
}
