#include"parser.h"
#include"Componente.h"
#include<string>

int main(){
  std::string input;
  std::cin>>input;
  parser<Componente> a(input);
  a.load_operators();
    std::cout<<"harambese"<<std::endl;
//  std::cout<<*(parser<Componente>::resolve(a.build_tree(input)))<<std::endl;
  a.build_tree(input);
  //
  // Complesso* a=new C_cartesiano(9,0);
  // Complesso* b=new C_polare(6,45);
  // Complesso* c=dynamic_cast<Complesso*>(a->operator/(b));
  // std::cout<<*(c->converti())<<std::endl;
  // //Complesso* c=new C_cartesiano(1,1);
  // std::cout<<*c<<std::endl;
  // //Complesso* e=dynamic_cast<Complesso*>((b->operator+(a))->operator-(c));
  std::cout<<"harambee"<<std::endl;


  return 0;
}
