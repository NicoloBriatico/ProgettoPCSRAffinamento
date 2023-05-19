#include "empty_class.hpp"
#include <math.h>

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */

namespace ShapeLibrary {
//ci deve essere un metodo show
Polygon::Polygon( Eigen::MatrixXd& points):points(points){}


   // area Polygon::Area() = area::0.0;

double Polygon::Area()
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

//poligono con coordinate
Triangle::Triangle( Eigen::MatrixXd& points):points(points){hasPoints = true;
    hasBaseHeight = false;}
Triangle::Triangle(double& base,double& height):
    base(base),
    height(height)
{hasPoints = false;
    hasBaseHeight = true;}
double Triangle::Area()
{
    if (hasPoints) {
        Polygon triangle = Polygon(points);
        return triangle.Area();
    }
    else if (hasBaseHeight){
        double area = 0.0;
        area = (base * height)*0.5;
        return area;
    }
    else{
        return 0;
    }

}



}




