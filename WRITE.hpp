#pragma once
#include <string>
#include "Comando.hpp"

class WRITE : public Comando{
    public:
    WRITE(){};
    void ejecucion();
    string texto;
};

void WRITE::ejecucion(){
    string archivo = directorio + "/" + valor;
    ofstream Write(archivo, ios::app );
    Write << texto << " ";
    if( !Write ){
        cerr << "No se ṕuedo abrir el archivo" << endl;
        exit( EXIT_FAILURE );
    }
    ejecutado = true;
}