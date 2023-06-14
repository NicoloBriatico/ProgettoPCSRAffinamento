#ifndef __TOLLERANZA_H
#define __TOLLERANZA_H
/*
 *
 * CANCELLA
 *
 *
 */
#include "iostream"
#include "list"

#include "Eigen/Eigen"
#include "map"

#include "empty_class.hpp"

using namespace std;
using namespace Eigen;
using namespace ShapeLibrary;
namespace TolleranzaLibrary
{
/*
constexpr double max_tolerance(const double& x, const double& y){
    return x > y ? x : y;
}

// ***************************************************************************

struct Point
{
    double x;
    double y;
    unsigned int id;

    Point *succ = nullptr;
    Point *prec = nullptr;

    static constexpr double geometricTol = 1.0e-12;
    static constexpr double geometricTol_Squared = max_tolerance(Point::geometricTol * Point::geometricTol,
                                                                 numeric_limits<double>::epsilon());

    Point(const double& x,
          const double& y,
          const unsigned int& id):
        x(x), y(y), id(id)
    {}

    Point(const Point& p):
        x(p.x), y(p.y), id(p.id)
    {}
};

// ***************************************************************************

inline double normSquared(const double& x, const double& y){
    return x * x + y * y;
}

// ***************************************************************************

inline bool operator==(const Point& p1, const Point& p2)
{
    return (normSquared(p1.x - p2.x, p1.y - p2.y) <=
            Point::geometricTol * Point::geometricTol *
            max(normSquared(p1.x, p1.y), normSquared(p2.x, p2.y)));
}

// ***************************************************************************

inline bool operator!=(const Point& p1, const Point& p2){
    return !(p1 == p2);
}

// ***************************************************************************

inline ostream& operator<<(ostream& os, const Point& p2){
    os << p2.id;
    return os;
}

// ***************************************************************************

inline bool operator>(const Point& p1, const Point& p2){
    return p1.x > p2.x + Point::geometricTol * max(p1.x, p2.x);
}

// ***************************************************************************

inline bool operator<=(const Point& p1, const Point& p2){
    return !(p1 > p2);
}
*/
// ***************************************************************************
/*
template<typename T>
vector<T> HeapSort(const vector<T>& v);

void CalcolaLunghezza();
ShapeLibrary::Vertice CalcolaPuntoMedio(const unsigned int& newIdVert);

void CalcolaArea();
void isVicino(ShapeLibrary::Triangle& triangolo2, Eigen::SparseMatrix<unsigned int>& adiacenza);
ShapeLibrary::Vertice VerticeOpposto(ShapeLibrary::Arco& arco);
tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco>  Raffina(const unsigned int& newIdEdges, const unsigned int& newIdVert);

void CalcolaMatriceAdiacenza();
unsigned int NuovoIdVertice();
unsigned int NuovoIdArco();
unsigned int NuovoIdTriangolo();
unsigned int Trova(unsigned int& col, unsigned int& valore);
void CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza, ShapeLibrary::Arco& arcoVecchio);
ShapeLibrary::Arco CercaArco(ShapeLibrary::Vertice& nodo1,ShapeLibrary::Vertice& nodo2);
void InserisciTriangoli(unsigned int& newIdTriangle, ShapeLibrary::Arco& arco, ShapeLibrary::Vertice& nodo3);
//void CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza);
void Verifica(ShapeLibrary::Triangle& triangolo, ShapeLibrary::Vertice& nodoNuovo, ShapeLibrary::Arco& arcoVecchio);
void RaffinamentoStart();
void Esporta();
*/
}

#endif // __TOLLERANZA_H
