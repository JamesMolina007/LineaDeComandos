#pragma once
#include <string>
#include "Comando.hpp"
#include <iostream>
#include <dirent.h>

using namespace std;

class CD : public Comando{
    public:
        CD(){};
        void ejecucion( );
};

void CD::ejecucion(  ){
    DIR *dir;
    struct dirent * elemento;
    string elem;
    ejecutado = false;
    int contador = 1;
    if (dir = opendir(directorio.c_str())){ 
        while (elemento = readdir(dir)){
            elem = elemento->d_name;
            if (elem != "." && elem != ".."){ 
               if( elem == valor ) ejecutado = true;
            }
        }        
    
    }
    closedir(dir);
    if( ejecutado )(*this).directorio += '/'+(*this).valor;
}

