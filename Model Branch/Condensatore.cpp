//
// Created by luca on 11/01/18.
//

#include "Condensatore.h"

Condensatore::Condensatore(double c):Componente(),capacita(c){
  Componente::setImp(impedenza());
}
Condensatore::Condensatore(std::string s):Componente(){
  auto pos=s.find('C');
  if(pos==0){
    capacita=std::stod(s.substr(1));
    Componente::setImp(impedenza());
  }
  else
    throw(0); //gestire eccezione errore di sintassi
}

Condensatore::Condensatore():Componente(),capacita(0){};

bool Condensatore::operator== (const Dato& d) const{
    try {
        auto aux = dynamic_cast<const Condensatore &>(d);
        return capacita == aux.capacita;
    }
    catch(const std::bad_cast& error) {
        return false;
    }
}

Condensatore& Condensatore::operator= (const Dato& d){
    try{
        auto aux= dynamic_cast<const Condensatore&>(d);
        capacita = aux.capacita;
        setImp(capacita);
        return *this;
    }
    catch(const std::bad_cast& error){
        std::cout<<"tipi incompatibili"<<std::endl;
    }
}

C_cartesiano Condensatore::impedenza() const{
    double xc=1/(2*(Numero::pi)*(Componente::freq)*capacita);
    return C_cartesiano(0,-xc);
}
