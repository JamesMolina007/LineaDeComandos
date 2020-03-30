#pragma once
#include <string>
#include "Comando.hpp"
#include <fstream>
#include <cstdlib>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

class READ : public Comando{
    public:
    READ(){};
    void ejecucion();
    string salida;
};

void READ::ejecucion(){
    string cadena;
    salida = "";
    ifstream datos(directorio + "/" + valor );
    if(datos.fail()){
        cout<<"Texto entrada Estructura.txt no existe"<<endl;
    } else {
    while(!datos.eof()){
      getline(datos,cadena);
      salida += cadena + '\n';
    }
  }
}
