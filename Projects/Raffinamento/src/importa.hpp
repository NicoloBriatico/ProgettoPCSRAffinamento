#ifndef __IMPORTA_H
#define __IMPORTA_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"

#include "empty_class.hpp"


using namespace std;
using namespace Eigen;
using namespace ShapeLibrary;


//*************************************************************

bool ImportMesh(vector<ShapeLibrary::Vertice>& vertici,vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Triangle>& triangoli);

bool ImportCell0Ds(vector<ShapeLibrary::Vertice>& vertici);

bool ImportCell1Ds(vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Vertice>& vertici);

bool ImportCell2Ds(vector<ShapeLibrary::Triangle>& lista, vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Vertice>& vertici);

// ***************************************************************************

bool ImportMesh(vector<ShapeLibrary::Vertice>& vertici,vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Triangle>& triangoli)
{

    if(!ImportCell0Ds(vertici))
        return false;

    if(!ImportCell1Ds(archi, vertici))
        return false;

    if(!ImportCell2Ds(triangoli, archi, vertici))
        return false;

    //testo che le informazioni sui triangoli siano corrette
    for (unsigned int i = 0;  i< triangoli.size();i++)
    {
        //ciclo su ogni triangolo e controllo che i vertici siano associati agli archi
        for (unsigned int j= 0; j<3;j++)
        {

            if (((triangoli[i].vertices[j].id != triangoli[i].edges[j].inizio.id)||(triangoli[i].vertices[(j+1)%3].id != triangoli[i].edges[j].fine.id))&((triangoli[i].vertices[j].id != triangoli[i].edges[j].fine.id)&&(triangoli[i].vertices[(j+1)%3].id != triangoli[i].edges[j].inizio.id)))
                cerr<<"errore di coerenza nei dati"<<endl;
        }
    }

    return true;

}


// ***************************************************************************

bool ImportCell0Ds(vector<ShapeLibrary::Vertice>& vertici)
{
    //leggo il file
    ifstream file;
    file.open("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    unsigned int NumberCell0D = listLines.size();

    if (NumberCell0D == 0)
    {
        cerr << "Nessuna cella in 0D" << endl;
        return false;
    }

    //cout<<"Cell0d"<<endl;

    for (const string& line : listLines)
    {
        //creo un oggetto di classe Vertice e ci salvo le informazioni
        istringstream converter(line);
        ShapeLibrary::Vertice nodo;

        converter >>  nodo.id >> nodo.marker >> nodo.x >> nodo.y;

        //cout<<nodo.id <<"\t"<< nodo.marker <<"\t"<<nodo.x <<"\t"<<nodo.y<<endl;
        //lo aggiungo
        vertici.push_back(nodo);

    }

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Vertice>& vertici)
{
    //leggo il file
    ifstream file;
    file.open("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();
    file.close();

    unsigned int NumberCell1D = listLines.size();

    if (NumberCell1D == 0)
    {
        cerr << "Nessuna cella in 1D" << endl;
        return false;
    }

    //cout<<"cell1d"<<endl;

    for (const string& line : listLines)
    {
        //creo un oggetto di tipo arco e ci salvo le informazioni
        istringstream converter(line);
        ShapeLibrary::Arco arco;

        //variabile di appoggio
        unsigned int size_unsigned_int;

        converter >>  arco.id >> arco.marker>>size_unsigned_int;

        //converto l'id in oggetto
        arco.inizio = id2object( size_unsigned_int, vertici);
        converter >> size_unsigned_int;

        //converto l'id in oggetto
        arco.fine = id2object(size_unsigned_int, vertici);

        //cout<<arco.id <<"\t"<< arco.marker <<"\t"<<arco.inizio.id <<"\t"<<arco.fine.id<<endl;

        //lo aggiungo
        archi.push_back(arco);


    }

    return true;
}

// ***************************************************************************

bool ImportCell2Ds(vector<ShapeLibrary::Triangle>& triangoli,vector<ShapeLibrary::Arco>&  archi, vector<ShapeLibrary::Vertice>& vertici)
{
    //leggo il file
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    file.close();

    unsigned int NumberCell2D = listLines.size();

    if (NumberCell2D == 0)
    {
        cerr << "Nessuna cella in 2D" << endl;
        return false;
    }

    //cout<<"Cell2d"<<endl;

    for (const string& line : listLines)
    {
        //creo un oggetto triangolo e ci salvo le informazioni
        istringstream converter(line);
        ShapeLibrary::Triangle triangolo;

        array<unsigned int,3> vett;

        converter >>  triangolo.id;

        for(unsigned int i = 0; i < 3; i++)
        {
            converter >> vett[i];
            //converto l'id in oggetto
            triangolo.vertices[i] = id2object( vett[i], vertici);
        }


        for(unsigned int i = 0; i < 3; i++)
        {
            converter >> vett[i];
            //converto l'id in oggetto
            triangolo.edges[i] = id2object(vett[i], archi);
        }

        //cout<<triangolo.id <<"\t"<< triangolo.vertices[0].id<<"\t"<< triangolo.vertices[1].id<<"\t"<< triangolo.vertices[2].id<<"\t"<< triangolo.edges[0].id<<"\t"<< triangolo.edges[1].id<<"\t"<< triangolo.edges[2].id<<endl;

        //aggiungo il triangolo
        triangoli.push_back(triangolo);


    }

    return true;
}

#endif // __IMPORTA_H
