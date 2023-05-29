#include "empty_class.hpp"
#include <math.h>

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */
//i test vanno costruiti in un progetto a parte che è chiamato raffinamento_test

using namespace std;

namespace ShapeLibrary {

//il costruttore di triangoli prende in input le info del file e le salva, in più deriva le coordinate dai vertici
Triangle::Triangle(unsigned int& id, array<unsigned int, 3>& vertices, array<unsigned int, 3>& edges, TriangularMesh& mesh):
    id(id),
    vertices(vertices),
    edges(edges),
    mesh(mesh){

    //associo i vertici alle coordinate: prima riga le x, seconda riga le y
    Eigen::MatrixXd coordinates = Eigen::MatrixXd::Zero(2,3);
    for (unsigned int i=0; i<3;i++){
        unsigned int j = vertices[i];
        float coordx =mesh.Cell0DCoordinates[j][0];
        float coordy =mesh.Cell0DCoordinates[j][1];
        coordinates(0,i) = coordx;
        coordinates(1,i) = coordy;
        }
    coordinate = coordinates;

}

//definisco il metodo per il calcolo delle aree
double Triangle::Area()
{
    //devo tenere conto che la matrice con le coordinate è già salvata, quindi posso farne accesso anche senza chiamarla esplicitamente

    double area = 0.0;
    //unsigned int righe = points.rows();
    unsigned int colonne  = coordinate.cols();
    for (unsigned int j=0; j< colonne; j++)
    {
        //y del punto
        double y_att = coordinate(1,j);
        //x precedente
        double x_pre = coordinate(0,((j-1+colonne)%(colonne)));
        //x successivo
        double x_succ = coordinate(0,((j+1+colonne)%(colonne)));
        area += y_att*(x_pre-x_succ);
    };
    area = 0.5*area;

    //uso la formula di Gauss: semi somma delle coordinate y*(xprecedente -x successivo in senso antiorario)
    return abs(area);
}


int Triangle::Vicini(ShapeLibrary::Triangle& triangolo2)
{
    //partendo dal presupposto che due triangolo possono avere al massimo un lato in comune:
    //controllo se il triangolo1 e il 2 sono adiacenti verificando se hanno un lato in comune

    //OSSERVAZIONE: anche se non dovrebbe mai capitare, secondo me sarebbe opportuno verificare che non vengano avanzate proposte di confronto fra due triangoli uguali
    //dovremmo quindi controllare che l'id del triangolo che stiamo valutando sia diverso dall'id del traingolo2
    for(unsigned int i=0; i<3; i++)
    {
        int vertice1= edges[i];

        for (unsigned int j=0;j<3;j++)
        {
            int vertice2= triangolo2.edges[j];
            if (vertice2==vertice1)
                return vertice2;
        }
    }
    //ritorno un valore a caso che non sia il nome di uno degli archi
    return -4;
}



/*vector<int> Triangle::Raffina(){


};

*/


//gli passo una lista di oggetti della classe triangolo e ne deriva la matrice di adiacenza
Mesh::Mesh(vector<ShapeLibrary::Triangle>& lista): lista(lista){

    //calcolo la matrice di adiacenza
    unsigned int numTri = lista.size();

    Eigen::SparseMatrix<double> adj(numTri,numTri);

    //cerco le adiacenze frai vari triangoli
    for (unsigned int i= 0; i< numTri-1; i++)
    {
        //seleziono un triangolo
        for (unsigned int j = i+1; j<numTri;j++)
        {
            //cerco tutti i triangoli che confinano
            int link = lista[i].Vicini(lista[j]);
            if (link >=0)
            {
                //cout<<link<<endl;
                adj.insert(lista[i].id, lista[j].id) = link;
                adj.insert(lista[j].id, lista[i].id) = link;
            }
        }
    }
    adiacenza = adj;

}




}




