#include "empty_class.hpp"
#include <math.h>
#include "sortingArea.hpp"
#include <fstream>
#include <sstream>

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */
//i test vanno costruiti in un progetto a parte che è chiamato raffinamento_test

using namespace std;

namespace ShapeLibrary {



Vertice::Vertice(const unsigned int& id,  const unsigned int& marker, const double& x, const double& y): id(id), marker(marker),x(x), y(y) {}



Arco::Arco(const unsigned int& id,const unsigned int& marker, ShapeLibrary::Vertice& inizio,ShapeLibrary::Vertice& fine): id(id), marker(marker),inizio(inizio), fine(fine){}

void Arco::CalcolaLunghezza(){
    lunghezza = sqrt((inizio.x-fine.x)*(inizio.x-fine.x)+(inizio.y-fine.y)*(inizio.y-fine.y));
}

ShapeLibrary::Vertice Arco::CalcolaPuntoMedio(const unsigned int& newIdVert){
    //accedo alle coordinate dei punti che definisco il lato e calcolo il punto medio
    ShapeLibrary::Vertice puntoMedio;
    puntoMedio.id = newIdVert ;
    puntoMedio.marker = marker;
    puntoMedio.x = (inizio.x+fine.x)/2;
    puntoMedio.y = (inizio.y+fine.y)/2;
    return puntoMedio;

}




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

    //uso la formula di Gauss: semi somma delle coordinate y*(xprecedente -x successivo in senso antiorario)
    area = abs(Area);
}

void Triangle::isVicino(ShapeLibrary::Triangle& triangolo2,Eigen::SparseMatrix<unsigned int>& adiacenza){

    for(unsigned int i=0; i<3; i++)
    {  for (unsigned int j=0;j<3;j++)
        {   if (edges[i].id==triangolo2.edges[j].id)
            {
                //vicini.push_back(triangolo2);
                //triangolo2.vicini.push_back(*this);
                //cout<<edges[i].id<<endl;
                if ((adiacenza.coeff(this->id, triangolo2.id) == 0)||(adiacenza.coeff(triangolo2.id, this->id)==0))
                {
                    adiacenza.insert(this->id, triangolo2.id) = edges[i].id;
                    adiacenza.insert(triangolo2.id,this->id) = edges[i].id;
                }
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

}

tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco>  Triangle::Raffina(const unsigned int& newIdEdges, const unsigned int& newIdVert){
    //prendo gli archi e li ordino seleziando il più lungo
    vector<ShapeLibrary::Arco> arc ;
    cout<<"\narchi e lunghezza: "<<endl;
    for (unsigned int i = 0;i<3; i++)
    {
        edges[i].CalcolaLunghezza();
        cout<<edges[i].id<<"\t"<<edges[i].lunghezza<<endl;
        arc.push_back(edges[i]);
    }
    arc = SortLibrary::HeapSort(arc, &ShapeLibrary::Arco::lunghezza);
    cout<<"\nil lato più lungo: "<<arc[0].id<<endl;

    //selezionato il lato più lungo mi calcolo il punto medio
    ShapeLibrary::Vertice punto = arc[0].CalcolaPuntoMedio(newIdVert);
    ShapeLibrary::Arco arco;
    //cerco il vertice opposto
    arco.id = newIdEdges;
    arco.marker = 0;
    arco.inizio = VerticeOpposto(arc[0]);
    arco.fine = punto;
    cout<<"punto aggiunto: "<<punto.id<<endl;
    cout<<"Arco aggiunto: "<<arco.id<<"\t"<<arco.marker<<"\t"<<arco.inizio.id<<"\t"<<arco.fine.id<<endl;
    tuple<ShapeLibrary::Arco,ShapeLibrary::Vertice, ShapeLibrary::Arco> aggiunti(arco, punto, arc[0]);
    return aggiunti;
}




Mesh::Mesh(vector<ShapeLibrary::Triangle>& triangoli,vector<ShapeLibrary::Arco>& archi,vector<ShapeLibrary::Vertice>& vertici):triangoli(triangoli), archi(archi),vertici(vertici){}

void Mesh::CalcolaMatriceAdiacenza()
{
    //calcolo la matrice di adiacenza
    unsigned int numTri = triangoli.size();

    Eigen::SparseMatrix<unsigned int> adj(numTri,numTri);

    //cerco le adiacenze frai vari triangoli
    for (unsigned int i= 0; i< numTri-1; i++)
    {
        //seleziono un triangolo
        for (unsigned int j = i+1; j<numTri;j++)
        {     

            triangoli[i].isVicino(triangoli[j], adj);

        }
    }
    adiacenza = adj;

}

unsigned int Mesh::NuovoIdVertice()
{
    //TODO se ordinassi prima di chiamare la prima volta la mesh non avrei bisogno di fare questa cosa di ordinare
    vector<ShapeLibrary::Vertice> lista;
    lista = vertici;
    lista = SortLibrary::HeapSort(vertici, &ShapeLibrary::Vertice::id);
    //cout<<lista[0].id<<endl;
    return lista[0].id +1;
}

unsigned int Mesh::NuovoIdArco()
{
    //TODO se ordinassi prima di chiamare la prima volta la mesh non avrei bisogno di fare questa cosa di ordinare

    vector<ShapeLibrary::Arco> lista;
    lista = archi;
    lista = SortLibrary::HeapSort(archi, &ShapeLibrary::Arco::id);
    //cout<<lista[0].id<<endl;
    return lista[0].id +1;
}

unsigned int Mesh::NuovoIdTriangolo()
{
    //TODO se ordinassi prima di chiamare la prima volta la mesh non avrei bisogno di fare questa cosa di ordinare

    vector<ShapeLibrary::Triangle> lista;
    lista = triangoli;
    lista = SortLibrary::HeapSort(triangoli, &ShapeLibrary::Triangle::id);
    //cout<<lista[0].id<<endl;
    return lista[0].id +1;
}

ShapeLibrary::Arco Mesh::CercaArco(ShapeLibrary::Vertice& nodo1,ShapeLibrary::Vertice& nodo2)
{
    //cerco in tutta la lista quale arco è associato a questi nodi
    for(unsigned int i=0; i<archi.size();i++)
    {
        if ((archi[i].inizio.id == nodo1.id && archi[i].fine.id == nodo2.id) || (archi[i].inizio.id == nodo2.id && archi[i].fine.id == nodo1.id))
            return archi[i];
    }
}

void Mesh::InserisciTriangoli(unsigned int& newIdTriangle, ShapeLibrary::Arco& arco, ShapeLibrary::Vertice& nodo3)
{
    cout<<newIdTriangle<<endl;
    ShapeLibrary::Triangle triangolo;
    triangolo.id = newIdTriangle;
    //nuovo noodo
    triangolo.vertices[0] =arco.inizio;
    //vertice opposto
    triangolo.vertices[1] =arco.fine;
    //l'altro
    triangolo.vertices[2] =nodo3;


    triangolo.edges[0] =arco;
    //già esiste
    triangolo.edges[1] = CercaArco(arco.fine, nodo3);
    //devo crearlo
    ShapeLibrary::Arco arco2;
    arco2.id = NuovoIdArco();
    arco2.inizio = nodo3;
    arco2.fine = arco.inizio;
    arco2.marker = 0;
    archi.push_back(arco2);
    triangolo.edges[2] = arco2;

    triangoli.push_back(triangolo);
    //inserisci nella matrice di adiacenza
    adiacenza.conservativeResize(newIdTriangle + 1, newIdTriangle+1);

    for (unsigned int i = 0; i<(triangoli.size())-1; i++)
    {
       triangolo.isVicino(triangoli[i], adiacenza);
    }
    //cout<<"superato"<<endl;
}

unsigned int Mesh::Trova(unsigned int& col, unsigned int& valore)
{
    for (InnerIterator<SparseMatrix<unsigned int>> it(adiacenza, col); it; ++it) {
            if (it.value() == valore) {
                cout<<"\nTriangolo Adiancente ha id: "<<it.row()<<endl;
                return it.row() ;

            }

        }
    //se sono finito nell'else significa che non ci sono triangoli, quindi mi trovo al bordo, ritorno l'indice di colonna
    return col;

}

void Mesh::CancellaTriangolo(ShapeLibrary::Triangle& triangoloPartenza, ShapeLibrary::Arco& arcoVecchio){
    //devo per prima cosa cancellare l'arco in comune
    //per ora non cambio la matrice di adiacenza, ma forse converrebbe aggiornare le chiamate piuttosto che rifarla tutta
    for (unsigned int i = 0; i<archi.size();i++)
    {
        if (archi[i].id == arcoVecchio.id)
        {
            archi.erase(archi.begin()+i);
            cout<<"Cancellato l'arco: "<<arcoVecchio.id<<endl;
            break;
        }
    }
//cout<<"non c'è nessun arco da cancellare"<<endl;
    //cout<<"non c'è nessun arco da cancellare"<<endl;
    for (unsigned int i = 0; i<triangoli.size();i++)
    {
        if (triangoli[i].id == triangoloPartenza.id)
        {
            triangoli.erase(triangoli.begin()+i);
            cout<<"Cancellato il triangolo: "<<triangoloPartenza.id<<endl;
            break;
        }
    }
    //TODO cancella nella matrice di adiacenza
    //adiacenza.conservativeResize(newIdTriangle -1, newIdTriangle-1);
    //adiacenza.middleRows(triangoloPartenza.id, adiacenza.rows() - triangoloPartenza.id) = adiacenza.bottomRows(adiacenza.rows() - triangoloPartenza.id);
    //adiacenza.middleCols(triangoloPartenza.id, adiacenza.cols() - triangoloPartenza.id) = adiacenza.rightCols(adiacenza.cols() - triangoloPartenza.id);
    //adiacenza.pruned(triangoloPartenza.id,triangoloPartenza.id);
    /*for (InnerIterator<SparseMatrix<unsigned int>> it(adiacenza, triangoloPartenza.id); it; ++it) {
        cout<<it.value()<<endl;
            if (it.value() != 0) {
                cout<<"\nSto eliminando: "<<it.value()<<endl;
                adiacenza.coeffRef(triangoloPartenza.id, it.index()) = null;
                adiacenza.coeffRef(it.index(),triangoloPartenza.id) = null;

            }

        }*/
    //mi creo un matrice di appoggio,
    Eigen::SparseMatrix<unsigned int> adj(adiacenza.rows(),adiacenza.cols());
    //cout <<"\n"<< adiacenza.rows()<<"\t"<<adiacenza.cols()<<endl;
    for(unsigned int i = 0; i<adiacenza.rows()-1;i++)
    {   //cout<<"i: "<<i<<"j:"<<endl;
        if (i!=triangoloPartenza.id)
        {
        for (unsigned int j = i+1; j<adiacenza.cols(); j++)
        {
            if (j!=triangoloPartenza.id){
            //cout<<j<<endl;

            adj.insert(i, j) = adiacenza.coeffRef(i,j);
            adj.insert(j, i) = adiacenza.coeffRef(j,i);
            }

        }
        }
    }
    adiacenza = adj;


}

void Mesh::Verifica(ShapeLibrary::Triangle& triangolo, ShapeLibrary::Arco& arcoNuovo, ShapeLibrary::Vertice& nodoNuovo, ShapeLibrary::Arco& arcoVecchio){

    //voglio verificare se l'arco e il nodo che ho creato hanno rotto la mia mesh
    //parto quindi dal triangolo che ho raffinato, se esiste, il triangolo adiacente al lato che ho modicato, faccio quindi accesso alla matrice di adiacenza

    unsigned int idTri;
    unsigned int col = triangolo.id;
    unsigned int valore = arcoVecchio.id;

    idTri = Trova(col, valore);
    //cout<<"id del triangolo adiancente:"<<idTri<<endl;
    if (idTri == col)
    {
        //se non ho vicini sono sul bordo e posso terminare il raffinamento
        cout<<"sono sul bordo, raffinamento completato"<<endl;
    }

    else{

        //adesso dovrei raffinare il triangolo adiacente
        ShapeLibrary::Triangle TriangAdiace =id2object(idTri, triangoli);

        //raffino e mi salvo il nuovo arco e il nuovo punto
        unsigned int newIdEdges = NuovoIdArco();
        unsigned int newIdVert = NuovoIdVertice();
        tuple<ShapeLibrary::Arco, ShapeLibrary::Vertice,ShapeLibrary::Arco> aggiunti(TriangAdiace.Raffina(newIdEdges, newIdVert));

        ShapeLibrary::Arco arcoNuovo2 = get<0>(aggiunti);
        ShapeLibrary::Vertice puntoNuovo2 = get<1>(aggiunti);
        ShapeLibrary::Arco arcoLungo= get<2>(aggiunti);

        //aggiungo sicuramente l'arco
        archi.insert(archi.begin(),arcoNuovo2);

        //devo verificare se il punto nuovo medio calcolato coincide con quello che sto controllando oppure no
        if (arcoLungo.id ==arcoVecchio.id)
        {
            //mi salvo solo il nuovo arco
            cout<<"\nwe, ho già finito di raffinare"<<endl;

            //adesso dovrei anche aggiungere i due triangoli che si sono formati
            unsigned int newIdTriangle = NuovoIdTriangolo();
            //TODO
            InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.inizio );
            newIdTriangle +=1;
            InserisciTriangoli(newIdTriangle,arcoNuovo2, arcoLungo.fine );
        }
        else{
            //se non coincidono, allora devo unire i punti medi

            //devo congiungere il punto medio con il vecchio punto medio
            ShapeLibrary::Arco arcoDiMezzo;
            arcoDiMezzo.id = newIdEdges+1;
            arcoDiMezzo.marker = 0;
            arcoDiMezzo.inizio = nodoNuovo ;
            arcoDiMezzo.fine = puntoNuovo2;

            //aggiungo il nuovo arco nella lista
            archi.insert(archi.begin(),arcoDiMezzo);

            unsigned int newIdTriangle = NuovoIdTriangolo();
            InserisciTriangoli(newIdTriangle, arcoDiMezzo, arcoVecchio.inizio);
            newIdTriangle +=1;
            InserisciTriangoli(newIdTriangle,arcoDiMezzo, arcoVecchio.fine );
            newIdTriangle +=1;
            if (arcoLungo.inizio.id ==arcoVecchio.inizio.id ||arcoLungo.inizio.id ==arcoVecchio.fine.id)
                InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.fine);
            else
                InserisciTriangoli(newIdTriangle, arcoNuovo2, arcoLungo.inizio);


            //verifico che queste aggiunte non abbiano causato interferenze
            Verifica(TriangAdiace,arcoNuovo2,puntoNuovo2, arcoLungo);
            CancellaTriangolo(TriangAdiace, arcoVecchio);

            }
        //posso cancellare il triangolo di partenza
        cout<<"Sto per cancellare: "<<triangolo.id<<"\t   e\t"<<arcoVecchio.id<<endl;
        CancellaTriangolo(TriangAdiace, arcoLungo);
    }



}



void Mesh::RaffinamentoStart(){
    //calcolo le aree dei triangoli
    //cout<<"\nid e aree:"<<endl;

    for (unsigned int i=0; i<triangoli.size();i++)
    {
        //calcolo l'area di tutti i triangoli
        triangoli[i].CalcolaArea();
        //cout<<triangoli[i].id<<"\t"<<triangoli[i].area<<endl;
    }
    //cout<<endl;

    //ordino i triangoli per area
    triangoli = SortLibrary::HeapSort(triangoli, &ShapeLibrary::Triangle::area);
    ShapeLibrary::Triangle triangoloPartenza = triangoli[0];
    cout<<"triangolo con area più grande:\n"<<triangoloPartenza.id<<"\t"<<triangoloPartenza.area<<endl;


    //definisco i nuovi id per il punto e l'arco nuovo che si formerrano dopo il raffinamento
    unsigned int newIdEdges = NuovoIdArco();
    unsigned int newIdVert = NuovoIdVertice();
    //raffino il triangolo più grande e mi salvo il nuovo arco e il nuovo punto
    tuple<ShapeLibrary::Arco, ShapeLibrary::Vertice,ShapeLibrary::Arco> aggiunti(triangoloPartenza.Raffina(newIdEdges, newIdVert));
    ShapeLibrary::Arco arcoNuovo = get<0>(aggiunti);
    ShapeLibrary::Vertice puntoNuovo = get<1>(aggiunti);
    ShapeLibrary::Arco arcoAdiacente= get<2>(aggiunti);

    cout<<"arco Nuovo: "<<arcoNuovo.id<<"\t"<<"punto Nuovo: "<<puntoNuovo.id<<endl;

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
    Verifica(triangoloPartenza, arcoNuovo, puntoNuovo, arcoAdiacente);

    //posso cancellare il triangolo di partenza
    //TODO definisci un metodo per cancellare dalla lista il triangolo di partenza
    CancellaTriangolo(triangoloPartenza, arcoAdiacente);



}

void Mesh::Esporta()
{
    /// Open File
    ofstream file;
    file.open("./cell0DNuovo.csv");

    if (file.fail())
    {
      cerr<< "file open failed"<< endl;
    }

    for (unsigned int i = 0; i<vertici.size();i++) {
        file<<vertici[i].id<<" "<<vertici[i].marker<<" "<<vertici[i].x<<" "<<vertici[i].y<<endl;
       }

    /// Close File
    file.close();

    /// Open File
    ofstream file1;
    file1.open("./cell1DNuovo.csv");

    if (file1.fail())
    {
      cerr<< "file open failed"<< endl;
    }

    for (unsigned int i = 0; i<archi.size();i++) {
        file1<<archi[i].id<<" "<<archi[i].marker<<" "<<archi[i].inizio.x<<" "<<archi[i].inizio.y<<" "<<archi[i].fine.x<<" "<<archi[i].fine.y<<endl;
       }

    /// Close File
    file1.close();



}

}




