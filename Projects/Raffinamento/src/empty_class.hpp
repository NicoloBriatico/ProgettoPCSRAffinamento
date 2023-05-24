#ifndef __EMPTY_H
#define __EMPTY_H
//dobbiamo sicuramente cambiare nome alla classe

#include <iostream>
#include "Eigen/Eigen"

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */

// Un'idea potrebbe essere:
/*definire una classe triangolo che ha diversi metodi:
 * 1. calcolo aree;
 * 2. buona positura;
 * 3. bisezione;
 *
 * oss: per il calcolo delle aree dovremmo sfruttare le informazioni tratte dal file, conoscendo sia i lati che i punti, forse conviene calcolare l'area come un poligono e quindi implementare solo quel metodo
 * oss: nell'ottica della lezione del 19/05 potremmo anche pensare di definire 3 classi al posto di 3 metodi, ma va capito anche se ne vale effettivamente la pena
 */


using namespace std;

namespace ShapeLibrary {

//forse bisogna usare i templete o qualcosa del genere per associare a nodo un insieme di archi di cui a priori non conosco la dimensione
class Mesh {
    //qui raccolgo un riassunto sulle informazioni di nodi e di archi
private:
    //nodo
    //archi
    (...);
public:
    //costruttore di default
    Mesh() = default;
    //costruttore che mi definisce le cose se gli passo i valori giusti, mi servirebbe creare una sorta di matrice (come ho fatto nella struct e forse conviene copiare quella) nella quale mettere i dati
    //potrei ad esempio utilizzare l'id come riga della matrice, in modo da salvare i dati in un array di vector di 2 dimensioni, quindi ogni volta che chiamo il costruttore passandogli questi 3 valori
    //deve aggiungere un elemento nella matrice dinamica...cerca di prendere spunto dalla struct
    Mesh(...);

    //definisco i metodi:
    ///calcolo matrice di adiacenza
    matrix MatriceAdiacenza(...);
    /// aggiunto valori alla matrice di adiacenza
    matrix AggiornaMatrice(...);
    /// algoritmo di ricerca di un nodo o di un lato in base al tipo di oggetto passato
    int Ricerca(...);

};


class Vertici : public Mesh
{
    //li uso per leggere il file Cell1D
private:
    //mi salvo l'id del nodo
    int idNodo;
    //mi salvo le coordinate x e y
    double x;
    double y;

public:
    //chiamo il costruttore di default
    Vertici() = default;
    //se a vertici passo le informazioni ci costruisco un oggetto
    Vertici(int& idNodo, double& x, double& y);

    //definisco i vari metodi:
    ///dato un nodo voglio che mi restituisca l'id di un lato
    int TrovaLati(int& idNodo);

    /// dati 3 vertici voglio che li riordini in senso antiorario
    //non credo si scriva così
    int Riordina(vector<int>& nodi );

};


class Archi : public Mesh
{
    //li uso per leggere il file Cell2D
private:
    int idArco;
    int idOrigin;
    int idEnd;

public:
    //inizializzo un costruttore di default
    Archi()=default;
    //date le tre informazioni definisco un arco
    Archi(int& idArco, int& idOrigin, int& idEnd );

    //definisco i metodi
    ///dato un arco trovare gli id dei vertici
    vector<int> TrovaVertici(int& lato);

};


  //oss: io gestirei alcuni casi particolari tipo triangolo degenere (eg una linea) che poi testiamo e altre cose patologiche, posto che vogliamo essere in grado di gestirli
  class Triangle    //cercare come si definisce una classe amica, posto che serva definirla come tale!!!
  {
      //gli passo le coordinate dalla mesh, implemento il metodo area come poligono
    private:
      Eigen::MatrixXd points;
      ///se fosse un triangolo a se, 3 vertici basterebbero, ma essendo parte di una mesh mi serve anche segnare chi sono i lati
      Eigen::MatrixXd lati;

    public:

      Triangle() = default;
      Triangle(Eigen::MatrixXd& points, Eigen::MatrixXd& lati);

      //definisco i metodi
      double Area();
      vector<int> Dimezza();
      bool Verifica();
      //string Show() {}

  };


}













/*
#ifndef __SHAPE_H
#define __SHAPE_H











}
#endif // __SHAPE_H

*/
#endif // __EMPTY_H
