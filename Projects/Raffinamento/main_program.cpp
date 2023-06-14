#include <iostream>
#include "Eigen/Eigen"
#include "map"
#include <chrono>
//#include <mpi.h>
//AGGIUNTA
#include <omp.h>

//file contenente il codice per il sorting
#include "sortingArea.hpp"
//file contenente la definizione delle tolleranze
#include "tolleranza.hpp"
//file contente le funzioni per importare la mesh
#include "importa.hpp"
//file contente le classi
#include "empty_class.hpp"

using namespace std;
// ***************************************************************************
int main()
{
    /*
     *
     * ----attenzione a mettere i puntatore e le referenze, perchè il vector fa cambiare il puntatore---
     *
     *
     * Parallelizzare il codice
     *
     *
     * come posso calcolare l'efficienza del mio codicei dal punto di vista di memoria e risorse utilizzate, come faccio a monitorarle
     * /proc/memInfo solo per linux
     *
     *
     *--- vai sul git di vicini PhDMPI----
     *
     *
     * ---ha senso mantenere l'orientamento dei vertici, se sì come posso fare?---
     *
     *TODO
     * ordinare i vertici in senso antiorario           <- TODO-DA FARE
     *
     *
     * DISCUTI
     * Fai al posto della matrice di adiacenza una matrice di adiacenza che agli archi asoscia i triangoli adiacenti
     * Forse conviene mettere gli id al posto degli oggetti per questione di memoria
     *
     *TODO
     *
     *test tolleranza
     *
     *TODO
     *report con immagini, complessita
     *TODO
     *la presentazione slide che prendono le immagine dei report per commentare, non guardare le linee di codice, compplessità computazionale della funzione
     *non troppe slide
     */

    //----------------------------------------------------

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
        //auto startRaffinamento= chrono::high_resolution_clock::now();

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

    return 0;

}






