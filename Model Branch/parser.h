
#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include <iostream>

#include "Numerical_Hierarchy.h"
#include "Circuit_Hierarchy.h"
#include "Database_Hierarchy.h"

template<class T>
class parser{
public:
  class node{
  public:
    T* obj;
    char op;
    double prec;
    node* left, *right;
    node(T* t=nullptr, char o='\0', int p=0, node* l=nullptr, node* r=nullptr):
      obj(t), op(o), prec(p), left(l), right(r){};
    ~node(){delete left; delete right; delete obj;};

    bool operator==(node& n){
      return *obj==*(n.obj) && op==n.op && left==n.left && right==n.right;
    }
    bool operator!=(node& n){
      return !(*this == n);
    }

    static node* copy(node* p=nullptr){
      if(!p) return 0;
         return new node(p->obj,p->op, p->prec, copy(p->left), copy(p->right));
    };
  };
  parser(std::string ="");
  ~parser();

  parser<T> operator=(const parser<T>&);
  bool operator==(const parser<T>&);
  bool operator!=(const parser<T>&);

  node* build_tree(std::string ="\0")const ;
  static Dato* resolve(node*);
  void print(node* =nullptr, int =0) const ;
  node* getStart() const ;
  Hierarchy_Handler* getHandler() const;
  bool compara_alberi(typename parser<T>::node*, typename parser<T>::node*);

private:
  std::string input;
  node* start;
  Hierarchy_Handler* handler;

  Hierarchy_Handler* check_handler(T*);

protected:
  double set_prec(char) const;
  bool balanced_brackets(std::string ="\0") const;
  static node* find_father(node* =nullptr, node* =nullptr) ;
  static void balance_tree(node* =0);
  static Dato* create(std::string);
};

//
//PARSER
//
//costruttore da stringa, default=nullo
template<class T>
parser<T>::parser(std::string s): input(s), start(){
  handler=parser<T>::check_handler(start->obj);
  start=build_tree(input);
}

//distruttore
template<class T>
parser<T>::~parser(){
  delete start;
  delete handler;
}

template<class T>
Hierarchy_Handler* parser<T>::check_handler(T* object){
  if(dynamic_cast<Complesso*>(object))
    return new Numerical_Hierarchy();
  if(dynamic_cast<Raz*>(object))
    return new Numerical_Hierarchy();
  if(dynamic_cast<Componente*>(object))
    return new Circuit_Hierarchy();
  if(dynamic_cast<tupla*>(object))
    return new Database_Hierarchy();

  throw(0); //gestire eccezione tipo non riconosciuto
}

//controllo parentesi bilanciate
template<class T>
bool parser<T>::balanced_brackets(std::string s) const{
  int bracket=0;
  for(auto it=s.begin(); it!=s.end(); ++it){
    if(*it=='(')  bracket++;
    else if (*it==')') bracket--;
    if(bracket<0) return false;
  }
  if(bracket==0) return true;
  return false;
}

//trova nodo padre del nodo wanted, nell'albero (o sub albero) root
template<class T>
typename parser<T>::node* parser<T>::find_father(typename parser<T>::node* wanted,typename parser<T>::node* root) {
  if(!root || !wanted || wanted==root) return nullptr; //l'albero e il nodo figlio devono essere != null
  if((root->left && root->left == wanted) || (root->right && root->right == wanted)) return root;
  node* sub_left=find_father(wanted, root->left);
  if(sub_left) return sub_left;
  node* sub_right=find_father(wanted, root->right);
  if(sub_right) return sub_right;
  return nullptr;
}

//costruzione albero di parsing
template<class T>
typename parser<T>::node* parser<T>::build_tree(std::string s) const {
  if(!balanced_brackets(s)) throw(0); //gestire eccezione parentesi non bilanciate
  if(s.length()==0) throw(0); //gestire eccezione stringa vuota
  std::string tmp= "(";
  tmp=tmp.append(s);
  tmp=tmp.append(")");
  auto it=tmp.begin();
  node* start = nullptr;
  node* current = start;

  while(it!=tmp.end()){
    if(!(handler->is_operator(*it))){
      auto aux = it;
      while(!(handler->is_operator(*aux)) && aux!=tmp.end())
        aux++;
      std::string spoil_item(it,aux);
      T* obj_p=dynamic_cast<T*>(create(spoil_item));
      if(!obj_p)
        std::cout << "identify_literal ERROR";
      current->right=new node();
      current=current->right;
      current->op = 0;
      current->prec = set_prec(*it);
      current->obj = obj_p;
      it = aux;
    }
    else{
      switch (*it) {
        case '(': {
          node* item=new node();
          item->op=*it;
          item->prec = set_prec(*it);
          if(!start && !current){
            start=item;
            current=item;
          }
          else{
            current->right=item;
            current=current->right;
          }
        }
        break;

        case ')':{
          while(current->prec != set_prec(*it))
            current=find_father(current, start);
          node*father=find_father(current,start);
          node* aux=current;
          if(father){
            father->right=current->right;
            current=father;
          }
          else{
            current=current->right;
            start=current;
          }
          aux->right=nullptr;
          delete aux;
        }
        break;

        default:{
          node* item=new node();
          item->op=*it;
          item->prec=set_prec(*it);
          while(current->prec >= item->prec)
            current=find_father(current,start);
          item->left=current->right;
          current->right=item;
          current=item;
        }
        break;
      }
      it++;
    }
  }
  balance_tree(start);
  return start;
}

template<class T>
double parser<T>::set_prec(char c) const{
  switch(c){
    case '(':
    case ')':
      return 1;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
      return 4;
    case '^':
    case '#':
      return 6;
    default:
      return 7;
  }
}

template<class T>
bool parser<T>::compara_alberi(parser<T>::node * root, parser<T>::node * aux) {
  if(root->operator==(*aux))
    return compara_alberi(root->left, aux->left) && compara_alberi(root->right, aux->right);
  return false;
}

template <class T>
typename parser<T>::node* parser<T>::getStart() const {
  return start;
}

template <class T>
Hierarchy_Handler* parser<T>::getHandler() const{
  return handler;
}

template<class T>
parser<T> parser<T>::operator=(const parser<T>& p){
  if(*start!=*(p.start)){
    delete start;
    start=parser<T>::node::copy(p.start);
  }
  if(!(*handler==*(p.handler))){
    delete handler;
    handler=p.handler;
  }
  input=p.input;
  return *this;
}

template<class T>
bool parser<T>::operator==(const parser<T>& p){
  return input==p.input && compara_alberi(start,p.start);
}

template<class T>
bool parser<T>::operator!=(const parser<T>& p){
  return !(*this==p);
}

template<class T>
void parser<T>::print(node* n, int z) const{
  if(!n) return;
  if(!n->left && !n->right)
    std::cout<<*(n->obj)<<std::endl;
  else{
    if(n->left){
      std::cout<<"<"<<std::endl;
      print(n->left);
    }
    std::cout<<n->op<<std::endl;
    if(n->right){
      std::cout<<">"<<std::endl;
      print(n->right);
    }
  }
}


template<class T>
void parser<T>::balance_tree(typename parser<T>::node* root){
  if(!root || (!root->left && !root->right)) return;
  balance_tree(root->left);
  if(!root->left && root->right) root->left=new node(new T(),'0');
  balance_tree(root->right);
}

template <class T>
Dato* parser<T>::create(std::string s){
  T* aux;
  if(dynamic_cast<Complesso*>(aux))
    return Numerical_Hierarchy::create_complex(s);
  else if(dynamic_cast<Raz*>(aux))
    return Numerical_Hierarchy::create_rational(s);
  else if(dynamic_cast<Componente*>(aux))
    return Circuit_Hierarchy::create(s);
  else if(dynamic_cast<tupla*>(aux))
    return Database_Hierarchy::create(s);
  else
    throw(0); //gestire eccezione tipo non riconosciuto
}

template<class T>
Dato* parser<T>::resolve(typename parser<T>::node* n){
  if(!n) return 0;
  if(n->op == 0)
    return n->obj;
  return T::solve_operation(resolve(n->left), resolve(n->right), n->op);
}

#endif
