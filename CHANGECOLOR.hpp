#pragma once
#include <string>
#include "Comando.hpp"
#include <ncurses.h>
#include <iostream>
class CHANGECOLOR : public Comando{
    public:
    void ejecucion();
    WINDOW *w;
    int color = 0;
};

void CHANGECOLOR::ejecucion(){
    if( valor == "white"){
        init_pair(5, COLOR_WHITE,COLOR_WHITE);
        wbkgd(w,COLOR_PAIR(5));
        color = COLOR_WHITE;
        ejecutado = true;
    }
    if( valor == "black"){
        init_pair(5, COLOR_BLACK,COLOR_BLACK);
        wbkgd(w,COLOR_PAIR(5));
        color = COLOR_BLACK;
        ejecutado = true;
    }
    if( valor == "red"){
        init_pair(5, COLOR_RED,COLOR_RED);
        wbkgd(w,COLOR_PAIR(5));
        color = COLOR_RED;
        ejecutado = true;
    }
    endwin();
}