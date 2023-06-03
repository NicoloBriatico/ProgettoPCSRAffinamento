#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include "map"


using namespace Eigen;
using namespace std;

namespace ShapeLibrary {
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


//struct per le informazioni su vertici e lati

  class Vertice
   {
    public:

       unsigned int id;
       unsigned int marker;
       double x;
       double y;


       Vertice() = default;
       //al costruttore passo id, vertici, lati e struct e lui mi salva le informazioni e in più definisce le coordinate (derivandole dalla struct)
       Vertice(const unsigned int& id,const unsigned int& marker,const double& x, const double& y );


    };

   class Arco
   {
    public:

      unsigned int id;
      unsigned int marker;
      ShapeLibrary::Vertice inizio;
      ShapeLibrary::Vertice fine;
      double lunghezza;


      Arco() = default;
      //al costruttore passo id, vertici, lati e struct e lui mi salva le informazioni e in più definisce le coordinate (derivandole dalla struct)
      Arco(const unsigned int& id,const unsigned int& marker, ShapeLibrary::Vertice& inizio, ShapeLibrary::Vertice& fine);
      void CalcolaLunghezza();
      ShapeLibrary::Vertice CalcolaPuntoMedio(const unsigned int& newIdVert);
    };


//classe triangolo per le informazioni sui triangoli della mesh
  class Triangle
  {
    //attenzione che andrebbero messi in ordine gli attributi così come glieli passo, infatti mi da un warning -Wreord

    public:

      unsigned int id;
      array<ShapeLibrary::Vertice, 3> vertices;
      array<ShapeLibrary::Arco, 3> edges;
      double area;

      //vector<ShapeLibrary::Triangle> vicini;

      Triangle() = default;
      //al costruttore passo id, vertici, lati e struct e lui mi salva le informazioni e in più definisce le coordinate (derivandole dalla struct)
      Triangle(const unsigned int& id, array<ShapeLibrary::Vertice, 3>& vertices, array<ShapeLibrary::Arco, 3>& edges);

      void CalcolaArea();
      void isVicino(ShapeLibrary::Triangle& triangolo2, Eigen::SparseMatrix<unsigned int>& adiacenza);
      ShapeLibrary::Vertice VerticeOpposto(ShapeLibrary::Arco& arco);
      tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco>  Raffina(const unsigned int& newIdEdges, const unsigned int& newIdVert);

  };

  class Mesh
  {
  //private:

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
}




#endif // __EMPTY_H
