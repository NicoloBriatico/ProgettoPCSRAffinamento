#ifndef SORTINGAREA_HPP
#define SORTINGAREA_HPP
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

// ***************************************************************************

inline int Padre(unsigned int i)  {
    return (i - 1) / 2;
}

// ***************************************************************************

inline unsigned int Sinistro(unsigned int i)  {
    return 2 * i + 1;
}

// ***************************************************************************

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

    return j;
}

// ***************************************************************************

template<typename T, typename A>
void Riordina(vector<T>& heapTree,const unsigned int& heapSize, unsigned int i,A T::*specifica) {

    while( i>0 && heapTree[i].*specifica < heapTree[Padre(i)].*specifica){
        Scambia(i, Padre(i), heapTree);
        i = Padre(i);
    }

    while (Sinistro(i) < heapSize && i!= MigliorePadreFigli(i, heapTree, heapSize, specifica))
    {
        Scambia(i, Sinistro(i), heapTree);
        i = Sinistro(i);
    }
}

// ***************************************************************************

template<typename T, typename A>
vector<T> HeapSort(const vector<T>& v,A T::*specifica){

    unsigned int heapSize = 0;
    heapSize = v.size();
    vector<T> heapTree(heapSize);

    for (unsigned int i = 0; i<heapSize; i++){
        //inserisco l'elemento nell'heapTree e li ordino
        heapTree[i]=v[i];
        Riordina(heapTree,i, i, specifica);
    }

    while (heapSize != 0)
    {
        T massimo = heapTree[0];
        heapTree[0] = heapTree[heapSize - 1];
        heapTree[heapSize-1] = massimo;

        //aggiorno la dimensione dello heap
        heapSize = heapSize - 1;
        for (unsigned int i = 0; i<heapSize; i++){
            Riordina(heapTree, heapSize, i, specifica);
        }
    }
    return heapTree;
}


}





#endif // SORTINGAREA_HPP
