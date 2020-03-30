#pragma once
#include <string>
#include "Comando.hpp"
#include <sys/stat.h>
#include <ncurses.h>

class MKDIR : public Comando{
    public:
        MKDIR(){};
        void ejecucion();
};

void MKDIR::ejecucion(){
    string path = directorio + "/" + valor;
    mkdir(path.c_str(),0777 ); 
}