#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include "map"


using namespace Eigen;
using namespace std;

namespace ShapeLibrary {

//funzione per il passaggio da un id all'oggetto associato all'id
template<typename T>
T id2object(unsigned int& id, vector<T>& vertici)
{
    for (unsigned int i=0; i< vertici.size();i++)
    {
        if (vertici[i].id ==id)
            return vertici[i];
    }
    T nullo;
    return nullo;
}

//*************************************************************************

class Vertice
{
public:
    //informazioni sui vertici estratte in input
    unsigned int id;
    unsigned int marker;
    double x;
    double y;


    Vertice() = default;
    Vertice(const unsigned int& id,const unsigned int& marker,const double& x, const double& y );


};

//*************************************************************************

class Arco
{
public:
    //informazioni sugli archi estratte in input
    unsigned int id;
    unsigned int marker;
    ShapeLibrary::Vertice inizio;
    ShapeLibrary::Vertice fine;

    //attributo aggiunto
    double lunghezza;


    Arco() = default;
    Arco(const unsigned int& id,const unsigned int& marker, ShapeLibrary::Vertice& inizio, ShapeLibrary::Vertice& fine);

    void CalcolaLunghezza();
    ShapeLibrary::Vertice CalcolaPuntoMedio(const unsigned int& newIdVert);
};

//*************************************************************************

class Triangle
{
public:
    //informazioni sui triangoli estratte in input
    unsigned int id;
    array<ShapeLibrary::Vertice, 3> vertices;
    array<ShapeLibrary::Arco, 3> edges;

    //attributo aggiunto
    double area;

    Triangle() = default;
    Triangle(const unsigned int& id, array<ShapeLibrary::Vertice, 3>& vertices, array<ShapeLibrary::Arco, 3>& edges);

    void CalcolaArea();
    void isVicino(ShapeLibrary::Triangle& triangolo2, Eigen::SparseMatrix<unsigned int>& adiacenza);
    ShapeLibrary::Vertice VerticeOpposto(ShapeLibrary::Arco& arco);
    tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco>  Raffina(const unsigned int& newIdEdges, const unsigned int& newIdVert);

};

//*************************************************************************

class Mesh
{
public:
    vector<ShapeLibrary::Triangle> triangoli;
    vector<ShapeLibrary::Arco> archi;
    vector<ShapeLibrary::Vertice> vertici;

    Eigen::SparseMatrix<unsigned int> adiacenza;

    Mesh() = default;
    Mesh(vector<ShapeLibrary::Triangle>& triangoli,vector<ShapeLibrary::Arco>& archi,vector<ShapeLibrary::Vertice>& vertici);

    void CalcolaMatriceAdiacenza();
    unsigned int NuovoIdVertice();
    unsigned int NuovoIdArco();
    unsigned int NuovoIdTriangolo();
    unsigned int Trova(unsigned int& col, unsigned int& valore);
    void CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza, ShapeLibrary::Arco& arcoVecchio);
    ShapeLibrary::Arco CercaArco(ShapeLibrary::Vertice& nodo1,ShapeLibrary::Vertice& nodo2);
    void InserisciTriangoli(unsigned int& newIdTriangle, ShapeLibrary::Arco& arco, ShapeLibrary::Vertice& nodo3);
    //void CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza);
    void Verifica(ShapeLibrary::Triangle& triangolo, ShapeLibrary::Arco& arcoNuovo, ShapeLibrary::Vertice& nodoNuovo, ShapeLibrary::Arco& arcoVecchio);
    void RaffinamentoStart();
    void Esporta();

};
//*************************************************************************
}




#endif // __EMPTY_H
