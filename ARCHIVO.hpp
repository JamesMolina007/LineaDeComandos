#pragma once
#include <string>
#include "Comando.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class ARCHIVO : public Comando{
    public:
        ARCHIVO(){};
        void ejecucion( );
};

void ARCHIVO::ejecucion( ){
  string archivo = directorio + "/" + valor;
  ofstream CrearTxt(archivo, ios::app );
  if( !CrearTxt ){
      cerr << "No se ṕuedo abrir el archivo" << endl;
      exit( EXIT_FAILURE );
  }
  ejecutado = true;
}