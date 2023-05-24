#include "empty_class.hpp"
#include <math.h>

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */
//i test vanno costruiti in un progetto a parte che è chiamato raffinamento_test

namespace ShapeLibrary {
//ci deve essere un metodo show


   // area Polygon::Area() = area::0.0;
//poligono con coordinate

Mesh::Mesh(...): {};

matrix Mesh::MatriceAdiacenza(...) {

};


/// aggiunto valori alla matrice di adiacenza
matrix Mesh::AggiornaMatrice(...): {};
/// algoritmo di ricerca di un nodo o di un lato in base al tipo di oggetto passato
int Mesh::Ricerca(...){

};






Vertici::Vertici(int& idNodo, double& x, double& y): {};

//definisco i vari metodi:
///dato un nodo voglio che mi restituisca l'id di un lato
int Vertici::TrovaLati(int& idNodo) {

};

/// dati 3 vertici voglio che li riordini in senso antiorario
//non credo si scriva così
int Vertici::Riordina(vector<int>& nodi ) {

};






Archi::Archi(int& idArco, int& idOrigin, int& idEnd ): {};

//definisco i metodi
///dato un arco trovare gli id dei vertici
vector<int> Archi::TrovaVertici(int& lato){

};




Triangle::Triangle( Eigen::MatrixXd& points):points(points){}

double Triangle::Area()
{
    double area = 0.0;
    //unsigned int righe = points.rows();
    unsigned int colonne  = points.cols();
    for (unsigned int j=0; j< colonne; j++)
    {
        //y del punto
        double y_att = points(1,j);
        //x precedente
        double x_pre = points(0,((j-1+colonne)%(colonne)));
        //x successivo
        double x_succ = points(0,((j+1+colonne)%(colonne)));
        area += y_att*(x_pre-x_succ);
    };
    area = 0.5*area;

    //uso la formula di Gauss: semi somma delle coordinate y*(xprecedente -x successivo in senso antiorario)

    return abs(area);
}

vector<int> Triangle::Dimezza(){


};
bool Triangle::Verifica(){

};


}




