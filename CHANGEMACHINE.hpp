#pragma once
#include <string>
#include <fstream>
#include <cstdlib>
#include "Comando.hpp"

class CHANGEMACHINE : public Comando{
    public:
    void ejecucion();
    string getMachine();
};

void CHANGEMACHINE::ejecucion(){
    if( valor != ""){
        ofstream fs("Maquina.txt");
        fs << valor;
        fs.close();
    }else{
        ofstream fs("Maquina.txt");
        fs << "vm-gauss";
        fs.close();
    }
    ejecutado = true;
}

string CHANGEMACHINE::getMachine(){
    char cadena[128];
    ifstream maquina("Maquina.txt");
    while (!maquina.eof()) {
        maquina >> cadena;
    }
    maquina.close();
    return cadena;
}