#pragma once
#include <string>

using namespace std;

class Comando{
    public:
        string valor;
        string directorio;
        bool ejecutado = false;
        Comando(){};
        void seleccion();
        virtual void ejecucion(){};
        void setValor( string valor ){ this->valor = valor; }
        string getValor(){ return valor; }
};

