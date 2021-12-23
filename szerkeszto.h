/**
 * \file
 * \brief A szerkeszto.cpp-hez tartozó header file
 * \details
 * Ebben a fájlban találhatóak a szerkeszto.cpp fájlhoz tartozó függvény deklarációk, és a fájlhoz tartozó include-ok
 */
#pragma once

#include <iostream>
#include <cstring>
#include "tarolo.h"
#include "vonat.h"
#include "ncurses.h"
#include "curses.h"
#include "fomenu.h"

#include "memtrace.h"


void megtekint_kiir(WINDOW*,Tarolo<Vonat>&, size_t, size_t, size_t);

void vonatokat_megtekint(WINDOW *,Tarolo<Vonat>&, size_t, size_t);

Tarolo<Vonat>& vonat_hozzaad(WINDOW*, Tarolo<Vonat>&, size_t,size_t, std::string&);

void indexel_kiir(WINDOW*,Tarolo<Vonat>&, size_t,size_t,size_t, size_t);

Tarolo<Vonat>& vonat_torol(WINDOW *win, Tarolo<Vonat>&, size_t, size_t, std::string&);

void rossz_jelszo(WINDOW* win, size_t);

void jelszo_modosit(WINDOW *, std::string&, size_t, size_t, Tarolo<Vonat>&);

Tarolo<Vonat>& jelszo(WINDOW *,std::string&, Tarolo<Vonat>&);

void szerkeszto_kiir(WINDOW*, size_t,size_t,size_t);

Tarolo<Vonat>& szerkeszto_menu(WINDOW *,std::string&, Tarolo<Vonat>&);




