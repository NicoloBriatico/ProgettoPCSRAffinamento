#include <iostream>
/*
 * va valutato quali librerie importare e quali file importare e dove
 */

//#include "Eigen/Eigen"
//#include <fstream>
//#include "map"


//file contenente il codice per il sorting
#include "sortingArea.hpp"

//file contenente la definizione delle tolleranze
#include "tolleranza.hpp"

//file contente le funzioni per importare la mesh
#include "importa.hpp"

//file contente le classi
#include "empty_class.hpp"


/*    RICORDARE DI FARE I TEST PER OGNI CLASSE IMPLEMENTATA, E PER OGNI FUNZIONE DEFINITA     */



// ***************************************************************************
int main()
{

    //FARE ATTENZIONE, VANNO OMOLOGATI I NOMI DEI FILE E I VARI RICHIAMI AD ESSI//

    /* PER ULIZZARE UNA CLASSE RICORDA:
     * METTERE #include "empty_class.hpp" all'inizio del file
     * scrivere nel codice ProjectLibrary::Empty empty;
     * chiamare l'oggetto con il metodo*/



    /*      VA SETTATA LA TOLLERANZA INIZIALE       */



/*Al posto di utilizzare una struct per la lettura potremmo definire una classe oggetto padre Mesh, all'interno della quale andremo ad inserire
 *  i vertici e gli annessi archi; nella classe figlia vertici metteremo i vertici, nell'altra classe figlia archi metteremo gli archi.
Ora, l'idea è che all'interno della classe padre Mesh noi possiamo implementare un metodo per il calcolo della matrice di adiacenza, uno per
l'aggiornamento di una matrice di adiacenza, uno per la ricerca dei nodi; nella classe vertice implementare un metodo per la ricerca dei lati
 che passano per un nodo e dei lati che passano per due nodi (ricorrendo al metodo di ricerca della classe padre [o qualcosa del genere] ),
passati tre punti al costruttore me li ordina in modo da averli sempre ordinati in senso antiorario; la classe lati, preso in input un lato
(passando per il metodo della classe padre) mi restituisce i vertici che ne sono le estremità.

La classe triangolo, almeno per il momento l'avevo pensata come qualcosa del tipo classe amica di mesh (o forse di tutte e tre), che dati in
input tre vertici e tre lati costruisce un triangolo, come metodo ha il calcolo dell'area, il dimezzamento e la verifica. (i metodi ereditati
 principalmente sarebbero i metodi di ricerca di archi o nodi).

    */


    ////////ATTENZIONE, NEL DEFINIRE LE CLASSI MESH, VERTICI, ARCHI, TRIANGOLI, PRENDI SPUNTO ( CIOÈ COPIA I TIPI E LA LOGICA, GROSSOMODO, DI IMPORTAZIONE DEL DATO
    /// CHE VENIVA UTILIZZATA NELLA STRUCT
    /// ATTENZIONE, POSSO FARE IN UNA CLASSE QUELLO CHE FACEVO IN UNA STRUCT, MA DEVE AVERE SENSO: LA STRUCT NON HA UNA LOGICA, MENTRE LE CLASSI SI
    /// L'IDEA QUINDI È DI FAR FARE COSE HAI DATI CHE STIAMO RACCOGLIENDO, TIPO FAR PARTIRE DELLE RICERCHE, CALCOLARE MATRICI, AGGIORNARE MATRICI ECC
    /// TENERE BENE A MENTE QUESTA COSA, ANCHE PER DARE UN SENSO ALLA PROGRAMMAZIONE AD OGGETTI
    ////////















  //dobbiamo valutare se mantenere questa impostazione, oppure sceglierne una diversa da quella fatta dalla Teo
  //definiamo la mesh sfruttando la struct quindi importiamo i dati

  ///SE OPTIAMO PER LA MESH COME CLASSE, DOBBIAMO PASSARGLI DEI COMANDI DIVERSI E SICURAMENTE LA MESH NON SARA UNA TRIANGULAR MESH, OVVERO UN OGGETTO DI TIPO STRUCT
    TriangularMesh mesh; //VA CAMBIATO IL TIPO E FORSE NE VA PASSATO PIÙ DI UNO (FORSE DOVREMMO PASSARGLI MESH, VERTICI, ARCHI)

  if(!ImportMesh(mesh))
  {
    return 1;
  }

  return 0;
  ///TEORICAMENTE SE TUTTO VA A BUON FINE IO DOVREI AVERE UN VERTICI TUTTI I VERTICI, IN ARCHI GLI ARCHI E IN TRIANGOLI I TRIANGOLI, ADESSO UNISCO LE INFORMAZIONI DI VERTICI E ARCHI
  /// DENTRO LA CLASSE MESH, IN MODO DA CREARE LA MATRICE DI ADIACENZA.
  /// A QUESTO PUNTO SFRUTTO LA MATRICE DI ADIACENZA PER CONTINUARE A LAVORARE
  /// OSS: POTREI UTILIZZARE IL METODO DERIVATO IN TRIANGOLI PER CALCOLARE LA MATRICE DI ADIACENZA DEI TRIANGOLI (UTILIZZANDO LA RICERCA DEL LATO COMUNE) [VA CAPITO BENE COME IMPLEMENTARE QUESTA COSA]
  ///
  //abbiamo importato i dati all'interno di Mesh, ora possiamo ad esempio costruire un grafo prendendo i nodi e gli archi per definire una matrice di adiacenta
    //potremmo quindi utilizzare una classe di tipo grafo e passargli i punti e gli archi che abbiamo messo in mesh per costruire una matrice di adiacenza
}

/*                                              COSE DA AGGIUNGERE
 *
 * test per il calcolo dell'area della classe triangolo
 *
 *

/*                                                              PROBLEMI DA RISOLVERE
 *capire come si fa a settare le tolleranze, basta fare #include file??
 *
 * al momento ImportMesh fallisce la lettura, dobbiamo trovare un modo per fargli leggere il file, penso sia un problema di dove è salvato nella directory;
 *
 *scegliere se mantenere per la mesh la struct definita dalla Teora nell'esercitazione;
 *
 *capire come impostare la classe Triangolo, quali metodi fare;
 *
 *capire se ci serve definire altre classi, come ad esempio triangolo ben posto, triangolo splittato o cose così;
 *
 *scegliere se definire tutto come metodo delle classi (ad esempio impostare un metodo bisezione che calcoli la bisezioneLatoMaggiore) o sfruttare delle funzioni a parte;
 *
 *definire un criterio d'arresto;
 *
 *teoricamente ci sono due file da testare uno nella cartella Dataset/Test1 e uno in Dataset/Test2
 *
 *capire se nel file tolleranza.hpp vado incluso e chiamato il file di sorting, perchè teoricamente per tutte le operazioni che includano l'uso di confronti dovremmo applicare le nuove tolleranze
 *
 *!!! oss: va omologata la lingua per una questione stilistica, quindi se scegliamo di scrivere gli output tutti in inglese vanno fatti tutti in inglese!!
*/


/*                                                          PROBLEMI RISOLTI DA SEGNALARE
 *
 *per inserire un file nel Header File o nel Source File, aprire il file CMakeList.txt in src (in basso) e scrivere list(APPEND raffinamento_headers ${CMAKE_CURRENT_SOURCE_DIR}/empty_class.hpp) sostituendo i nomi dei file scelti;
 *
 *anche i file da leggere vanno inseriti nel cmakelist quello in alto
 *
 *
 *
 *
 *
*/
