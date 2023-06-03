#include <iostream>
#include "Eigen/Eigen"
#include "map"

//file contenente il codice per il sorting
#include "sortingArea.hpp"
//file contenente la definizione delle tolleranze
#include "tolleranza.hpp"
//file contente le funzioni per importare la mesh
#include "importa.hpp"
//file contente le classi
#include "empty_class.hpp"


/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA
        DOVREMMO TESTARE ANCHE LA TOLLERANZA
*/


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
        * -VERIFICARE CHE LA MESH SIA BEN POSTA     <-NOI SIAMO QUI ORA
        * -ESPORTARE IL FILE
    */

    /*      VA SETTATA LA TOLLERANZA INIZIALE       */

    //----------------------------------------------------

    //imposto una percentuale di triangoli da considerare
    double theta = 0.9;

    vector<ShapeLibrary::Vertice> vertici;
    vector<ShapeLibrary::Arco> archi;
    vector<ShapeLibrary::Triangle> triangoli;

    if(!ImportMesh(vertici,archi, triangoli))
    {
    return 1;
    }

    //------------------------------------------------------------

    //mi costruisco un oggetto in classe mesh
    ShapeLibrary::Mesh mesh = Mesh(triangoli, archi, vertici);
    mesh.CalcolaMatriceAdiacenza();
    //cout<<mesh.adiacenza<<endl;

    //-----------------------------------------------------------

    unsigned int numTriPartenza = triangoli.size();
    while(numTriPartenza>mesh.triangoli.size()*theta)
    {

        mesh.RaffinamentoStart();
        //mesh.RaffinamentoStart();
        //dovrei aggiornare la matrice di adiacenza
    }

    mesh.Esporta();
    //file vertici come in input;
    //file archi che associ subito id arco, vertice inizio (senza id) con coordinata x e y, vertice fine (senza id) con coordinata x e y;

  return 0;

}






