#ifndef __EMPTY_H
#define __EMPTY_H
//dpbbiamo siciramente cambiare nome alla classe

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
 */


using namespace std;

namespace ShapeLibrary {
/* qui va aggiustato perchè non ha senso definire un classe poligono e una triangolo, a noi serve calcolare aree di mesh triangolari, tanto vale implementare solo quelle*/
//al più potremmo pensare di implementare più metodi per il calcolo delle aree, ma a mio parere è inutikle, tanto scegliamo noi cosa passarglii alla funzione
  class Polygon {
    private:
      Eigen::MatrixXd points;

    public:
      Polygon() = default;
      Polygon( Eigen::MatrixXd& points);
      double Area() ;
      string Show() {return "Polygon: " + to_string(Area()) ; }
      //double Area(Eigen::MatrixXd& points){ return Area; }
  };
  //oss: io gestirei alcuni casi particolari tipo triangolo degenere (eg una linea) che poi testiamo e altre cose patologiche
  class Triangle : public Polygon
  {
    private:
      Eigen::MatrixXd points;
      double base;
      double height;
      bool hasPoints;
      bool hasBaseHeight;

    public:

      Triangle() = default;
      Triangle(double& base,
               double& height);

      Triangle(Eigen::MatrixXd& points);

      double Area() ;
      string Show() {
          double area = Area();
          if (hasPoints) {

                return "Triangle As Polygon: "+ to_string(area);
          }
          else if (hasBaseHeight){
                return "Triangle: " + to_string(area) ;
          }
          else{
                return "Dati passati sbagliati";
          }
      }
  };
}













/*
#ifndef __SHAPE_H
#define __SHAPE_H











}
#endif // __SHAPE_H

*/
#endif // __EMPTY_H
