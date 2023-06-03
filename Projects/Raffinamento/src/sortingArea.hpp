#ifndef SORTINGAREA_HPP
#define SORTINGAREA_HPP

/*
 * nella scelta del sorting ci conviene implementarne uno che funziona bene tipo heapsorting o mergesorting (se non sbaglio), far funzionare tutto e quindi utilizzarlo come campione.
 * qualora avessimo tempo per farlo potremmo pensare di implementare un quicksorting, ovvero qualcosa di più veloce e meno accurato, runnare tutto e valutare la differenza di efficienza
 * a livello di velocità e di accuratezza come una sorta di errore rispetto allo heapsorting e quindi definire dei pro e dei contro
 */

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"

using namespace std;
using namespace Eigen;

namespace SortLibrary {



  template<typename T>
  inline void Scambia(unsigned int i, unsigned int j,vector<T>& heapTree ) {

    T tmp = heapTree[i];

    heapTree[i] = heapTree[j];

    heapTree[j] = tmp;
  }


  inline int Padre(unsigned int i)  {
    return (i - 1) / 2;
  }


  inline unsigned int Sinistro(unsigned int i)  {
    return 2 * i + 1;
  }

  template<typename T, typename A>
  unsigned int MigliorePadreFigli(unsigned int i,vector<T>& heapTree,const unsigned int& heapSize,A T::*specifica )  {

    unsigned int j = Sinistro(i);
    unsigned int k = Sinistro(i);

    if (k + 1 < heapSize)
        k = k + 1;

    if (heapTree[k].*specifica < heapTree[j].*specifica)
        j = k;

    if (heapTree[i].*specifica <= heapTree[j].*specifica)
        j = i;
    //ritorno il nuovo indice
    return j;
  }

  template<typename T, typename A>
  void Riordina(vector<T>& heapTree,const unsigned int& heapSize, unsigned int i,A T::*specifica) {

    while( i>0 && heapTree[i].*specifica < heapTree[Padre(i)].*specifica){
        Scambia(i, Padre(i), heapTree);
        i = Padre(i);
        }

    //scorro fino alla fine il vettore e finchè non trovo il migliore dei figli
    while (Sinistro(i) < heapSize && i!= MigliorePadreFigli(i, heapTree, heapSize, specifica))
    {
        //unsigned int migliore = MigliorePadreFigli(i, heapTree, heapSize);
        Scambia(i, Sinistro(i), heapTree);
        i = Sinistro(i);

    }
  }


    //gli passo il vettore di oggetti da ordinare e il parametro secondo il quale definire l'ordinamento
  template<typename T, typename A>
  vector<T> HeapSort(const vector<T>& v,A T::*specifica){
    //creo un heap tree
    unsigned int heapSize = 0;
    //definisco la dim del vettore
    heapSize = v.size();
    //definisco un vettore heapTree
    vector<T> heapTree(heapSize);
    //costruisco un heap tree
    for (unsigned int i = 0; i<heapSize; i++){

        //inserisco l'elemento nell'heapTree
        heapTree[i]=v[i];
        Riordina(heapTree,i, i, specifica);
    }

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
            Riordina(heapTree, heapSize, i, specifica);
        }


    }
    return heapTree;
  }


}





#endif // SORTINGAREA_HPP
