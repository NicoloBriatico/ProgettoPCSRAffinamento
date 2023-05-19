#ifndef SORTINGAREA_HPP
#define SORTINGAREA_HPP

/*
 * nella scelta del sorting ci conviene implementarne uno che funziona bene tipo heapsorting o mergesorting (se non sbaglio), far funzionare tutto e quindi utilizzarlo come campione.
 * qualora avessimo tempo per farlo potremmo pensare di implementare un quicksorting, ovvero qualcosa di più veloce e meno accurato, runnare tutto e valutare la differenza di efficienza
 * a livello di velocità e di accuratezza come una sorta di errore rispetto allo heapsorting e quindi definire dei pro e dei contro
 */

/* dobbiamo scegliere se utilizzare o meno i templete
 * teoricamente se lo vogliamo fare generico ha senso usare i templeti
 * nell'ottica di risolvere questo file specifico tanto vale passargli un int
 * boh dobbiamo decidere tanto di fatto è pochissima la differenza fra l'uno e l'altro
 */


/*
 * per come è implementato questo heapsort prende in input un vettore di dimensione variabile contenente un qualsiasi tipo di funzione (è un templete) e riordina il vettore
 * dal più piccolo al più grande, qualora si voglia implementare dal più grande al più piccolo bisognerebbe attivare decreasing.
 * Dato che a noi serve sempre ordinare dal più grande al più piccolo io opterei per ridefinire direttamente l'algoritmo in modo che ordini dal più grande al più piccolo
*/
//OSS ho apportato (e segnalato i vari cambi), ma andrebbe testato per garantirne l'effettivo funzionamento!!!

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"

using namespace std;
using namespace Eigen;

namespace SortLibrary {

/*
//impostazioni per ordinare in senso inverso
  struct DecreasingInt
  {
    int value;
    DecreasingInt() = default;
    DecreasingInt(const int& value): value(value){}

  };

  inline ostream &operator<<(ostream &os, const DecreasingInt &obj)
  {
    os << obj.value;
    return os;
  }

  inline bool operator==(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value == obj2.value;
  }

  inline bool operator!=(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return !(obj1 == obj2);
  }

  inline bool operator<(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value > obj2.value;
  }

  inline bool operator>(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value < obj2.value;
  }
*/

/* PER ORA HO LASCIATO LO HEAPSORT, POI SCEGLIAMO BENE COSA IMPLEMENTARE*/

  template<typename T>
  //funzione che scambia gli indici
  void Scambia(unsigned int i, unsigned int j,vector<T>& heapTree ) {
    //salvo l'elemento in posizione i esima
    T tmp = heapTree[i];
    //scambio l'elemento i esimo con quello in posizione j
    heapTree[i] = heapTree[j];
    //analogamente per l'elemento j esimo
    heapTree[j] = tmp;
  }

  //dato un nodo il padre è definito come
  int Padre(unsigned int i)  {
    return (i - 1) / 2;
  }

  //dato un nodo mi calcolo i figli sinistri
  unsigned int Sinistro(unsigned int i)  {
    return 2 * i + 1;
  }

  template<typename T>
  unsigned int MigliorePadreFigli(unsigned int i,vector<T>& heapTree,const unsigned int& heapSize )  {
    //parto dal nodo sinistro di i
    unsigned int j = Sinistro(i);
    unsigned int k = Sinistro(i);
    //se k+1 è ancora nell'albero lo aggiorno
    if (k + 1 < heapSize)
        k = k + 1;
    //se il nodo k è più grande del nodo j sostituisco j con k
    //HO INVERTITO > CON <
    if (heapTree[k] < heapTree[j])
        j = k;
    //HO INVERTITO <= CON <=
    //se il nodo i>=nodo j sostituisco j con i
    if (heapTree[i] <= heapTree[j])
        j = i;
    //ritorno il nuovo indice
    return j;
  }

  template<typename T>
  void Riordina(vector<T>& heapTree,const unsigned int& heapSize, unsigned int i) {
    //l'albero che ho in heapTree è tutto ordinato fino alla posizione i-esima
    //scorro finche è verificata la condizione di heap Tree
      //HO INVERTITO > CON <
    while( i>0 && heapTree[i] < heapTree[Padre(i)]){
        //scambio gli indici e aggiorno la i (che ora si è invertita con il padre)
        Scambia(i, Padre(i), heapTree);
        i = Padre(i);
        /*cout<<"dopo: "<<endl;
        for (unsigned int k = 0; k<heapSize; k++){
            cout<<heapTree[k]<< ", ";
        }

        cout<<endl;*/
        }

    //scorro fino alla fine il vettore e finchè non trovo il migliore dei figli
    while (Sinistro(i) < heapSize && i!= MigliorePadreFigli(i, heapTree, heapSize))
    {
        //unsigned int migliore = MigliorePadreFigli(i, heapTree, heapSize);
        Scambia(i, Sinistro(i), heapTree);
        i = Sinistro(i);
        /*cout<<"dopo: "<<endl;
        for (unsigned int k = 0; k<heapSize; k++){
            cout<<heapTree[k]<< ", ";
        }

        cout<<endl;*/
    }
  }



  template<typename T>
  vector<T> HeapSort(const vector<T>& v){
    //creo un heap tree
    unsigned int heapSize = 0;
    //definisco la dim del vettore
    heapSize = v.size();
    //definisco un vettore heapTree
    vector<T> heapTree(heapSize);
    //costruisco un heap tree
    for (unsigned int i = 0; i<heapSize; i++){
        //cout<<i<<endl;
        //inserisco l'elemento nell'heapTree
        heapTree[i]=v[i];

        //cout<<"prima: "<<endl;

        /*for (unsigned int j = 0; j<heapSize; j++){
            cout<<heapTree[j]<< ", ";
            }

        cout<< endl;*/

        //lo riordino:
        Riordina(heapTree,i, i);

       /* cout<<"dopo: "<<endl;
        for (unsigned int k = 0; k<heapSize; k++){
            cout<<heapTree[k]<< ", ";
            }

        cout<<endl;*/

    }
    //uscito dal for heapTree è un heapTree
    /*cout<<"dopo: "<<endl;
    for (unsigned int k = 0; k<heapSize; k++){
        cout<<heapTree[k]<< ", ";
    }

    cout<<endl;*/
    while (heapSize != 0)
    {
        //inizializzo il massimo come il primo elemento dell'heap
        T massimo = heapTree[0];
        //metto al posto dell'elemento che ho salvato l'ultimo elemento della coda
        heapTree[0] = heapTree[heapSize - 1];
        heapTree[heapSize-1] = massimo;

        //aggiorno la dimensione dello heap
        heapSize = heapSize - 1;
        for (unsigned int i = 0; i<heapSize; i++){
        //riorganizzo lo heap considerando !!!!!!!!!!!!!!!!!!
            Riordina(heapTree, heapSize, i);
        }


        //verifico se posso dimezzare
        //VerificaDimezzamento(heapArray, heapSize);
        //ritorno il massimo valore ottenuto
    }
    return heapTree;
  }


}





#endif // SORTINGAREA_HPP
