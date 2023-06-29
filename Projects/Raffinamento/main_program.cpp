#include <iostream>
#include "Eigen/Eigen"
#include "map"
#include <chrono>
//#include <mpi.h>
//AGGIUNTA
#include <omp.h>

//file contenente il codice per il sorting
#include "sortingArea.hpp"
//file contente le funzioni per importare la mesh
#include "importa.hpp"
//file contente le classi
#include "empty_class.hpp"

using namespace std;
// ***************************************************************************
int main()
{

    //imposto una percentuale di triangoli da considerare
    double theta = 0.9;


    auto startProgram = chrono::high_resolution_clock::now();
    //inizializzo i vettori che conterranno tutte gli oggetti di classe Vertice, Arco e Triangle
    vector<ShapeLibrary::Vertice> vertici;
    vector<ShapeLibrary::Arco> archi;
    vector<ShapeLibrary::Triangle> triangoli;

    //faccio partire il cronometro
    auto startImport = chrono::high_resolution_clock::now();

    //importo i dati dal DataSet
    if(!ImportMesh(vertici,archi, triangoli))
    {
        return 1;
    }

    //fermo il cronometro
    auto endImport = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedImport = endImport - startImport;


    //------------------------------------------------------------

    //Definisco un oggetto di classe Mesh
    archi = SortLibrary::HeapSort(archi, &ShapeLibrary::Arco::id);
    vertici = SortLibrary::HeapSort(vertici, &ShapeLibrary::Vertice::id);
    ShapeLibrary::Mesh mesh = Mesh(triangoli, archi, vertici);

    // parte il cronometro
    auto startAdiacenza= chrono::high_resolution_clock::now();

    mesh.CalcolaMatriceAdiacenza();

    //si ferma il cronometro
    auto endAdiacenza = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedAdiacenza= endAdiacenza - startAdiacenza;
    //cout<<mesh.adiacenza<<endl;

    //-----------------------------------------------------------

    //mi salvo il numero iniziale di triangoli
    unsigned int numTriPartenza = triangoli.size();

    //raffino fino al raggiungimento della percentuale di raffinamento richiesta
    auto start1Raffinamento= chrono::high_resolution_clock::now();


    while(numTriPartenza>mesh.triangoli.size()*theta){
       // auto startRaffinamento= chrono::high_resolution_clock::now();

        mesh.RaffinamentoStart();

        //auto endRaffinamento = chrono::high_resolution_clock::now();
        //chrono::duration<double> elapsedRaffinamento = endRaffinamento - startRaffinamento;
        //cout<<mesh.triangoli.size()<<"\t"<<elapsedRaffinamento.count()<<endl;

        //cout<<"percentuale di raffinamento: "<<numTriPartenza*100/(mesh.triangoli.size()*theta)<<"%"<<endl;
    }
    auto end1Raffinamento = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed1Raffinamento = end1Raffinamento - start1Raffinamento;

    auto startExport= chrono::high_resolution_clock::now();
    //esporto i nuovi dati
    mesh.Esporta();
    auto endExport = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedExport = endExport - startExport;

    auto endProgram= chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedProgram = endProgram- startProgram;

    cout<<"\nTempo di import: "<<elapsedImport.count()<<" sec"<<endl;
    cout<<"Tempo di creazione matrice di Adiacenza: "<<elapsedAdiacenza.count()<<" sec"<<endl;
    cout<<"Tempo di Raffinamento: "<<elapsed1Raffinamento.count()<<" sec"<<endl;
    cout<<"Tempo di Raffinamento: "<<elapsedExport.count()<<" sec"<<endl;
    cout<<"Tempo di esecuzione totale: "<<elapsedProgram.count()<<"\t"<<mesh.triangoli.size()<<" sec"<<endl;
    //cout<<mesh.triangoli.size()<<endl;


    return 0;

}






