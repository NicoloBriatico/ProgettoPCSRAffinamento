#ifndef __EMPTY_H
#define __EMPTY_H
//dobbiamo sicuramente cambiare nome alla classe

#include <iostream>
#include "Eigen/Eigen"
#include "map"




// Un'idea potrebbe essere:
/*definire una classe triangolo che ha diversi metodi:
 * 1. calcolo aree;
 * 2. buona positura;
 * 3. bisezione;
 *
 * oss: per il calcolo delle aree dovremmo sfruttare le informazioni tratte dal file, conoscendo sia i lati che i punti, forse conviene calcolare l'area come un poligono e quindi implementare solo quel metodo
 * oss: nell'ottica della lezione del 19/05 potremmo anche pensare di definire 3 classi al posto di 3 metodi, ma va capito anche se ne vale effettivamente la pena
 */

using namespace Eigen;
using namespace std;

namespace ShapeLibrary {

struct TriangularMesh
{
    unsigned int NumberCell0D = 0; ///< number of Cell0D
    std::vector<unsigned int> Cell0DId = {}; ///< Cell0D id, size 1 x NumberCell0D
    std::vector<Vector2d> Cell0DCoordinates = {}; ///< Cell0D coordinates, size 2 x NumberCell0D (x,y)
    std::map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; ///< Cell0D markers, size 1 x NumberCell0D (marker)

    unsigned int NumberCell1D = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DId = {}; ///< Cell1D id, size 1 x NumberCell1D
    std::vector<Vector2i> Cell1DVertices = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; ///< Cell1D propertoes, size 1 x NumberCell1D (marker)

};


  class Triangle
  {
    //attenzione che andrebbero messi in ordine gli attributi così come glieli passo, infatti mi da un warning -Wreorder
    private:
      array<unsigned int, 3> vertices;
      TriangularMesh& mesh ;
      Eigen::MatrixXd coordinate;

    public:
      unsigned int id;
      array<unsigned int, 3> edges;
      Triangle() = default;
      //io gli passo i vertici presi dalla triangular mesh che sono un array e la struct0d con le informazioni sui vertici
      Triangle(unsigned int& id, array<unsigned int, 3>& vertices, array<unsigned int, 3>& edges, TriangularMesh& mesh);

      //definisco i metodi
      double Area();
      int Vicini(ShapeLibrary::Triangle& triangolo2);
      //vector<int> Raffina();

  };


  class Mesh
  {
    private:
      vector<ShapeLibrary::Triangle> lista;


    public:
      //la sto pensando come una matrice di numerotriangoliXnumerotriangoli simmetrica che indica se triangolo i è collegato a triangolo j con l'arco segnato come argomento della matrice
       Eigen::MatrixXd adiacenza;
      Mesh() = default;
      //io gli passo i vertici presi dalla triangular mesh che sono un array e la struct0d con le informazioni sui vertici
      Mesh(vector<ShapeLibrary::Triangle>& lista);

      //definisco i metodi
      ///aggiungo un triangolo alla mesh
      /// verifico la buona positura della mesh (qui devo richiamare il metodo di raffinamento della classe triangolo
      //vector<int> Raffina();
      //bool Verifica();


  };


}




#endif // __EMPTY_H
