#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include "map"


using namespace Eigen;
using namespace std;

namespace ShapeLibrary {

//struct per le informazioni su vertici e lati
    struct TriangularMesh
    {
        unsigned int NumberCell0D = 0; ///< number of Cell0D
        vector<unsigned int> Cell0DId = {}; ///< Cell0D id, size 1 x NumberCell0D
        vector<Vector2d> Cell0DCoordinates = {}; ///< Cell0D coordinates, size 2 x NumberCell0D (x,y)
        map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; ///< Cell0D markers, size 1 x NumberCell0D (marker)

        unsigned int NumberCell1D = 0; ///< number of Cell1D
        vector<unsigned int> Cell1DId = {}; ///< Cell1D id, size 1 x NumberCell1D
        vector<Vector2i> Cell1DVertices = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
        map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; ///< Cell1D propertoes, size 1 x NumberCell1D (marker)

    };

//classe triangolo per le informazioni sui triangoli della mesh
  class Triangle
  {
    //attenzione che andrebbero messi in ordine gli attributi così come glieli passo, infatti mi da un warning -Wreorder
    private:
      array<unsigned int, 3> vertices;

      Eigen::MatrixXd coordinate;

    public:
      TriangularMesh& mesh ;
      unsigned int id;
      array<unsigned int, 3> edges;
      Triangle() = default;
      //al costruttore passo id, vertici, lati e struct e lui mi salva le informazioni e in più definisce le coordinate (derivandole dalla struct)
      Triangle(unsigned int& id, array<unsigned int, 3>& vertices, array<unsigned int, 3>& edges, TriangularMesh& mesh);

      //metodo che restituisce il valore dell'area del triangolo
      double Area();
      //metodo che dato un triangolo restituisce se presente, il lato adiacente
      int Vicini(ShapeLibrary::Triangle& triangolo2);
      //raffino il triangolo
      Vector2i Raffina();

  };


  //classe che definisce la mesh come insieme di triangoli
  class Mesh
  {
    private:
      vector<ShapeLibrary::Triangle> lista;


    public:
      // l'ho messa pubblica nell'ottica di farne un accesso nel main, ma considerando il commento scritto, forse ha più senso metterlo fra i privati
      Eigen::SparseMatrix<double> adiacenza;

      Mesh() = default;
      //prende in input tutti i triangoli e costruisce la matrice di adiacenza
      Mesh(vector<ShapeLibrary::Triangle>& lista);

      //definisco i metodi
      ///aggiungo un triangolo alla mesh
      /// verifico la buona positura della mesh (qui devo richiamare il metodo di raffinamento della classe triangolo
      void Verifica(unsigned int& idPartenza ,Vector2i& aggiunta  );


  };


}




#endif // __EMPTY_H
