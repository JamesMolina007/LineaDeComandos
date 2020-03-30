#pragma once
#include <string>
#include "Comando.hpp"

class CHANGEUSER : public Comando{
    public:
    void ejecucion();
    string getUser();
};

void CHANGEUSER::ejecucion(){
    if( valor != ""){
        ofstream fs("Usuario.txt");
        fs << valor;
        fs.close();
    }else{
        ofstream fs("Usuario.txt");
        fs << "home";
        fs.close();
    }
    ejecutado = true;
}

string CHANGEUSER::getUser(){
    string _usuario;
    ifstream usuario( "Usuario.txt" , ios::in );
    usuario >> _usuario;
    return _usuario;
}