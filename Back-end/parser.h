#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>

class Dato;

class parser{
private:

  class node{

  private:

    static node* copy(node*);   //copia in modo profondo una struttura di node
    static void destroy(node*); //libera

  public:

    bool is_Operator;
    char op;
    Dato* object;
    node* left;
    node* right;

    //di default inserisco il dato vuoto in un node singolo
    node(bool isop = false, char o = '\0', Dato* obj = 0, node* l = 0,
    node* r = 0): is_Operator(isop), op(o), object(obj), left(l), right(r) {}

    //node ha un campo puntatore, regola dei tre
    //distruttore
    ~node();

    //assegnazione
    node& operator=(const node&);

    //costruttore di copia
    node(const node&);
  };

  template <class T>
  bool find(T item, std::list<T> l){
    bool res = false;
    for(typename std::list<T>::const_iterator it = l.begin(); it != l.end(); it++){
      if(*it == item)
        res = true;
    }
    return res;
  }

  static node* find_father(node*, node*);
  static Dato* indentify_literal(std::string::const_iterator,
    std::string::const_iterator);


  static std::list <const Dato* (*) (std::string)>  p_list;
  static std::list <const char> operator_list;


public:

  static void add_operator(const char&);
  static void add_parser_pointer(const Dato* (*) (std::string) &);

  node* parse(std::string) const;
};

#endif
