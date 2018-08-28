//
// Created by luca on 03/01/18.
//

#include "Componente.h"

double Componente::freq=0;
double Componente::volt=0;

Componente::Componente(C_cartesiano c): imp(c){}

Componente::Componente(std::string s){
    auto pos=s.find('Z');
    if(pos == 0)
        setImp(std::stod(s.substr(1)));
    else{
        std::cout << "errore di sintassi nella costruzione di Componente" << std::endl;
        //------------------
        //GESTIRE ECCEZIONE
        //------------------
    }
}

Componente::Componente(): imp(0){}

Componente* Componente::operator+ (const Componente* c) const{
    C_cartesiano c1=impedenza();
    C_cartesiano c2=c->impedenza();
    /*
    C_cartesiano* result = (&c1)->operator+(&c2);
    Componente* aux = new Componente(*result);
    delete result;
    return aux;
    */
    return new Componente(*((&c1)->operator+(&c2)));
}

Componente* Componente::operator/ (const Componente* c) const {
    C_cartesiano c1=impedenza();
    C_cartesiano c2=c->impedenza();
    return new Componente(*(((&c1)->operator*(&c2))->operator/((&c1)->operator+(&c2))));
}

bool Componente::operator== (const Dato& d) const{
   try{
       auto aux= dynamic_cast<const Componente&>(d);
       return imp==aux.imp;
   }
   catch(const std::bad_cast& error){
       return false;
   }
}

Componente& Componente::operator= (const Dato& d){
    try{
        auto aux= dynamic_cast<const Componente&>(d);
        setImp(aux.impedenza());
        return *this;
    }
    catch (const std::bad_cast &error){
        std::cout << "tipi incompatibili" << std::endl;
    }
}

Componente* Componente::solve_operation(const Dato* a, const Dato* b, char o){
    auto l=dynamic_cast<const Componente*>(a);
    auto r=dynamic_cast<const Componente*>(b);
    if(l && r){
        switch(o) {

            case '+':
              return l->operator+(r);
            break;

            case '/':
              return l->operator/(r);
            break;

            default:
              std::cout << "Componente::solve_operation->operatore errato" << std::endl;
              //------------------
              //GESTIRE ECCEZIONE
              //------------------
            break;

        }
    }
}

C_cartesiano Componente::impedenza() const{
  return imp;
}

double Componente::getVolt(){
    return volt;
}

double Componente::getFreq(){
    return freq;
}

void Componente::setImp(const C_cartesiano& c ){
  imp=c;
}

void Componente::setVolt(double v){
    if(v>=0)
        volt=v;
    else{
      std::cout << "volt negativi" << std::endl;
      //------------------
      //GESTIRE ECCEZIONE
      //------------------
    }
}

void Componente::setFreq(double f){
    if(f>=0)
        freq=f;
    else{
      std::cout << "frequenza negativa" << std::endl;
      //------------------
      //GESTIRE ECCEZIONE
      //------------------
    }
}
