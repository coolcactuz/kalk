// classe concreta Condensatore, derivata da Componente


// TO DO:
//   GESTIONE ECCEZIONI -> segnalate nell'implementazione dei vari metodi


//SCELTE PROGETTUALI:
// 1) override dei metodi toString(), equals(), assign(), impedenza()
// 3) "traduzione" in linguaggio Java delle ulteriori funzionalita' offerte dalla corrispettiva classe C++
//    a)costruttore da double
//    b)costruttore da stringa
//    c)costruttore di default

class Condensatore extends Componente{

  private double capacita;

  public Condensatore(double d){
    capacita = d;
    super.setImp(impedenza());
  }

  public Condensatore(){
    capacita = 0;
  }

  public Condensatore(String s){
    if(s.charAt(0) == 'C'){
      capacita = Double.parseDouble(s.substring(1));
      super.setImp(impedenza());
    }
    else{
      System.out.println("errore di sintassi nella costruzione di Condensatore")
      //-------------------
      //GESTIRE ECCEZIONE
      //-------------------
    }
  }

  public CCartesiano impedenza(){
    double aux = 1 / (2 * (Numero.pi) * (Componente.freq) * capacita);
    CCartesiano result = new CCartesiano(0, -aux);
    return result;
  }

  public void assign(Dato d){
    if(!(d instanceof Condensatore)){
      System.out.println("Condensatore.assign()-> d non e' instanza di Condensatore")
      //-------------------
      //GESTIRE ECCEZIONE
      //-------------------
    }

    Condensatore aux = (Condensatore) d;

    super.assign(aux);

    capacita = aux.capacita;
  }

  public boolean equals(Object obj){
    if(!(obj instanceof Condensatore)){
      System.out.println("Condensatore.equals()-> obj non e' instanza di Condensatore")
      //-------------------
      //GESTIRE ECCEZIONE
      //-------------------
    }

    Condensatore aux = (Condensatore) obj;

    if(super.equals(aux)){
      if(capacita == aux.capacita){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }

  public String toString(){
    String result = super.toString();
    result = result + "CAPACITA': " + capacita + ";\r\n";
    return result;
  }
}
