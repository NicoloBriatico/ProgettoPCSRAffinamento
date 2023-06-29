#include "empty_class.hpp"
#include <math.h>
#include "sortingArea.hpp"
#include <fstream>
#include <sstream>

using namespace std;

namespace ShapeLibrary {

Vertice::Vertice(const unsigned int& id,  const unsigned int& marker, const double& x, const double& y): id(id), marker(marker),x(x), y(y) {}

// ***************************************************************************

Arco::Arco(const unsigned int& id,const unsigned int& marker, ShapeLibrary::Vertice& inizio,ShapeLibrary::Vertice& fine): id(id), marker(marker),inizio(inizio), fine(fine){

    lunghezza = sqrt((inizio.x-fine.x)*(inizio.x-fine.x)+(inizio.y-fine.y)*(inizio.y-fine.y));
}

void Arco::CalcolaLunghezza(){
    lunghezza = sqrt((inizio.x-fine.x)*(inizio.x-fine.x)+(inizio.y-fine.y)*(inizio.y-fine.y));
}

ShapeLibrary::Vertice Arco::CalcolaPuntoMedio(const unsigned int& newIdVert){
    ShapeLibrary::Vertice puntoMedio;
    puntoMedio.id = newIdVert ;
    puntoMedio.marker = marker;
    puntoMedio.x = (inizio.x+fine.x)/2;
    puntoMedio.y = (inizio.y+fine.y)/2;
    return puntoMedio;
}

// ***************************************************************************

Triangle::Triangle(const unsigned int& id,array<ShapeLibrary::Vertice,3>& vertices,array<ShapeLibrary::Arco,3>& edges): id(id), vertices(vertices),edges(edges){}

void Triangle::CalcolaArea(){
    //calcolo l'area con il metodo di Gauss
    double Area = 0.0;

    for (unsigned int j=0; j<3; j++)
    {
        //y del punto
        double y_att = vertices[j].y;
        //x precedente
        double x_pre = vertices[(j-1+3)%3].x;
        //x successivo
        double x_succ = vertices[(j+1+3)%3].x;
        Area += y_att*(x_pre-x_succ);
    };
    Area *= 0.5;
    area = abs(Area);
}

void Triangle::isVicino(ShapeLibrary::Triangle& triangolo2,Eigen::SparseMatrix<unsigned int>& adiacenza){

    for(unsigned int i=0; i<3; i++)
    {  for (unsigned int j=0;j<3;j++)
        {   if (edges[i].id==triangolo2.edges[j].id)
            {
                //cout<<id<<"\t"<<triangolo2.id<<endl;
                if ((adiacenza.coeff(id, triangolo2.id) == 0)||(adiacenza.coeff(triangolo2.id, id)== 0))
                {
                    //cout<<id<<"\t"<<triangolo2.id<<"\t"<<edges[i].id<<endl;
                    adiacenza.insert(id, triangolo2.id) = edges[i].id+1;
                    adiacenza.insert(triangolo2.id,id) = edges[i].id+1;
                }
                return;
            }
        }
    }
}

ShapeLibrary::Vertice Triangle::VerticeOpposto(ShapeLibrary::Arco& arco){
    for (unsigned int i=0;i<3;i++)
    {
        if (vertices[i].id != arco.inizio.id && vertices[i].id != arco.fine.id)
            return vertices[i];
    }
    return arco.inizio;
}

tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco>  Triangle::Raffina(const unsigned int& newIdEdges, const unsigned int& newIdVert){
    //prendo gli archi e li ordino seleziando il più lungo
    vector<ShapeLibrary::Arco> arc ;
    //cout<<"\narchi e lunghezza: "<<endl;

    
    for (unsigned int i = 0;i<3; i++)
    {
        edges[i].CalcolaLunghezza();
        //cout<<edges[i].id<<"\t"<<edges[i].lunghezza<<endl;
        arc.push_back(edges[i]);
    }
    arc = SortLibrary::HeapSort(arc, &ShapeLibrary::Arco::lunghezza);

    //cout<<"\nil lato più lungo: "<<arc[0].id<<endl;

    //selezionato il lato più lungo mi calcolo il punto medio
    ShapeLibrary::Vertice punto = arc[0].CalcolaPuntoMedio(newIdVert);

    ShapeLibrary::Arco arco;
    arco.id = newIdEdges;
    arco.marker = 0;

    //cerco il vertice opposto
    if(VerticeOpposto(arc[0]).id != arc[0].inizio.id)
        arco.inizio = VerticeOpposto(arc[0]);
    else
        cerr<<"errore di archi"<<endl;

    arco.fine = punto;

    //cout<<"punto aggiunto: "<<punto.id<<endl;
    //cout<<"Arco aggiunto: "<<arco.id<<"\t"<<arco.marker<<"\t"<<arco.inizio.id<<"\t"<<arco.fine.id<<endl;

    tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco> aggiunti(arco, punto, arc[0]);
    return aggiunti;
}

// ***************************************************************************

Mesh::Mesh(vector<ShapeLibrary::Triangle>& triangoli,vector<ShapeLibrary::Arco>& archi,vector<ShapeLibrary::Vertice>& vertici):triangoli(triangoli), archi(archi),vertici(vertici){}

void Mesh::CalcolaMatriceAdiacenza()
{
    //calcolo la matrice di adiacenza
    unsigned int numTri = triangoli.size();

    Eigen::SparseMatrix<unsigned int> adj(numTri,numTri);

    //TODO si può parallelizzare
    //cerco le adiacenze frai vari triangoli
    for (unsigned int i= 0; i< numTri-1; i++)
    {
        //seleziono un triangolo
        for (unsigned int j = i+1; j<numTri;j++)
            triangoli[i].isVicino(triangoli[j], adj);
    }
    adiacenza = adj;
}

inline unsigned int Mesh::NuovoIdVertice()
{
    return vertici[0].id +1;
}

inline unsigned int Mesh::NuovoIdArco()
{
    return archi[0].id +1;
}

inline unsigned int Mesh::NuovoIdTriangolo()
{
    //la lista di triangoli viene ordinata per aree, ma a me serve averla ordina per id
    vector<ShapeLibrary::Triangle> lista;
    lista = triangoli;
    lista = SortLibrary::HeapSort(triangoli, &ShapeLibrary::Triangle::id);
    return lista[0].id +1;
}

ShapeLibrary::Arco Mesh::CercaArco(ShapeLibrary::Vertice& nodo1,ShapeLibrary::Vertice& nodo2)
{
    //TODO si può parallelizzare
    //cerco in tutta la lista quale arco è associato a questi nodi
    for(unsigned int i=0; i<archi.size();i++)
    {
        if ((archi[i].inizio.id == nodo1.id && archi[i].fine.id == nodo2.id)||(archi[i].inizio.id == nodo2.id && archi[i].fine.id == nodo1.id))
            return archi[i];
    }

    //se non esiste, me lo creo
    ShapeLibrary::Arco arco2;
    arco2.id = NuovoIdArco();


    //se hanno lo stesso id
    if(nodo1.marker == nodo2.marker)
            arco2.marker = nodo1.marker;
    //se uno dei due è un nodo di angolo
    else if ((nodo1.marker == 1)||(nodo1.marker == 2)||(nodo1.marker == 3)||(nodo1.marker == 4))
        arco2.marker = nodo2.marker;
    else if ((nodo2.marker == 1)||(nodo2.marker == 2)||(nodo2.marker == 3)||(nodo2.marker == 4))
        arco2.marker = nodo1.marker;
    //se uno dei due è interno
    else if ((nodo1.marker = 0)||(nodo2.marker = 0))
            arco2.marker = 0;
    else
        arco2.marker = 0;



    arco2.inizio = nodo1;
    arco2.fine = nodo2;

    archi.insert(archi.begin(),arco2);

    return arco2;
}

void Mesh::InserisciTriangoli(unsigned int& newIdTriangle, ShapeLibrary::Arco& arco, ShapeLibrary::Vertice& nodo3)
{

    ShapeLibrary::Triangle triangolo;
    triangolo.id = newIdTriangle;
    //nuovo noodo
    triangolo.vertices[0] =arco.inizio;
    //vertice opposto
    triangolo.vertices[1] =arco.fine;
    //l'altro
    triangolo.vertices[2] =nodo3;

    triangolo.edges[0] =arco;
    triangolo.edges[1] = CercaArco(arco.fine, nodo3);
    triangolo.edges[2] = CercaArco(nodo3, arco.inizio);

    triangoli.insert(triangoli.begin(),triangolo);

    //aumento la dimensione della matrice di adiacenza
    adiacenza.conservativeResize(newIdTriangle + 1, newIdTriangle+1);

    //TODO si può parallelizzare
    //aggiungo i triangoli vicini al nuovo triangolo
    for (unsigned int i = 1; i<triangoli.size(); i++)
        triangolo.isVicino(triangoli[i], adiacenza);
}

unsigned int Mesh::Trova(unsigned int& col, unsigned int& valore)
{

    //TODO si può parallelizzare
    for (InnerIterator<SparseMatrix<unsigned int>> it(adiacenza, col); it; ++it) {
        if ((it.value()-1) == valore) {
            //cout<<"\nTriangolo Adiancente ha id: "<<it.row()<<endl;
            return it.row() ;
        }
    }
    //non ci sono triangoli, quindi mi trovo al bordo, ritorno l'indice di colonna
    return col;

}

void Mesh::CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza, ShapeLibrary::Arco& arcoVecchio){
    //TODO si può parallelizzare
    //cancello l'arco in comune
    for (unsigned int i = 0; i<archi.size();i++)
    {
        if (archi[i].id == arcoVecchio.id)
        {
            archi.erase(archi.begin()+i);
            //cout<<"Cancellato l'arco: "<<arcoVecchio.id<<endl;
            break;
        }
    }

    //TODO si può parallelizzare
    //cancello il triangolo che è stato raffinato
    for (unsigned int i = 0; i<triangoli.size();i++)
    {
        if (triangoli[i].id == triangoloPartenza.id)
        {
            triangoli.erase(triangoli.begin()+i);
            //cout<<"Cancellato il triangolo: "<<triangoloPartenza.id<<endl;
            break;
        }
    }

    //aggiorno la matrice di adiacenza
    Eigen::SparseMatrix<unsigned int> adj(adiacenza.rows(),adiacenza.cols());
    //TODO si può parallelizzare
    for(unsigned int i = 0; i<adiacenza.rows()-1;i++)
    {   if (i!=triangoloPartenza.id)
        {   for (unsigned int j = i+1; j<adiacenza.cols(); j++)
            {   if (j!=triangoloPartenza.id){
                    if(adiacenza.coeffRef(i,j)!=0){
                        adj.insert(i, j) = adiacenza.coeffRef(i,j);
                        adj.insert(j, i) = adiacenza.coeffRef(j,i);
                    }
                }
            }
        }
    }

    adiacenza = adj;
}

void Mesh::Verifica(ShapeLibrary::Triangle& triangolo,  ShapeLibrary::Vertice& nodoNuovo, ShapeLibrary::Arco& arcoVecchio){

    //cerco un triangolo adiacente al lato che ho raffinato
    unsigned int idTri;
    unsigned int col = triangolo.id;
    unsigned int valore = arcoVecchio.id;
    //cout<<valore<<"\t"<<col<<endl;

    //idTri = Trova(col, valore);

    if (arcoVecchio.marker!=0)//(idTri == col)
    {
        //se non ho vicini sono sul bordo e posso terminare il raffinamento
        //cout<<"sono sul bordo, raffinamento completato"<<endl;
    }

    else{
        idTri = Trova(col, valore);
        //cout<<"il triangolo "<<idTri<<" è adiacente a "<<col<<endl;
        if (idTri == col)
            return;
        //raffino il triangolo adiacente
        ShapeLibrary::Triangle TriangAdiace =id2object(idTri, triangoli);

        unsigned int newIdEdges = NuovoIdArco();
        unsigned int newIdVert = NuovoIdVertice();
        tuple<ShapeLibrary::Arco, ShapeLibrary::Vertice,ShapeLibrary::Arco> aggiunti(TriangAdiace.Raffina(newIdEdges, newIdVert));

        ShapeLibrary::Arco arcoNuovo2 = get<0>(aggiunti);
        ShapeLibrary::Vertice puntoNuovo2 = get<1>(aggiunti);
        ShapeLibrary::Arco arcoLungo= get<2>(aggiunti);

        //devo verificare se il punto nuovo medio calcolato coincide con quello che sto controllando oppure no
        if (arcoLungo.id ==arcoVecchio.id)
        {
            //cout<<"\nwe, ho già finito di raffinare"<<endl;
            arcoNuovo2.fine = nodoNuovo;
            archi.insert(archi.begin(),arcoNuovo2);
            //aggiungo i due triangoli che si sono formati
            unsigned int newIdTriangle = NuovoIdTriangolo();

            InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.inizio );
            newIdTriangle +=1;
            InserisciTriangoli(newIdTriangle,arcoNuovo2, arcoLungo.fine );
        }
        else{

            //se non coincidono, allora salvo il nuovo punto
            vertici.insert(vertici.begin(), puntoNuovo2);
            archi.insert(archi.begin(),arcoNuovo2);
            //congiungo i due punti
            ShapeLibrary::Arco arcoDiMezzo;
            arcoDiMezzo.id = newIdEdges+1;
            arcoDiMezzo.marker = 0;
            arcoDiMezzo.inizio = nodoNuovo;
            arcoDiMezzo.fine = puntoNuovo2;

            //aggiungo il nuovo arco nella lista
            archi.insert(archi.begin(),arcoDiMezzo);

            //aggiungo i nuovi triangoli
            unsigned int newIdTriangle = NuovoIdTriangolo();
            InserisciTriangoli(newIdTriangle, arcoDiMezzo, arcoVecchio.inizio);
            newIdTriangle +=1;
            InserisciTriangoli(newIdTriangle,arcoDiMezzo, arcoVecchio.fine );
            newIdTriangle +=1;

            if (arcoLungo.inizio.id ==arcoVecchio.inizio.id ||arcoLungo.inizio.id ==arcoVecchio.fine.id)
                InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.fine);
            else if (arcoLungo.fine.id ==arcoVecchio.inizio.id ||arcoLungo.fine.id ==arcoVecchio.fine.id)
                InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.inizio);

            //verifico che queste aggiunte non abbiano causato interferenze
            Verifica(TriangAdiace, puntoNuovo2, arcoLungo);



        }

        //cancello il triangolo di partenza
        //cout<<"Sto per cancellare: "<<triangolo.id<<"\t   e\t"<<arcoVecchio.id<<endl;
        CancellaTriangolo(TriangAdiace, arcoLungo);
    }
}

void Mesh::RaffinamentoStart(){

    //TODO parallelizza
    //calcolo le aree dei triangoli
    for (unsigned int i=0; i<triangoli.size();i++)
        triangoli[i].CalcolaArea();

    //ordino i triangoli per area
    triangoli = SortLibrary::HeapSort(triangoli, &ShapeLibrary::Triangle::area);
    ShapeLibrary::Triangle triangoloPartenza = triangoli[0];

    //cout<<"triangolo con area più grande:\n"<<triangoloPartenza.id<<"\t"<<triangoloPartenza.area<<endl;

    //definisco i nuovi id per il punto e l'arco nuovo che si formerrano dopo il raffinamento
    unsigned int newIdEdges = NuovoIdArco();
    unsigned int newIdVert = NuovoIdVertice();

    //raffino il triangolo più grande e mi salvo il nuovo arco e il nuovo punto
    tuple<ShapeLibrary::Arco, ShapeLibrary::Vertice,ShapeLibrary::Arco> aggiunti(triangoloPartenza.Raffina(newIdEdges, newIdVert));
    ShapeLibrary::Arco arcoNuovo = get<0>(aggiunti);
    ShapeLibrary::Vertice puntoNuovo = get<1>(aggiunti);
    ShapeLibrary::Arco arcoAdiacente= get<2>(aggiunti);

    //cout<<"arco Nuovo: "<<arcoNuovo.id<<"\t"<<"punto Nuovo: "<<puntoNuovo.id<<endl;

    //aggiungo il punto alla lista di punti e l'arco alla lista di archi
    archi.insert(archi.begin(),arcoNuovo);
    vertici.insert(vertici.begin(),puntoNuovo);

    //aggiungo i due tringoli che si sono formati
    unsigned int newIdTriangle = NuovoIdTriangolo();

    //creo un metodo crea triangoli gli passo il nuovo id e una lista di punti
    InserisciTriangoli(newIdTriangle, arcoNuovo,arcoAdiacente.inizio);
    newIdTriangle +=1;
    InserisciTriangoli(newIdTriangle, arcoNuovo,arcoAdiacente.fine);

    //verifico se queste aggiunte hanno rovinato la mesh
    Verifica(triangoloPartenza, puntoNuovo, arcoAdiacente);

    //cancello il triangolo di partenza
    CancellaTriangolo(triangoloPartenza, arcoAdiacente);
}

void Mesh::Esporta()
{
    //apro il file
    ofstream file;
    file.open("./cell0DNuovo.csv");

    if (file.fail())
        cerr<< "file open failed"<< endl;

    for (unsigned int i = 0; i<vertici.size();i++)
        file<<vertici[i].id<<" "<<vertici[i].marker<<" "<<vertici[i].x<<" "<<vertici[i].y<<endl;


    //chiudo il file
    file.close();

    //apro il file
    ofstream file1;
    file1.open("./cell1DNuovo.csv");

    if (file1.fail())
        cerr<< "file open failed"<< endl;

    for (unsigned int i = 0; i<archi.size();i++)
        file1<<archi[i].id<<" "<<archi[i].marker<<" "<<archi[i].inizio.x<<" "<<archi[i].inizio.y<<" "<<archi[i].fine.x<<" "<<archi[i].fine.y<<endl;

    //chiudo il file
    file1.close();
}

}




