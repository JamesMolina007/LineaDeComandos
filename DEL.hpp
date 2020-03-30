#pragma once
#include <string>
#include "Comando.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class DEL : public Comando{
    public:
    DEL(){};
    void ejecucion();
    vector<string> getBorrados();
};

void DEL::ejecucion(){
    ofstream DirectoriosBorrados("Borrados.txt", ios::app );
    if( !DirectoriosBorrados ){
        cerr << "No se ṕuedo abrir el archivo" << endl;
        exit( EXIT_FAILURE );
    }
    string path = directorio + "/" + valor;
    DirectoriosBorrados << path << endl;
    ejecutado = true;
}

vector<string> DEL::getBorrados(){
    vector<string> borrados;
    ifstream DirectoriosBorrados("Borrados.txt", ios::in );
    if( !DirectoriosBorrados ){
        cerr << "No se ṕuedo abrir el archivo" << endl;
        exit( EXIT_FAILURE );
    }
    string linea;
    while( DirectoriosBorrados >> linea ){
        borrados.push_back(linea);
    }
    return borrados;
}