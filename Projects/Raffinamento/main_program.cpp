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
        DOVREMMO TESTARE ANCHEE LA TOLLERANZA
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
    double theta = 0.5;

    vector<ShapeLibrary::Arco> archi;
    vector<ShapeLibrary::Vertice> vertici;
    vector<ShapeLibrary::Triangle> triangoli;

    if(!ImportMesh(vertici,archi, triangoli))
    {
    return 1;
    }

    //------------------------------------------------------------

    //calcolo le aree dei triangoli

    /*cout<<"\nid e aree:"<<endl;
    for (unsigned int i=0; i<triangoli.size();i++)
    {
        //calcolo l'area di tutti i triangoli
        triangoli[i].CalcolaArea();
        cout<<triangoli[i].id<<"\t"<<triangoli[i].area<<endl;
    }
    cout<<endl;
    //ordino i triangoli per area
    triangoli = SortLibrary::HeapSort(triangoli, &ShapeLibrary::Triangle::area);
    cout<<"triangolo con area più grande:\n"<<triangoli[0].id<<"\t"<<triangoli[0].area<<endl;
*/
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

    //mesh.Esporta();

  return 0;

}






