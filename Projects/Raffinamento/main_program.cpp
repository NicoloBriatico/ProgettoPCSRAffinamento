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


/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */


using namespace std;
// ***************************************************************************
int main()
{

    /*
     *                  INFO/PAZZIA
     *La mia idea pazza, una volta terminata la stesura del progetto è quella di stressare il più possibile il codice per verificarne il buon funzionamento e l'ottimizzazione delle parti
     *ovvero cercare/creare una mesh moooooooooooolto grande e vedere se continua a funzionare e quindi proporre come possibile soluzione (e confronto) l'uso di codice parallelizzato
     *questa cosa potrebbe tornarci comoda nell'ottica della relazione e poi mi eccita tantissimo parallelizzare il codice ahhah.
     *Detto questo, questa parte esce un po' fuori dalle richieste del progetto ed è penso notevolmente complicata (la parallelllizzazione), quindi fai finta di niente.
     *Ogni tanto all'interno del codice potresti trovare tipo ///questo codice si può parallelizzare m, che sono dei remarker per me qualora volessimo implementare la parallellizzazione
     *
     *
     *                     STRUTTURE DATI
     * - LA STRUCT (vedi "empty_class.hpp") è come quella impostata dalla Teora, manca dell'ultima parte (Cell2d), che è stata sostituita dalla classe Triangle. Vengono Cell0d e cell1d vengono letti come
     * aveva implementato la Teora, il file Cell2d ha la stessa implementazione della Teora, ma viene memorizzato in un oggetto della classe triangolo (vedi "importa.hpp")
     *
     * -è stata ristrutturata la classe TRIANGLE: è una classe senza figli o padre, prende in input le informazioni del file cell2d e costruisce una matrice con le coordinate (estratte
     * dalla struct), che ci consente di calcolare agilmente l'area con il metodo di Gauss;
     * metodi implementati:
     *    . area del triangolo
     *    . Vicini (no, non parlo del prof)
     *Da implementare:
     *      .Dimezza
     *Per informazioni più dettagliate vedi "empty_class.hpp"
     *
     *- è stata ristrutturata la classe MESH: è una classe senza padre o figli (per ora), prende in input un vettore di oggetti appartenti alla classe triangolo e calcola
     *subito una matrice di Adiacenza ATTENZIONE!!!! PER LA MATRICE DI ADIACENZA HO OPTATO PER UNA MATRICE SPARSA (QUINDI NON UNA MATRICE COMPLETA) PER QUESTIONI DI EFFICIENZA
     *metodi implementati:
     *          .
     *metodi da implementare:
     *          . aggiunta di un triangolo alla matrice di adiacenza
     *          .verifica della buona positura di una mesh
     *
     *
     *          SORTING
     *il sorting che ho scritto è quello dell'heapsort dell'esercitazione 6, volendo possiamo sceglierne un'altro
     *POTREMMO PENSARE DI IMPLEMENTARE DIVERSAMENTE L'HEAPSORT, PERCHÈ COM'È SCRITTO ORA RESTITUISCE UN VETTORE, POTREMMO PENSARE DI FARGLIELO MODIFICARE, MA DOVREMMO ANCHE
     *CONSIDERARE IL RISCHIO DI FARE UN'OPERAZIONE DEL GENERE!!!!!!!
     *
     *
     *          TOLLERANZA
     *ho settato le operazioni di tolleranza come nell'esercitazione 8 tipo, ma bisogna creare un collegamento con l'heapsort (forse)
     *
     *
     *                   LINEA GUIDA
     * -LEGGERE I FILE E SALVARE I CONTENUTI
     * -CALCOLARE LE AREE DEI TRIANGOLI E SALVARLE IN UN FILE
     * -CREARE LA MESH DI PARTENZA
     * -TROVARE IL TRIANGOLO PIÙ GRANDE <-NOI SIAMO QUI ORA
     * -RAFFINARE IL TRIANGOLO
     * -VERIFICARE CHE LA MESH SIA BEN POSTA
     * -ESPORTARE IL FILE
     */


    /*      VA SETTATA LA TOLLERANZA INIZIALE       */

    //----------------------------------------------------

    //definisco un oggetto di tipo struct
    TriangularMesh trimesh;       //trimesh mi ricorda un sacco trimon ahahha (mi diverto con poco lo so)
    //definisco la lista che mi conterrà i triangoli che creerò leggendo il file Cell2d
    vector<ShapeLibrary::Triangle> lista;

    if(!ImportMesh(trimesh, lista))
    {
    return 1;
    }

    /*arrivato a questo punto ho:
    *-trimesh contente le informazioni su vertici e archi;
    *-lista contente oggetti di tipo triangolo, ciascuno contente informazioni sui triangoli
    */

    //--------------------------------------------------------

    //osservazione: ho messo tutti i triangoli in una lista per due motivi
    //1) mi servono per creare l'oggetto nella classe mesh;
    //2) li ho creati in una funzione, ha senso salvarli perchè tanto mi serviranno di nuovo.



    ///per esempio potrei parallelizzare questa cosa///
    //definisco questa mappa che associerà all'id del triangolo la sua area
    map<int, double> aree = {};
    //v vettore temporaneo per ordinare le aree
    //per esempio qui sarebbe carino se riuscissimo ad evitare di creare un vettore così e passare direttamente a heapSort un vettore di aree (però per ora così funziona)
    vector<double> v= {};

    //calcolo le aree dei triangoli
    for(unsigned int i=0; i< lista.size();i++)
    {
        double area =lista[i].Area();
        //inserisco id e area nella mappa, solo l'area nella lista
        aree.insert({lista[i].id, area});
        v.push_back(area);
    }

    //-----------------------------------------------------------------------
    //ordino la lista, estraggo l'area più grande e attraverso la mappa mi ricollego all'id del triangolo

    vector<double> areaS=SortLibrary::HeapSort<double>(v);
    //cerco l'id del primo triangolo
    unsigned int idPartenza;
    for (const auto& coppia : aree) {
            if (coppia.second == areaS[0]) {
                idPartenza = coppia.first;
                break;
            }
        }
    cout<<idPartenza<<endl;

    //------------------------------------------------------------------
    //creo l'oggetto della classe mesh passandogli la lista di triangoli

    ShapeLibrary::Mesh mesh =Mesh(lista);

    /*oss: avremmo potuto scrivere direttamente una matrice piena, tuttavia in termini di efficienza fa molta acqua: per ogni triangolo al più potremmo avere al massimo 3 elementi (su 143 ora)
    * non nulli, quindi un inutile spreco di memoria. Per ovviare a questa cosa generalmente si ricorre alle matrici Sparse (abbiamo visto qualche accenno non troppo
    * dettagliato nel corso di metodi numerici), l'idea è che siano segnati all'interno di questa matrice fittizia solo i valori non nulli e la posizione all'interno della matrice.
    * fortunatamente la libreria eigen ha un tipo matrice sparsa, quindi mi aspetto che le operazioni siano tutte ottimizzate. Dobbiamo indagare in merito
    */

    ////!!!!!
    //mi salvo la matrice sparsa (in realtà riflettendoci ora, potrebbe non essere necessario definirla nel main questa, perchè mi basterebbe averla all'interno della classe
    //per poi utilizzarla nelle funzioni, sì mi sembra una scelta migliore, ci dobbiamo ragionare)
    ///!!!!

    Eigen::SparseMatrix<double> matriceAdiacenza = mesh.adiacenza;
    //se cancelli questo commento di sotto vedrai che stampa una prima parte dove segna le coppie (indice riga, indice colonna) e poi il valore associato, quindi si stampa la matrice intera con gli zeri
    //cout<<matriceAdiacenza<<endl;

    //-------------------------------------------




  return 0;

}








/*                                              COSE DA AGGIUNGERE
 *
 * test per il calcolo dell'area della classe triangolo
 *
 *
 */

/*                                                              PROBLEMI DA RISOLVERE
 *
 *definire un criterio d'arresto;
 *
 *teoricamente ci sono due file da testare uno nella cartella Dataset/Test1 e uno in Dataset/Test2
 *
 *!!! oss: va omologata la lingua per una questione stilistica, quindi se scegliamo di scrivere gli output tutti in inglese vanno fatti tutti in inglese!!
 *
 * VA ASSOLUTAMENTE CAPITO COME FUNZIONA IL MARKER PERCHÈ ALLA FINE DEL CODICE NOI VOGLIAMO UN FILE CSV DA EDITARE CON PARAVIEW E QUESTO PRENDE ANCHE IL MARKER
 *
 * decidere se il sorting va cambiato come nei commenti
 *
 * scegliere se scrivere del codice effettivo nel main, oppure chiamare una funzione e quindi evitare di richiamare la matrice di adiacenza
 *
*/


/*                                                          COSE UTILI
 *
 *per inserire un file nel Header File o nel Source File, aprire il file CMakeList.txt in src (in basso) e scrivere list(APPEND raffinamento_headers ${CMAKE_CURRENT_SOURCE_DIR}/empty_class.hpp) sostituendo i nomi dei file scelti;
 *
 *anche i file da leggere vanno inseriti nel cmakelist quello in alto
 *
 *Per stampare elementi di una mappa
 *  STAMPARE I CONTENUTI DI UNA MAPPA
  for(auto it = aree.begin(); it != aree.end(); it++)
  {

    cout << "key:\t" << it -> first << "\t values:"<<it -> second;
    //for(const unsigned int id : it -> second)
      //cout << "\t" << id;

    cout << endl;
  }

 *
 *STAMPARE UNA MATRICE DI
 *   for (int i = 0; i < matriceAdiacenza.rows(); ++i) {
           for (int j = 0; j < matriceAdiacenza.cols(); ++j) {
               cout << matriceAdiacenza(i, j) << " ";
           }
           cout << endl;
       }
 *
 *
 *
*/
