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



  //dobbiamo valutare se mantenere questa impostazione, oppure sceglierne una diversa da quella fatta dalla Teo
  //definiamo la mesh sfruttando la struct quindi importiamo i dati
  TriangularMesh mesh;

  if(!ImportMesh(mesh))
  {
    return 1;
  }

  return 0;
  //se tutto va a buon fine in mesh saranno contenute tutte le informazioni di cui necessitiamo


}



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
