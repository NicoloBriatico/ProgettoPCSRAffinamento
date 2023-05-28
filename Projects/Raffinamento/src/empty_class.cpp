#include "empty_class.hpp"
#include <math.h>

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */
//i test vanno costruiti in un progetto a parte che è chiamato raffinamento_test

using namespace std;

namespace ShapeLibrary {


Triangle::Triangle(unsigned int& id, array<unsigned int, 3>& vertices, array<unsigned int, 3>& edges, TriangularMesh& mesh):
    id(id),
    vertices(vertices),
    edges(edges),
    mesh(mesh){
    //mi salvo subito le coordinate associate al triangolo
    Eigen::MatrixXd coordinates = Eigen::MatrixXd::Zero(2,3);
    for (unsigned int i=0; i<3;i++){
        unsigned int j = vertices[i];
        //rispetto alla matrice coordinate nella prima riga inserisco le coordinate X, nella seconda le coordinate Y
        float coordx =mesh.Cell0DCoordinates[j][0];
        float coordy =mesh.Cell0DCoordinates[j][1];
        coordinates(0,i) = coordx;
        coordinates(1,i) = coordy;
        //cout<<vertici[i]<<"\t"<<coordx<<"\t"<<coordy<<endl;
        }
    coordinate = coordinates;
    //cout<<coordinate<<endl;
    //return coordinate;
}

double Triangle::Area()
{
    //Eigen::MatrixXd coordinate;
    //mi faccio costruire le coordinate, quindi calcolo l'area
    //Eigen::MatrixXd coordinate = ShapeLibrary::Triangle::Coordinate();
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
    //cout<<area<<endl;
    return abs(area);
}


int Triangle::Vicini(ShapeLibrary::Triangle& triangolo2)
{
    //partendo dal presupposto che due triangolo possono avere al massimo un lato in comune:
    //controllo se il triangolo1 e il 2 sono adiacenti verificando se hanno un lato in comune

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
    return -1;
}



/*vector<int> Triangle::Raffina(){


};
bool Triangle::Verifica(){

};
*/
/*vector<ShapeLibrary::Triangle> lista;
 Eigen::MatrixXd adiacenza;
*/

//io gli passo i vertici presi dalla triangular mesh che sono un array e la struct0d con le informazioni sui vertici
Mesh::Mesh(vector<ShapeLibrary::Triangle>& lista): lista(lista){
    //calcolo la matrice di adiacenza
    unsigned int numTri = lista.size();
    Eigen::MatrixXd adj = Eigen::MatrixXd::Zero(numTri,numTri);
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
                adj(lista[i].id, lista[j].id) = link;
                adj(lista[j].id, lista[i].id) = link;
            }
            //le segno nella matrice di adiacenza


        }
    }
    adiacenza = adj;

}




}




