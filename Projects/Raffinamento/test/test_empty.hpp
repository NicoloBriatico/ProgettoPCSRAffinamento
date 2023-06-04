#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"
#include "sortingArea.hpp"
#include "Eigen/Eigen"

using namespace testing;
using namespace Eigen;
using namespace ShapeLibrary;
using namespace SortLibrary;

TEST(TestShape,TestCalcolaLunghezza)
{
    Vertice vertice1 = Vertice(41,0,0.703125,0.421875);
    Vertice vertice2 = Vertice(43,0,0.705211,0.330114);
    Arco arco = Arco(0,0,vertice1,vertice2);
    arco.CalcolaLunghezza();
    EXPECT_FLOAT_EQ(arco.lunghezza,0.0917847);
    }

TEST(TeshShape,TestCalcolaPuntoMedio)
{
    Vertice vertice1 = Vertice(41,0,0.703125,0.421875);
    Vertice vertice2 = Vertice(43,0,0.705211,0.330114);
    Arco arco = Arco(0,0,vertice1,vertice2);
    Vertice PuntoMedio = arco.CalcolaPuntoMedio(199);
    EXPECT_EQ(PuntoMedio.id,199);
    EXPECT_EQ(PuntoMedio.marker,0);
    EXPECT_FLOAT_EQ(PuntoMedio.x,0.704168);
    EXPECT_FLOAT_EQ(PuntoMedio.y,0.3759945);
}

TEST(TestShape,TestCalcolaArea)
{
    array<ShapeLibrary::Vertice,3> vertices;
    array<ShapeLibrary::Arco,3> edges;
    Vertice vertice1 = Vertice(41,0,0.703125,0.421875);
    Vertice vertice2 = Vertice(43,0,0.705211,0.330114);
    Vertice vertice3 = Vertice(15,0,0.875000,0.375000);
    vertices[0]=vertice1;
    vertices[1]=vertice2;
    vertices[2]=vertice3;
    Arco arco1 = Arco(0,0,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,0,vertice3,vertice1);
    edges[0]=arco1;
    edges[1]=arco2;
    edges[2]=arco3;
    Triangle triangle = Triangle(0,vertices,edges);
    triangle.CalcolaArea();
    EXPECT_DOUBLE_EQ(triangle.area,0.036789);
}

TEST(TestShape, TestVerticeOpposto)
{
    Vertice vertice1 = Vertice(41,0,0.703125,0.421875);
    Vertice vertice2 = Vertice(43,0,0.705211,0.330114);
    Vertice vertice3 = Vertice(15,0,0.875000,0.375000);
    array<ShapeLibrary::Vertice,3> vertices;
    vertices[0]=vertice1;
    vertices[1]=vertice2;
    vertices[2]=vertice3;
    Arco arco1 = Arco(0,0,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,0,vertice3,vertice1);
    array<ShapeLibrary::Arco,3> edges;
    edges[0]=arco1;
    edges[1]=arco2;
    edges[2]=arco3;
    Triangle triangle = Triangle(0,vertices,edges);
    Vertice verticeopposto = triangle.Triangle::VerticeOpposto(arco1);
    EXPECT_EQ(verticeopposto.id,15);
    EXPECT_EQ(verticeopposto.marker,0);
    EXPECT_EQ(verticeopposto.x,0.875000);
    EXPECT_EQ(verticeopposto.y,0.375000);
}

TEST(TestSort, TestMigliorePadreFigli)
{
    Vertice vertice1 = Vertice(41,0,0.703125,0.421875);
    Vertice vertice2 = Vertice(43,0,0.705211,0.330114);
    Vertice vertice3 = Vertice(15,0,0.875000,0.375000);
    vector<Vertice> v = {vertice1,vertice2,vertice3};
    unsigned int j = SortLibrary::MigliorePadreFigli(0,v,3,&Vertice::id);


    EXPECT_EQ(j,2);
}


/*
//testo triangolo
TEST(TestShape, TestTriangleAsPolygon)
{
  //definisco una matrice con le coordinate del triangolo
  Eigen::MatrixXd coordinates = MatrixXd::Zero(2,3);
  coordinates << 2.8, 3.9, 3.1,
                  3.9, 1.8, 2.7;

  //chiamo il triangolo passando le coordinate
  Triangle triangle = Triangle(coordinates);

  //mi aspetto che mi calcoli l'area
  EXPECT_EQ(triangle.Show(), "Triangle As Polygon: 0.345000");
}

//testo triangolo passando base e altezza
TEST(TestShape, TestTriangle)
{
  //definisco base e altezza
  double base = 0.5;
  double height = 0.6;
  //passo a triangolo base e altezza e mi aspetto calcoli l'area
  Triangle triangle = Triangle(base, height);

  EXPECT_EQ(triangle.Show(), "Triangle: 0.150000");
}

//testo il triangolo equilatero con base e altezza
TEST(TestShape, TestTriangleEquilateralAsTraingle)
{
  //definisco base e altezza
  double base = 2;
  double height = sqrt(3);
  TriangleEquilateral triangle = TriangleEquilateral(base, height);

  EXPECT_EQ(triangle.Show(), "TriangleEquilateral As Triangle: 1.732051");
}

//testo il triangolo equilatero con il lato
TEST(TestShape, TestTriangleEquilateral)
{
  double edgeLength = 0.6;
  TriangleEquilateral triangle = TriangleEquilateral(edgeLength);

  EXPECT_EQ(triangle.Show(), "TriangleEquilateral: 0.155885");
}

//testo il quadrilatero con le coordinate
TEST(TestShape, TestQuadrilateralAsPolygon)
{
  Eigen::MatrixXd coordinates = MatrixXd::Zero(2, 4);
  coordinates << 0.0, 1.0, 1.0, 0.0,
                  0.0, 0.0, 1.0, 1.0;
  Quadrilateral quadrilateral = Quadrilateral(coordinates);

  EXPECT_EQ(quadrilateral.Show(), "Quadrilateral As Polygon: 1.000000");
}

//testo il calcolo dell'area di un quadrilatero passandogli due triangoli
TEST(TestShape, TestQuadrilateral)
{
  //definisco le coordinate dei due triangoli
  Eigen::MatrixXd coordinates1 = MatrixXd::Zero(2,3);
  coordinates1 << 0.0, 1.0, 1.0,
                  0.0, 0.0, 1.0;

  Eigen::MatrixXd coordinates2 = MatrixXd::Zero(2,3);
  coordinates2 << 1.0, 0.0, 0.0,
                  1.0, 1.0, 0.0;

  //calcolo le aree dei due triangoli
  Triangle t1 = Triangle(coordinates1);
  Triangle t2 = Triangle(coordinates2);

  //passo le aree alla classe quadrilateri che ne calcola il valore totale
  Quadrilateral quadrilateral = Quadrilateral(t1, t2);

  EXPECT_EQ(quadrilateral.Show(), "Quadrilateral: 1.000000");
}

//testo il rettangolo come poligono, attraverso coordinate
TEST(TestShape, TestRectangleAsPolygon)
{
  Eigen::MatrixXd coordinates = MatrixXd::Zero(2, 4);
  coordinates << 0.0, 1.0, 1.0, 0.0,
                  0.0, 0.0, 1.0, 1.0;
  Rectangle rectangle = Rectangle(coordinates);

  EXPECT_EQ(rectangle.Show(), "Rectangle As Polygon: 1.000000");
}

//testo rettangolo come un quadrilatero
TEST(TestShape, TestRectangleAsQuadrilateral)
{
  Eigen::MatrixXd coordinates1 = MatrixXd::Zero(2,3);
  coordinates1 << 0.0, 1.0, 1.0,
                  0.0, 0.0, 1.0;

  Eigen::MatrixXd coordinates2 = MatrixXd::Zero(2,3);
  coordinates2 << 1.0, 0.0, 0.0,
                  1.0, 1.0, 0.0;

  Triangle t1 = Triangle(coordinates1);
  Triangle t2 = Triangle(coordinates2);

  Rectangle rectangle = Rectangle(t1, t2);

  EXPECT_EQ(rectangle.Show(), "Rectangle As Quadrilateral: 1.000000");
}

//testo rettangolo
TEST(TestShape, TestRectangle)
{
  double base = 0.5;
  double height = 0.6;
  Rectangle rectangle = Rectangle(base, height);

  EXPECT_EQ(rectangle.Show(), "Rectangle: 0.300000");
}

//testo il quadrato come poligono
TEST(TestShape, TestSquareAsPolygon)
{
  Eigen::MatrixXd coordinates = MatrixXd::Zero(2, 4);
  coordinates << 0.0, 1.0, 1.0, 0.0,
                  0.0, 0.0, 1.0, 1.0;
  Square rectangle = Square(coordinates);

  EXPECT_EQ(rectangle.Show(), "Square As Polygon: 1.000000");
}

//testo il quadrato come quadrilatero
TEST(TestShape, TestSquareAsQuadrilateral)
{
  Eigen::MatrixXd coordinates1 = MatrixXd::Zero(2,3);
  coordinates1 << 0.0, 1.0, 1.0,
                  0.0, 0.0, 1.0;

  Eigen::MatrixXd coordinates2 = MatrixXd::Zero(2,3);
  coordinates2 << 1.0, 0.0, 0.0,
                  1.0, 1.0, 0.0;

  Triangle t1 = Triangle(coordinates1);
  Triangle t2 = Triangle(coordinates2);

  Square square = Square(t1, t2);

  EXPECT_EQ(square.Show(), "Square As Quadrilateral: 1.000000");
}

//testo il quadrato come base per altezza
TEST(TestShape, TestSquareAsRectangle)
{
  double base = 0.5;
  double height = 0.5;
  Square square = Square(base, height);

  EXPECT_EQ(square.Show(), "Square As Rectangle: 0.250000");
}

//testo il quadrato come quadrato
TEST(TestShape, TestSquare)
{
  double edgeLength = 0.5;
  Square square = Square(edgeLength);

  EXPECT_EQ(square.Show(), "Square: 0.250000");
}
*/

#endif // __TEST_EMPTY_H
