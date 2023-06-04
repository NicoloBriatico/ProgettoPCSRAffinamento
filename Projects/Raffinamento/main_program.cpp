#include <iostream>
#include "Eigen/Eigen"
#include "map"
#include <chrono>

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
    LINEA GUIDA
        * -LEGGERE I FILE E SALVARE I CONTENUTI
        * -CALCOLARE LE AREE DEI TRIANGOLI
        * -TROVARE IL TRIANGOLO PIÙ GRANDE
        * -CREARE LA MESH DI PARTENZA
        * -RAFFINARE IL TRIANGOLO
        * -VERIFICARE CHE LA MESH SIA BEN POSTA
        * -ESPORTARE IL FILE                        <-NOI SIAMO QUI ORA
        */

    /*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA   <-NOI SIAMO QUI ORA

*/

    //----------------------------------------------------

    //imposto una percentuale di triangoli da considerare
    double theta = 0.3;

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
    auto startRaffinamento= chrono::high_resolution_clock::now();

    while(numTriPartenza>mesh.triangoli.size()*theta)
        mesh.RaffinamentoStart();

    auto endRaffinamento = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedRaffinamento = endRaffinamento - startRaffinamento;

    auto startExport= chrono::high_resolution_clock::now();
    //esporto i nuovi dati
    mesh.Esporta();
    auto endExport = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedExport = endExport - startExport;


    cout<<"\nTempo di import: "<<elapsedImport.count()<<" sec"<<endl;
    cout<<"Tempo di creazione matrice di Adiacenza: "<<elapsedAdiacenza.count()<<" sec"<<endl;
    cout<<"Tempo di Raffinamento: "<<elapsedRaffinamento.count()<<" sec"<<endl;
    cout<<"Tempo di Raffinamento: "<<elapsedExport.count()<<" sec"<<endl;

    return 0;

}






