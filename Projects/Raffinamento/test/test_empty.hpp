#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>
#include "tolleranza.hpp"
#include "empty_class.hpp"
#include "sortingArea.hpp"
#include "Eigen/Eigen"

using namespace testing;
using namespace Eigen;
using namespace ShapeLibrary;
using namespace SortLibrary;
using namespace TolleranzaLibrary;
/*
TEST(TestShape,TestId2Object)
{
    //id del vertice che voglio recuperare
    unsigned int id=42;

    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);

    vector<Vertice> v = {vertice1,vertice2,vertice3};

    Vertice vertice = id2object(id,v);

    //mi aspetto che abbia come attributi quelli del vertice con l'id dato come argomento
    EXPECT_EQ(vertice.id,42);
    EXPECT_EQ(vertice.marker,6);
    EXPECT_EQ(vertice.x,1);
    EXPECT_EQ(vertice.y,0);
}

TEST(TestShape,TestCalcolaLunghezza)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);

    Arco arco = Arco(0,5,vertice1,vertice2);

    arco.CalcolaLunghezza();

    EXPECT_EQ(arco.lunghezza,1);
}

TEST(TeshShape,TestCalcolaPuntoMedio)
{
    Vertice vertice1 = Vertice(41,4,0,1);
    Vertice vertice2 = Vertice(42,6,1,0);

    Arco arco = Arco(1,0,vertice1,vertice2);

    Vertice PuntoMedio = arco.CalcolaPuntoMedio(200);

    EXPECT_EQ(PuntoMedio.id,200);
    EXPECT_EQ(PuntoMedio.marker,0);
    EXPECT_EQ(PuntoMedio.x,0.5);
    EXPECT_EQ(PuntoMedio.y,0.5);
}

TEST(TestShape,TestCalcolaArea)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);

    array<ShapeLibrary::Vertice,3> vertices;
    array<ShapeLibrary::Arco,3> edges;

    vertices[0]=vertice1;
    vertices[1]=vertice2;
    vertices[2]=vertice3;

    edges[0]=arco1;
    edges[1]=arco2;
    edges[2]=arco3;

    Triangle triangolo0 = Triangle(0,vertices,edges);

    triangolo0.CalcolaArea();

    EXPECT_EQ(triangolo0.area,0.5);
}

TEST(TestShape,TestIsVicino)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);
    Vertice vertice4 = Vertice(43,3,1,1);
    Vertice vertice5 = Vertice(44,2,2,0);

    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticitriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticitriangolo2 = {vertice4,vertice3,vertice5};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);
    Arco arco4 = Arco(3,8,vertice2,vertice4);
    Arco arco5 = Arco(4,0,vertice4,vertice3);
    Arco arco6 = Arco(5,6,vertice3,vertice5);
    Arco arco7 = Arco(6,7,vertice5,vertice4);

    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> architriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> architriangolo2 = {arco5,arco6,arco7};

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};

    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    Triangle triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    Triangle triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);

    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};

    Mesh mesh = Mesh(triangoli,archi,vertici);

    unsigned int numTri = triangoli.size();

    //creo una matrice sparsa della dimensione corretta che andrò a popolare con il metodo isVicino
    Eigen::SparseMatrix<unsigned int> adj(numTri,numTri);
    mesh.adiacenza=adj;

    triangolo0.isVicino(triangolo1,mesh.adiacenza);
    triangolo1.isVicino(triangolo2,mesh.adiacenza);
    triangolo0.isVicino(triangolo2,mesh.adiacenza);

    EXPECT_EQ(mesh.adiacenza.coeff(0,1)-1,1);
    EXPECT_EQ(mesh.adiacenza.coeff(1,0)-1,1);
    EXPECT_EQ(mesh.adiacenza.coeff(1,2)-1,4);
    EXPECT_EQ(mesh.adiacenza.coeff(2,1)-1,4);
    //non mi aspetto adiacenza tra triangolo0 e triangolo2
    EXPECT_EQ(mesh.adiacenza.coeff(0,2)-1,-1);
    EXPECT_EQ(mesh.adiacenza.coeff(2,0)-1,-1);

}

TEST(TestShape,TestVerticeOpposto)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);

    array<ShapeLibrary::Vertice,3> vertici;
    array<ShapeLibrary::Arco,3> archi;

    vertici[0]=vertice1;
    vertici[1]=vertice2;
    vertici[2]=vertice3;

    archi[0]=arco1;
    archi[1]=arco2;
    archi[2]=arco3;

    Triangle triangolo0 = Triangle(0,vertici,archi);

    Vertice verticeOpposto1 = triangolo0.Triangle::VerticeOpposto(arco1);
    Vertice verticeOpposto2 = triangolo0.Triangle::VerticeOpposto(arco2);
    Vertice verticeOpposto3 = triangolo0.Triangle::VerticeOpposto(arco3);

    EXPECT_EQ(verticeOpposto1.id,42);
    EXPECT_EQ(verticeOpposto2.id,40);
    EXPECT_EQ(verticeOpposto3.id,41);
}

TEST(TestShape,TestCalcolaMatriceAdiacenza)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);
    Vertice vertice4 = Vertice(43,3,1,1);
    Vertice vertice5 = Vertice(44,2,2,0);

    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticitriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticitriangolo2 = {vertice4,vertice3,vertice5};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);
    Arco arco4 = Arco(3,8,vertice2,vertice4);
    Arco arco5 = Arco(4,0,vertice4,vertice3);
    Arco arco6 = Arco(5,6,vertice3,vertice5);
    Arco arco7 = Arco(6,7,vertice5,vertice4);

    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> architriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> architriangolo2 = {arco5,arco6,arco7};

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};

    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    Triangle triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    Triangle triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);

    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};

    Mesh mesh = Mesh(triangoli,archi,vertici);
    //creo la matrice di adiacenza della mesh
    mesh.CalcolaMatriceAdiacenza();

    //controllo che i coefficienti di adiacenza rispecchino ciò che mi aspetto
    EXPECT_EQ(mesh.adiacenza.coeff(0,1)-1,1);
    EXPECT_EQ(mesh.adiacenza.coeff(1,0)-1,1);
    EXPECT_EQ(mesh.adiacenza.coeff(0,2)-1,-1);
    EXPECT_EQ(mesh.adiacenza.coeff(2,0)-1,-1);
    EXPECT_EQ(mesh.adiacenza.coeff(1,2)-1,4);
    EXPECT_EQ(mesh.adiacenza.coeff(2,1)-1,4);
    //un triangolo non deve considerare se stesso come adiacente
    EXPECT_EQ(mesh.adiacenza.coeff(0,0)-1,-1);
    EXPECT_EQ(mesh.adiacenza.coeff(1,1)-1,-1);
    EXPECT_EQ(mesh.adiacenza.coeff(2,2)-1,-1);
}

TEST(TestShape,TestCercaArco)
{
    //considero una mesh un pò diversa rispetto alla precedente per considerare tutte le declinazioni della funzione
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,2,1,0);
    Vertice vertice4 = Vertice(43,1,1,1);//pongo marker 1 per analizzare il caso in cui due vertici abbiano marker uguale
    Vertice vertice5 = Vertice(44,0,0.5,0.5);

    array<Vertice,3> verticiTriangolo0 = {vertice1,vertice2,vertice5};
    array<Vertice,3> verticiTriangolo1 = {vertice1,vertice3,vertice5};
    array<Vertice,3> verticiTriangolo2 = {vertice4,vertice3,vertice5};
    array<Vertice,3> verticiTriangolo3 = {vertice2,vertice4,vertice5};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,6,vertice1,vertice3);
    Arco arco3 = Arco(2,7,vertice3,vertice4);
    Arco arco4 = Arco(3,8,vertice2,vertice4);
    Arco arco5 = Arco(4,0,vertice2,vertice5);
    Arco arco6 = Arco(5,0,vertice3,vertice5);
    Arco arco7 = Arco(6,0,vertice5,vertice4);
    Arco arco8 = Arco(7,0,vertice1,vertice5);

    array<Arco,3> archiTriangolo0 = {arco1,arco5,arco8};
    array<Arco,3> archiTriangolo1 = {arco2,arco6,arco8};
    array<Arco,3> archiTriangolo2 = {arco3,arco6,arco7};
    array<Arco,3> archiTriangolo3 = {arco4,arco5,arco7};

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7,arco8};
    //ho bisogno nella funzione di archi ordinati per id decrescente
    archi=HeapSort(archi,&Arco::id);

    Triangle triangolo0 = Triangle(0,verticiTriangolo0,archiTriangolo0);
    Triangle triangolo1 = Triangle(1,verticiTriangolo1,archiTriangolo1);
    Triangle triangolo2 = Triangle(2,verticiTriangolo2,archiTriangolo2);
    Triangle triangolo3 = Triangle(3,verticiTriangolo3,archiTriangolo3);
    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2,triangolo3};

    Mesh mesh = Mesh(triangoli,archi,vertici);

    Arco arcoatteso = mesh.CercaArco(vertice2,vertice4);
    Arco arcoatteso1 = mesh.CercaArco(vertice1,vertice4);//che non esiste ancora, viene aggiunto in testa ad archi
    //ed avendo i due vertici stesso marker, così anche l'arco

    EXPECT_EQ(arcoatteso.id,3);
    EXPECT_EQ(arcoatteso.marker,8);

    EXPECT_EQ(arcoatteso1.id,8);//cioè id(nuovoarco)=id maggiore +1
    EXPECT_EQ(arcoatteso1.marker,1);

}

TEST(TestShape,TestRaffina)
{
    //lo testo su un solo triangolo, essendo un metodo della classe Triangle
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);

    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3};
    vertici = HeapSort(vertici,&Vertice::id);

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);

    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};

    vector<Arco> archi = {arco1,arco2,arco3};
    archi = HeapSort(archi,&Arco::id);

    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    vector<Triangle> triangoli = {triangolo0};

    Mesh mesh = Mesh(triangoli,archi,vertici);

    //raffinamento triangolo0
    unsigned int newIdEdge0 = mesh.NuovoIdArco();
    unsigned int newIdVert0 = mesh.NuovoIdVertice();

    tuple<Arco,Vertice,Arco> aggiunti0 = triangolo0.Raffina(newIdEdge0,newIdVert0);

    Arco nuovoArco0 = get<0>(aggiunti0);
    Vertice nuovoVertice0 = get<1>(aggiunti0);
    Arco arcoLungo0 = get<2>(aggiunti0);

    EXPECT_EQ(nuovoArco0.id,3);
    EXPECT_EQ(nuovoArco0.inizio.id,40);
    EXPECT_EQ(nuovoArco0.fine.id,43);
    EXPECT_EQ(nuovoVertice0.id,43);
    EXPECT_EQ(nuovoVertice0.x,0.5);
    EXPECT_EQ(nuovoVertice0.y,0.5);
    EXPECT_EQ(arcoLungo0.id,1);

}

TEST(TestShape,TestInserisciTriangoli)
{
    //creo mesh con solo triangolo0
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);

    array<Vertice,3> verticiTriangolo0 = {vertice1,vertice2,vertice3};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3};
    vertici = HeapSort(vertici,&Vertice::id);

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);

    array<Arco,3> archiTriangolo0 = {arco1,arco2,arco3};

    vector<Arco> archi = {arco1,arco2,arco3};
    archi = HeapSort(archi,&Arco::id);
    cout<< archi[0].id << endl;

    Triangle triangolo0 = Triangle(0,verticiTriangolo0,archiTriangolo0);

    vector<Triangle> triangoli = {triangolo0};

    Mesh mesh = Mesh(triangoli,archi,vertici);

    //raffino il triangolo0 e inserisco i due triangoli ottenuti dal raffinamento con InserisciTriangoli()
    unsigned int newIdEdge0 = mesh.NuovoIdArco();
    unsigned int newIdVert0 = mesh.NuovoIdVertice();

    tuple<Arco,Vertice,Arco> aggiunti0 = triangolo0.Raffina(newIdEdge0,newIdVert0);

    Arco nuovoArco0 = get<0>(aggiunti0);
    Arco arcoLungo0 = get<2>(aggiunti0);

    mesh.archi.insert(mesh.archi.begin(),nuovoArco0);

    //creo un id per il nuovo triangolo, non serviva l'ordinamento per area perchè è l'unico
    unsigned int newIdTriangle1 = mesh.NuovoIdTriangolo();

    mesh.InserisciTriangoli(newIdTriangle1,nuovoArco0,arcoLungo0.fine);//fine sarebbe vertice3, quindi
    //sto inserendo il triangolo con vertice1,verticeNuovo,vertice3

    //*quando viene inserito, edges sono in ordine nuovoArco0 (id3), nuovoArco0.fine-altro nodo(creato con id4)
    //*, nuovoArco0.inizio-altro nodo (già esistente, id2)
    //*creo e trovo gli altri due archi

    EXPECT_EQ(mesh.triangoli[0].id,1);
    EXPECT_EQ(mesh.triangoli[0].edges[0].id,3);
    EXPECT_EQ(mesh.triangoli[0].edges[1].id,4);
    EXPECT_EQ(mesh.triangoli[0].edges[2].id,2);

}

TEST(TestShape,TestTrova)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);
    Vertice vertice4 = Vertice(43,3,1,1);
    Vertice vertice5 = Vertice(44,2,2,0);

    array<Vertice,3> verticiTriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticiTriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticiTriangolo2 = {vertice4,vertice3,vertice5};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);
    Arco arco4 = Arco(3,8,vertice2,vertice4);
    Arco arco5 = Arco(4,0,vertice4,vertice3);
    Arco arco6 = Arco(5,6,vertice3,vertice5);
    Arco arco7 = Arco(6,7,vertice5,vertice4);

    array<Arco,3> archiTriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> archiTriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> archiTriangolo2 = {arco5,arco6,arco7};

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};

    Triangle triangolo0 = Triangle(0,verticiTriangolo0,archiTriangolo0);
    Triangle triangolo1 = Triangle(1,verticiTriangolo1,archiTriangolo1);
    Triangle triangolo2 = Triangle(2,verticiTriangolo2,archiTriangolo2);

    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};

    Mesh mesh = Mesh(triangoli,archi,vertici);
    mesh.CalcolaMatriceAdiacenza();

    //caso in cui c'è triangolo adiacente su quel lato
    unsigned int idTriangoloCorrente=1;
    unsigned int idArcoDiAdiacenza=4;
    unsigned int idTriAdiac = mesh.Trova(idTriangoloCorrente,idArcoDiAdiacenza);
    EXPECT_EQ(idTriAdiac,2);

    //caso in cui no adiacenza su quel lato, quel lato è di bordo
    unsigned int idTriangoloCorrente1=2;
    unsigned int idArcoDiAdiacenza1=5;
    unsigned int idTriAdiac1 = mesh.Trova(idTriangoloCorrente1,idArcoDiAdiacenza1);
    EXPECT_EQ(idTriAdiac1,2);//restituisce l'id del triangolo considerato (vedi col)
}

TEST(TestShape,TestCancellaTriangolo)
{
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);
    Vertice vertice4 = Vertice(43,3,1,1);
    Vertice vertice5 = Vertice(44,2,2,0);

    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticitriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticitriangolo2 = {vertice4,vertice3,vertice5};

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};

    Arco arco1 = Arco(0,5,vertice1,vertice2);
    Arco arco2 = Arco(1,0,vertice2,vertice3);
    Arco arco3 = Arco(2,6,vertice3,vertice1);
    Arco arco4 = Arco(3,8,vertice2,vertice4);
    Arco arco5 = Arco(4,0,vertice4,vertice2);
    Arco arco6 = Arco(5,6,vertice3,vertice5);
    Arco arco7 = Arco(6,7,vertice5,vertice4);

    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> architriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> architriangolo2 = {arco5,arco6,arco7};

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};

    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    Triangle triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    Triangle triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);

    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};

    Mesh mesh = Mesh(triangoli,archi,vertici);
    mesh.CalcolaMatriceAdiacenza();

    //*cancello triangolo0
    mesh.CancellaTriangolo(triangolo0,arco2);
    //*verifico la non adiacenza a nessun altro triangolo tramite coefficienti della matrice di adiacenza
    unsigned int adiacenzaPrimoArco = mesh.Trova(triangolo0.id,triangolo0.edges[0].id);
    unsigned int adiacenzaSecondoArco = mesh.Trova(triangolo0.id,triangolo0.edges[1].id);
    unsigned int adiacenzaTerzoArco = mesh.Trova(triangolo0.id,triangolo0.edges[2].id);

    EXPECT_EQ(adiacenzaPrimoArco,0);
    EXPECT_EQ(adiacenzaSecondoArco,0);
    EXPECT_EQ(adiacenzaTerzoArco,0);
}
*/
/*TEST(TestShape,TestVerifica)
{
    primo caso: il raffinamento termina alla prima iterazione
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,6,0,1);
    Vertice vertice3 = Vertice(42,5,1,0);
    Vertice vertice4 = Vertice(43,0,2,1);
    Vertice vertice5 = Vertice(44,6,0,2);
    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticitriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticitriangolo2 = {vertice4,vertice2,vertice5}; forse era vertice2
    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};
    vertici=HeapSort(vertici,&Vertice::id);

    Arco arco1 = Arco(1,6,vertice1,vertice2);
    Arco arco2 = Arco(2,0,vertice2,vertice3);
    Arco arco3 = Arco(3,5,vertice3,vertice1);
    Arco arco4 = Arco(4,0,vertice2,vertice4);
    Arco arco5 = Arco(5,8,vertice4,vertice3);
    Arco arco6 = Arco(6,6,vertice2,vertice5);
    Arco arco7 = Arco(7,7,vertice5,vertice4);
    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> architriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> architriangolo2 = {arco4,arco6,arco7};
    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};
    archi=HeapSort(archi,&Arco::id);


    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    Triangle triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    Triangle triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);
    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};
    triangoli = HeapSort(triangoli,&Triangle::area);

    Mesh mesh1 = Mesh(triangoli,archi,vertici);
    mesh1.CalcolaMatriceAdiacenza();
    unsigned int newIdEdge1 = mesh1.NuovoIdArco();

    unsigned int newIdVert1 = mesh1.NuovoIdVertice();
    tuple<Arco,Vertice,Arco> aggiunti1 = triangoli[0].Raffina(newIdEdge1,newIdVert1);

    mesh1.vertici.insert(mesh1.vertici.begin(),get<1>(aggiunti1));
    mesh1.archi.insert(mesh1.archi.begin(),get<0>(aggiunti1));


    mesh1.Verifica(triangoli[0],get<1>(aggiunti1),arco5);

    EXPECT_EQ(mesh1.vertici[0].id,45);
    EXPECT_EQ(mesh1.archi[0].id,8);

}*/
/*
TEST(TestShape,TestRaffinamentoStart)
{
    //*primo caso: il raffinamento termina alla prima iterazione
    Vertice vertice1 = Vertice(40,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(42,6,1,0);
    Vertice vertice4 = Vertice(43,3,2,1);
    Vertice vertice5 = Vertice(44,2,2,0);

    vector<Vertice> vertici = {vertice1,vertice2,vertice3,vertice4,vertice5};
    vertici=HeapSort(vertici,&Vertice::id);

    array<Vertice,3> verticitriangolo0 = {vertice1,vertice2,vertice3};
    array<Vertice,3> verticitriangolo1 = {vertice2,vertice4,vertice3};
    array<Vertice,3> verticitriangolo2 = {vertice4,vertice3,vertice5};

    Arco arco1 = Arco(1,6,vertice1,vertice3);
    Arco arco2 = Arco(2,0,vertice2,vertice3);
    Arco arco3 = Arco(3,5,vertice2,vertice1);
    Arco arco4 = Arco(4,8,vertice2,vertice4);
    Arco arco5 = Arco(5,0,vertice4,vertice3);
    Arco arco6 = Arco(6,6,vertice3,vertice5);
    Arco arco7 = Arco(7,7,vertice5,vertice4);

    vector<Arco> archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7};
    archi=HeapSort(archi,&Arco::id);

    array<Arco,3> architriangolo0 = {arco1,arco2,arco3};
    array<Arco,3> architriangolo1 = {arco2,arco4,arco5};
    array<Arco,3> architriangolo2 = {arco5,arco6,arco7};

    Triangle triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    Triangle triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    Triangle triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);

    vector<Triangle> triangoli = {triangolo0,triangolo1,triangolo2};
    triangoli = HeapSort(triangoli,&Triangle::area);

    Mesh mesh1 = Mesh(triangoli,archi,vertici);

    mesh1.CalcolaMatriceAdiacenza();
    mesh1.RaffinamentoStart();

    //controllo che abbia aggiunto il vertice e gli archi corretti
    EXPECT_EQ(mesh1.vertici[0].id,45);
    EXPECT_EQ(mesh1.archi[0].id,10);
    EXPECT_EQ(mesh1.archi[1].id,9);
    EXPECT_EQ(mesh1.archi[2].id,8);
    EXPECT_EQ(mesh1.triangoli[0].id,4);
    EXPECT_EQ(mesh1.triangoli[1].id,3);
    EXPECT_EQ(mesh1.triangoli.size(),4);

    //secondo caso: il vertice opposto del triangolo adiacente da raffinare coincide con il nuovo nodo del precedente
    mesh1.RaffinamentoStart();

    EXPECT_EQ(mesh1.vertici[0].id,46);
    EXPECT_EQ(mesh1.archi[0].id,14);
    EXPECT_EQ(mesh1.archi[1].id,13);
    EXPECT_EQ(mesh1.archi[2].id,12);
    EXPECT_EQ(mesh1.triangoli[0].id,8);
    EXPECT_EQ(mesh1.triangoli[1].id,7);
    EXPECT_EQ(mesh1.triangoli[2].id,6);
    EXPECT_EQ(mesh1.triangoli[3].id,5);
    EXPECT_EQ(mesh1.triangoli.size(),6);

    //terzo caso: si va avanti per più di due iterazioni, cambio totalmente mesh (rimane uguale solo il vertice1

    vertice2 = Vertice(41,4,0,2);
    vertice3 = Vertice(42,6,4,0);
    vertice4 = Vertice(43,2,4.5,0);
    vertice5 = Vertice(44,7,4.5,1);
    Vertice vertice6 = Vertice(45,3,4.5,2);

    vertici = {vertice1,vertice2,vertice3,vertice4,vertice5,vertice6};
    vertici=HeapSort(vertici,&Vertice::id);

    arco1 = Arco(0,5,vertice1,vertice2);
    arco2 = Arco(1,0,vertice2,vertice3);
    arco3 = Arco(2,6,vertice3,vertice1);
    arco4 = Arco(3,0,vertice2,vertice5);
    arco5 = Arco(4,6,vertice4,vertice3);
    arco6 = Arco(5,7,vertice4,vertice5);
    arco7 = Arco(6,0,vertice5,vertice3);
    Arco arco8 = Arco(7,7,vertice5,vertice6);
    Arco arco9 = Arco(8,8,vertice2,vertice6);

    archi = {arco1,arco2,arco3,arco4,arco5,arco6,arco7,arco8,arco9};
    archi=HeapSort(archi,&Arco::id);

    verticitriangolo0 = {vertice1,vertice2,vertice3};
    verticitriangolo1 = {vertice2,vertice5,vertice3};
    verticitriangolo2 = {vertice4,vertice3,vertice5};
    array<Vertice,3> verticitriangolo3 = {vertice5,vertice6,vertice2};

    architriangolo0 = {arco1,arco2,arco3};
    architriangolo1 = {arco2,arco4,arco7};
    architriangolo2 = {arco5,arco6,arco7};
    array<Arco,3> architriangolo3 = {arco4,arco8,arco9};

    triangolo0 = Triangle(0,verticitriangolo0,architriangolo0);
    triangolo1 = Triangle(1,verticitriangolo1,architriangolo1);
    triangolo2 = Triangle(2,verticitriangolo2,architriangolo2);
    Triangle triangolo3 = Triangle(3,verticitriangolo3,architriangolo3);

    triangoli = {triangolo0,triangolo1,triangolo2,triangolo3};
    triangoli = HeapSort(triangoli,&Triangle::area);

    mesh1 = Mesh(triangoli,archi,vertici);

    mesh1.CalcolaMatriceAdiacenza();
    mesh1.RaffinamentoStart();

    EXPECT_EQ(mesh1.vertici[0].id,47);
    EXPECT_EQ(mesh1.vertici[1].id,46);
    EXPECT_EQ(mesh1.archi[0].id,16);
    EXPECT_EQ(mesh1.archi[1].id,15);
    EXPECT_EQ(mesh1.archi[2].id,14);
    EXPECT_EQ(mesh1.archi[3].id,13);
    EXPECT_EQ(mesh1.archi[4].id,12);
    EXPECT_EQ(mesh1.archi[5].id,11);
    EXPECT_EQ(mesh1.archi[6].id,10);
    EXPECT_EQ(mesh1.archi[7].id,9);
    EXPECT_EQ(mesh1.triangoli[0].id,10);
    EXPECT_EQ(mesh1.triangoli[1].id,9);
    EXPECT_EQ(mesh1.triangoli[2].id,8);
    EXPECT_EQ(mesh1.triangoli[3].id,7);
    EXPECT_EQ(mesh1.triangoli[4].id,6);
    EXPECT_EQ(mesh1.triangoli[5].id,5);
    EXPECT_EQ(mesh1.triangoli[6].id,4);
}
*/
/*TEST(TestSort, TestMigliorePadreFigli)
{
    Vertice vertice1 = Vertice(41,0,1,3);
    Vertice vertice2 = Vertice(43,0,2,1);
    Vertice vertice3 = Vertice(15,0,0,0);

    vector<Vertice> v = {vertice1,vertice2,vertice3};

    unsigned int j = SortLibrary::MigliorePadreFigli(0,v,3,&Vertice::x);

    EXPECT_EQ(j,2);
}
*/
/*
TEST(TestSort,TestHeapSort)
{
    Vertice vertice1 = Vertice(15,1,0,0);
    Vertice vertice2 = Vertice(41,4,0,1);
    Vertice vertice3 = Vertice(1,6,1,0);
    Vertice vertice4 = Vertice(65,3,1,1);
    Vertice vertice5 = Vertice(83,2,2,0);

    vector<Vertice> v = {vertice3,vertice5,vertice1,vertice2,vertice4};
    v = SortLibrary::HeapSort(v,&Vertice::id);

    vector<Vertice> expectedV = {vertice5,vertice4,vertice2,vertice1,vertice3};

    EXPECT_EQ(v[0].id,expectedV[0].id);
    EXPECT_EQ(v[1].id,expectedV[1].id);
    EXPECT_EQ(v[2].id,expectedV[2].id);
    EXPECT_EQ(v[3].id,expectedV[3].id);
    EXPECT_EQ(v[4].id,expectedV[4].id);
}

Test sulla tolleranza va fatto con oggetti di tipo vertice, quindi sulle coordinate dei vertici
*/
#endif // __TEST_EMPTY_H
