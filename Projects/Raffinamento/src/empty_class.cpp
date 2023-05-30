#include "empty_class.hpp"
#include <math.h>
#include "sortingArea.hpp"

/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */
//i test vanno costruiti in un progetto a parte che è chiamato raffinamento_test

using namespace std;

namespace ShapeLibrary {

inline double distanza(const double& x1, const double& y1,const double& x2, const double& y2)
{
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

//il costruttore di triangoli prende in input le info del file e le salva, in più deriva le coordinate dai vertici
Triangle::Triangle(unsigned int& id, array<unsigned int, 3>& vertices, array<unsigned int, 3>& edges, TriangularMesh& mesh):
    id(id),
    vertices(vertices),
    edges(edges),
    mesh(mesh){

    //associo i vertici alle coordinate: prima riga le x, seconda riga le y
    Eigen::MatrixXd coordinates = Eigen::MatrixXd::Zero(2,3);
    for (unsigned int i=0; i<3;i++){
        unsigned int j = vertices[i];
        float coordx =mesh.Cell0DCoordinates[j][0];
        float coordy =mesh.Cell0DCoordinates[j][1];
        coordinates(0,i) = coordx;
        coordinates(1,i) = coordy;
        }
    coordinate = coordinates;

}

//definisco il metodo per il calcolo delle aree
double Triangle::Area()
{
    //devo tenere conto che la matrice con le coordinate è già salvata, quindi posso farne accesso anche senza chiamarla esplicitamente

    double area = 0.0;
    //unsigned int righe = points.rows();
    unsigned int colonne  = coordinate.cols();
    for (unsigned int j=0; j< colonne; j++)
    {
        //y del punto
        double y_att = coordinate(1,j);
        //x precedente
        double x_pre = coordinate(0,((j-1+colonne)%(colonne)));
        //x successivo
        double x_succ = coordinate(0,((j+1+colonne)%(colonne)));
        area += y_att*(x_pre-x_succ);
    };
    area = 0.5*area;

    //uso la formula di Gauss: semi somma delle coordinate y*(xprecedente -x successivo in senso antiorario)
    return abs(area);
}


int Triangle::Vicini(ShapeLibrary::Triangle& triangolo2)
{
    //partendo dal presupposto che due triangolo possono avere al massimo un lato in comune:
    //controllo se il triangolo1 e il 2 sono adiacenti verificando se hanno un lato in comune

    //OSSERVAZIONE: anche se non dovrebbe mai capitare, secondo me sarebbe opportuno verificare che non vengano avanzate proposte di confronto fra due triangoli uguali
    //dovremmo quindi controllare che l'id del triangolo che stiamo valutando sia diverso dall'id del traingolo2
    for(unsigned int i=0; i<3; i++)
    {
        int lato1= edges[i];

        for (unsigned int j=0;j<3;j++)
        {
            int lato2= triangolo2.edges[j];
            if (lato2==lato1)
                return lato2;
        }
    }
    //ritorno un valore a caso che non sia il nome di uno degli archi
    return -4;
}



Vector2i Triangle::Raffina()
{
    //sono nel triangolo, voglio prendere il lato più lungo, faccio come ho fatto per le aree
    //definisco una mappa che associa l'id del lato alla sua lunghezza
    map<int, double> lati = {};
    map<int, Vector2d> medi = {};
    //v vettore temporaneo per ordinare le lunghezze
    //per esempio qui sarebbe carino se riuscissimo ad evitare di creare un vettore così e passare direttamente a heapSort un vettore di aree (però per ora così funziona)
    vector<double> v= {};



    //potrei pensare, quando costruisco il triangolo di creare una tabella lati dove salvare le coordinate per evitare di doverle creare tutte le volte




    //calcolo le lunghezze dei lati
    for(unsigned int i=0; i< 3; i++)
    {
        Vector2d punti;
        //cout<<i<<"\t"<<(i+1)%3<<endl;
        double x1=coordinate(0,i);
        double y1=coordinate(1,i);
        double x2=coordinate(0,(i+1)%3);
        double y2=coordinate(1,(i+1)%3);
        double lunghezza = distanza(x1,y1,x2,y2);
        //double xM; yM;
        punti(0) = (x2+x1)/2;
        punti(1) = (y2+y1)/2;
        //inserisco id e area nella mappa, solo l'area nella lista
        lati.insert({edges[i], lunghezza});
        v.push_back(lunghezza);
        medi.insert({edges[i], punti});
        //cout<<edges[i]<<"\t"<<lunghezza<<"\t"<<vertices[i]<<"\t"<<vertices[(i+1)%3]<<endl;
        //cout<<x1<<"\t"<<y1<<"\t"<<x2<<"\t"<<y2<<"\t"<<punti(0)<<"\t"<<punti(1)<<endl;
    }
    //cout<<endl;

    v=SortLibrary::HeapSort<double>(v);
    //cerco l'id del primo triangolo
    unsigned int idLatoMaggiore;
    for (const auto& coppia : lati) {
            if (coppia.second == v[0]) {
                idLatoMaggiore = coppia.first;
                break;
            }
        }
    cout<<idLatoMaggiore<<endl;




    //abbiamo trovato le coordinate del punto medio, ora dobbiamo salvarle
    //ci serve un (id, marker, coordinate)


    //dobbiamo salvare il nuovo lato, quindi prendere il vertice non compreso nel lato
    //accediamo tramite l'id alla mesh e cicliamo fra i vertici
    unsigned int idVerticeOpposto;
    for (unsigned int i=0;i<3;i++)
    {
        bool flag = false;
        for (unsigned int j=0;j<2;j++)
        {
            //cout<<vertices[i]<<"\t"<<mesh.Cell1DVertices[idLatoMaggiore][j]<<endl;
            if(vertices[i] == mesh.Cell1DVertices[idLatoMaggiore][j])
            {
                //cout<<"qui"<<endl;
                flag = true;
                break;
            }
            //cout<<"qua"<<endl;

        }
        if (flag == false)
        {
            idVerticeOpposto = vertices[i];
            break;
        }

    }
   cout<<idVerticeOpposto<<endl;

   //definisco i nuovi id
   unsigned int idArcoNuovo = mesh.NumberCell1D;
   unsigned int idVerticeNuovo = mesh.NumberCell0D;
   //aggiorniamo il numero di archi e di vertici presenti nella struct

   mesh.NumberCell1D +=1;
   mesh.NumberCell0D +=1;



   mesh.Cell0DId.push_back(idVerticeNuovo);

   mesh.Cell0DCoordinates.push_back(medi[idLatoMaggiore]);

   Vector2i puntinuovi;
   puntinuovi(0) = idVerticeOpposto;
   puntinuovi(1) = idVerticeNuovo;


   mesh.Cell1DId.push_back(idArcoNuovo);
   mesh.Cell1DVertices.push_back(puntinuovi);

  cout<<idLatoMaggiore<<"\t"<<idVerticeNuovo<<endl;
  Vector2i result ;
  result(0) = idLatoMaggiore;
  result(1) = idVerticeNuovo;
  return result;
 }










//gli passo una lista di oggetti della classe triangolo e ne deriva la matrice di adiacenza
Mesh::Mesh(vector<ShapeLibrary::Triangle>& lista): lista(lista){
///si può parallelizzare
    //calcolo la matrice di adiacenza
    unsigned int numTri = lista.size();

    Eigen::SparseMatrix<double> adj(numTri,numTri);

    //cerco le adiacenze frai vari triangoli
    for (unsigned int i= 0; i< numTri-1; i++)
    {
        //seleziono un triangolo
        for (unsigned int j = i+1; j<numTri;j++)
        {
            //cerco tutti i triangoli che confinano
            int link = lista[i].Vicini(lista[j]);
            if (link >=0)
            {
                //cout<<link<<endl;
                adj.insert(lista[i].id, lista[j].id) = link;
                adj.insert(lista[j].id, lista[i].id) = link;
            }
        }
    }
    adiacenza = adj;

}
/*    Vector2i aggiunta  = lista[idPartenza].Raffina();
    //adesso ho il punto aggiunto, verifico se è ben posto
    mesh.Verifica(aggiunta);*/

void Mesh::Verifica(unsigned int& idPartenza, Vector2i& aggiunta )
{
    //cerco il triangolo vicino al triangolo di partenza avente l'id del lato maggiore
    InnerIterator<SparseMatrix<double>> it(adiacenza, idPartenza);
        unsigned int idTriAdiacente = 0;
        while (it && idTriAdiacente == 0 && idTriAdiacente!=idPartenza) {
            if (it.value() == aggiunta[0]) {
                idTriAdiacente = it.row();
            }
            ++it;
        }
    cout<<idTriAdiacente<<"\t"<<idPartenza<<endl;
    //ora siamo nel triangolo adiacente
    Vector2i puntiNuovi = lista[idTriAdiacente].Raffina();
    //proviamo a congiungere il nuovo punto del secondo triangolo con il primo
    double x1 =lista[idTriAdiacente].mesh.Cell0DCoordinates[idTriAdiacente][0];
    double y1 =lista[idTriAdiacente].mesh.Cell0DCoordinates[idTriAdiacente][1];
    double x2 =lista[idPartenza].mesh.Cell0DCoordinates[idPartenza][0];
    double y2 =lista[idPartenza].mesh.Cell0DCoordinates[idPartenza][1];


    cout<<x1<<"\t"<<x2<<"\t"<<y1<<"\t"<<y2<<endl;
    //ci dobbiamo salvare le coordinate
    if (abs(x1-x2)==0 && abs(y1-y2)==0)
    {   cout<<"qui"<<endl;
        return;}
    else
    {
        cout<<"qua"<<endl;
        //congiungiamo i due punti e richiamiamo verifica
        //dovremmo salvare il nuovo e aggiungerla alla mesh(struct)

        //chiamiamo di nuovo verifica
        Verifica(idTriAdiacente, puntiNuovi);

    }
}


}




