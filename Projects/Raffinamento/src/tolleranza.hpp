#ifndef __TOLLERANZA_H
#define __TOLLERANZA_H

#include "iostream"
#include "list"

#include "Eigen/Eigen"
#include "map"
//#include "sortingArea.hpp"


/*
 * il file sulle tolleranze l'ho preso dall'esercitazione convex hull
 */

using namespace std;
using namespace Eigen;
namespace TolleranzaLibrary
{

  constexpr double max_tolerance(const double& x, const double& y)
  {
    return x > y ? x : y;
  }

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
      {
      }

      Point(const Point& p):
        x(p.x), y(p.y), id(p.id)
      {
      }
  };
  inline double normSquared(const double& x, const double& y)
  {
    return x * x + y * y;
  }

  inline bool operator==(const Point& p1, const Point& p2)
  {
    return (normSquared(p1.x - p2.x, p1.y - p2.y) <=
            Point::geometricTol * Point::geometricTol *
            max(normSquared(p1.x, p1.y), normSquared(p2.x, p2.y)));
  }

  inline bool operator!=(const Point& p1, const Point& p2)
  {
    return !(p1 == p2);
  }

  inline ostream& operator<<(ostream& os, const Point& p2)
  {
    os << p2.id;
    return os;
  }

  inline bool operator>(const Point& p1, const Point& p2)
  {
    return p1.x > p2.x + Point::geometricTol * max(p1.x, p2.x);
  }

  inline bool operator<=(const Point& p1, const Point& p2)
  {
    return !(p1 > p2);
  }


//FORSE DOVREMMO INSERIRE IL SORTING PER DARGLI UN DEFINIZIONE DI TOLLERANZA NEL CALCOLO DEL <, >,  =, ECC..-

  template<typename T>
  vector<T> HeapSort(const vector<T>& v);

  /*non credo che queste funzioni ci servano*/

  /*bool UpperLine(const Point& p1,
                 const Point& p2,
                 const Point& p3);

  void MergeHulls(vector<Point>& sortedV,
                  const unsigned int& cx);


  void MergeHull(vector<Point>& sortedV,
                 const unsigned int& sx,
                 const unsigned int& dx);

  vector<Point> ConvexHull(vector<Point> points);
*/

}

#endif // __TOLLERANZA_H




