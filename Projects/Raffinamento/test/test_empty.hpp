#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "empty_class.hpp"
#include "Eigen/Eigen"

using namespace testing;
using namespace Eigen;
using namespace ShapeLibrary;
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
