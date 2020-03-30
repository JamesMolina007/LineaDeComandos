#include <ncurses.h>
#include "DEL.hpp"
#include "MKDIR.hpp"
#include "ARCHIVO.hpp"
#include "WRITE.hpp"
#include "READ.hpp"
#include "CHANGECOLOR.hpp"
#include "CHANGEMACHINE.hpp"
#include "CHANGEUSER.hpp"
#include "CD.hpp"
#include "Comando.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <vector>

using namespace std;

string usuario;
string maquina;
WINDOW *w = new WINDOW();
DIR *dir;
string ruta;
string comando;
bool vivo = true;
Comando *comando_ptr = new Comando();
vector<string> valores;
CD _cd;
CHANGECOLOR _changecolor;
MKDIR _mkdir;
ARCHIVO _file;
WRITE _write;
READ _read;
CHANGEMACHINE _changemachine;
CHANGEUSER _changeuser;
DEL _del;
bool valido = false;

void defecto();
void EscribirComando();
void RevisarComando();
string getString();
void procesoArchivo( char *Archivo );
void ejecutarLS();
void changecolor();
void mkdir();
void file();
void write();
void read();
void changeuser();
void changecolor();
void changemachine();
void cd(int);
void del();


int main(){
    maquina = _changemachine.getMachine();
    usuario = _changeuser.getUser();
    comando_ptr->directorio = "/home";
    w = initscr();
    scrollok(w,TRUE);
    start_color();
    clear();
    defecto();
    EscribirComando();
    endwin();
}

void defecto(){
    ruta = comando_ptr->directorio;

    init_pair(1, COLOR_GREEN, _changecolor.color );
    init_pair(2, COLOR_CYAN, _changecolor.color);
    attron( A_DIM | COLOR_PAIR(1) );
    string init = usuario + "@" + maquina;
    addstr( init.c_str() );
    attroff( A_DIM | COLOR_PAIR(1) );
    attron( A_DIM | COLOR_PAIR(2) );
    addstr( comando_ptr->directorio.c_str() );
    addch(':');
    addch('~');
    attroff( A_DIM | COLOR_PAIR(2) );
    addstr("$ ");
    refresh();
}

void EscribirComando(){
    do{
        comando = getString();
        if( comando != "exit" ){
            RevisarComando();
        }
        else
            vivo = false;
    }while( vivo );
}

string getString(){
    string entrada;
    nocbreak();
    echo();
    attron( A_DIM | COLOR_PAIR(2) );
    int ch = getch();
    attroff( A_DIM | COLOR_PAIR(2));
    while ( ch != '\n' ){
        entrada.push_back( ch );
        ch = getch();
    }
    return entrada;
}

void comandoMalo(){ 
    attron( A_DIM | COLOR_PAIR(1) );
    addstr("Comando No Valido!");
    addstr("\n-----------------------------------------------------------------------------------\n");
    addstr("Comandos Disponibles:\n");
    addstr("cd/                               -> Vuelve a la carpeta anterior\n");
    addstr("clear                             -> Limpiar pantalla\n");
    addstr("ls                                -> Listar directorio actual\n");
    addstr("cd <NombreCarpeta>                -> Ingresa a la carpeta indicada\n");
    addstr("del <NombreElemento>              -> Elimina carpeta especificada\n");
    addstr("mkdir <NombreCarpeta>             -> Crea carpeta en el directorio actual\n");
    addstr("file <NombreArchivo>.txt          -> Crea archivo de texto en el directorio actual\n");
    addstr("write <NombreArchivo>.txt <Texto> -> Escribe en el archivo indicado\n");
    addstr("read <NombreArchivo>.txt          -> Lee el contenido del archivo indicado\n");
    addstr("changeColor <Color>               -> Cambiar color del fondo\n");
    addstr("changeUser <Valor>                -> Cambia el nombre del usuario por el indicado\n");
    addstr("changeMachine <Valor>             -> Cambia el nombrel del usuario\n");
    addstr("exit                              -> Cerrar la terminal \n");
    addstr("-----------------------------------------------------------------------------------\n\n");
    attroff( A_DIM | COLOR_PAIR(1));
}

void arreglar(){
    valores.clear();
    vector<string> temp;
    string acum = "", acum2 = "";
    bool bandera = false;
    for (size_t i = 0; i < comando.size(); i++){
        if( comando[i] != ' ' || bandera ){
            acum += comando[i];
            bandera = true;
        }
    }
    acum += ' ';
    for (size_t i = 0; i < acum.size(); i++){
        if( acum[i] != ' '){
            acum2 += acum[i];
        }else{
            temp.push_back(acum2);
            acum2 = "";
        }
    }

    for (size_t j = 0; j < temp.size(); j++){
        if( temp[j] != " " && temp[j] != "" )
            valores.push_back(temp[j]);
    }
}

void RevisarComando(){
    valido = false;
    arreglar();
    if( valores.size() == 1 ){
        if( valores[0] == "ls"){
            ejecutarLS();
            valido = true;
        }
        if( valores[0] == "exit" ){
            exit(1);
            valido = true;
        }
        if( valores[0] == "clear" ){
            clear();
            valido = true;
        }
        if( valores[0] == "cd/" ){
            cd(2); 
            valido = true;
        }
    }
    if( valores.size() == 2 ){
        if( valores[0] == "cd" )cd(1);
        if( valores[0] == "del" )del();
        if( valores[0] == "file" )file();
        if( valores[0] == "read" )read();
        if( valores[0] == "mkdir" )mkdir();
        if( valores[0] == "changeUser" )changeuser();
        if( valores[0] == "changeColor" )changecolor();
        if( valores[0] == "changeMachine" )changemachine();  
    }
    if( valores[0] == "write" && valores.size() == 3 ) write();
    if( !valido && comando != "" )comandoMalo();
    defecto();
}

void comando_comun(){
    comando_ptr->setValor(valores[1]);
    comando_ptr->directorio = ruta;
    comando_ptr->ejecucion();
    valido = true;
}

void cd(int op){
    if(op == 1){
        comando_ptr = &_cd;
        comando_comun();
        if( !_cd.ejecutado )
            addstr("El archivo seleccionado no existe!\n");
    }
    else{
        int borrar;
        for (size_t i = 0; i < comando_ptr->directorio.size(); i++){
            if( comando_ptr->directorio[i] == '/' )borrar = i;
        }
        string temp;
        for (size_t i = 0; i < borrar; i++){
            temp += comando_ptr->directorio[i];
        }
        comando_ptr->directorio = temp;    
    }
    valido = true;
}

void mkdir(){
    comando_ptr = &_mkdir;
    comando_comun();
}

void file(){
    comando_ptr = &_file;
    comando_comun();
}

void write(){
    comando_ptr = &_write;
    _write.texto = valores[2];
    comando_comun();
}

void read(){
    comando_ptr = &_read;
    comando_comun();
    attron( A_DIM | COLOR_PAIR(2) );
    addstr( _read.salida.c_str() );
    attroff( A_DIM | COLOR_PAIR(2) );
}

void changecolor(){
    comando_ptr = &_changecolor;
    _changecolor.w = w;
    comando_comun();
    if(!_changecolor.ejecutado){
        attron(A_DIM | COLOR_PAIR(1));
        printw("El color ingresado no esta disponible!\n");
        attron(A_DIM | COLOR_PAIR(1));
    }else clear();
}

void changeuser(){
    comando_ptr = &_changeuser;
    comando_comun();
    usuario = _changeuser.getUser();
}

void changemachine(){
    comando_ptr = &_changemachine;
    comando_comun();
    maquina = _changemachine.getMachine();
}

void del(){
    comando_ptr = &_del;
    comando_comun();
}

bool EsDirectorio( string path) {
	struct stat st_info;
	assert(path.c_str() != NULL);
	if (stat(path.c_str(), &st_info) < 0) {
		return false;
	}
	return S_ISDIR(st_info.st_mode);
}

void ejecutarLS( ){
    init_pair(7,COLOR_WHITE,_changecolor.color);
    vector<string> borrados;
    borrados = _del.getBorrados();
    struct dirent * elemento;
    string elem;
    int contador = 1;
    if (dir = opendir(comando_ptr->directorio.c_str())){ 
        while (elemento = readdir(dir)){
            bool existe = true;
            elem = elemento->d_name;
            if (elem != "." && elem != ".."){
                for (size_t i = 0; i < borrados.size(); i++){
                    if( comando_ptr->directorio+"/"+elem == borrados[i] ){
                        existe = false;
                    }
                }
                if( existe ){
                    if( EsDirectorio(comando_ptr->directorio+"/"+elem) ){
                        init_pair(4, COLOR_BLUE, _changecolor.color );
                        attron( A_DIM | COLOR_PAIR(4));
                        printw("%-35s",elem.c_str());
                        attroff( A_DIM | COLOR_PAIR(4));
                    }else{
                        if( _changecolor.color != 7 ){
                            attron( A_DIM | COLOR_PAIR(7));
                            printw("%-35s",elem.c_str());
                            attroff( A_DIM | COLOR_PAIR(7));
                        }else{
                            attron( A_DIM | COLOR_PAIR(2));
                            printw("%-35s",elem.c_str());
                            attroff( A_DIM | COLOR_PAIR(2));
                        }
                    }
                    if( contador % 4 == 0 ) {
                        addch('\n');
                    }
                    contador++;
                }
                
            }
        }    
    
    }
    addch('\n');
    closedir(dir);
}