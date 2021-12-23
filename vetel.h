
#pragma once

/**
 * \file
 * \brief A vetel.cpp-hez tartozó header file
 * \details
 * Ebben a fájlban találhatóak a vetel.cpp fájl függvényeinek deklarációi, illetve a szükséges include-ok.
 */
#include "iostream"
#include "jegy.h"
#include "vonat.h"
#include "fomenu.h"
#include <fstream>
#include "ncurses.h"
#include "curses.h"
#include "szerkeszto.h"

#include "memtrace.h"


bool van_meg_helyO(const Vonat&, bool);

bool van_meg_hely(const Vonat&);

void ynKiir(WINDOW *,int, size_t, const char*);

bool yn(WINDOW*, size_t, const char*);

void vissza(WINDOW *, int mivel, size_t ,const char* szoveg);

bool vasarlas(WINDOW *, size_t, Vonat&);

void jegyvetel_begin(WINDOW *,Tarolo<Vonat>&, size_t, size_t );
