
/**
 * \file fomenu.h
 * \brief A 'fomenu.cpp' header fájlja
 * \details Ebben a fájlban találhatók a 'fomenu.cpp' fájl fordításához szükséges 'include'-ok, illetve
 * a .cpp fájl által használt függvények deklarációi.
 */

#pragma once

#include <iostream>
#include <fstream>
#include "ncurses.h"
#include "curses.h"
#include "szerkeszto.h"
#include "tarolo.h"
#include "vonat.h"
#include "vetel.h"

#include "memtrace.h"



void fomenu_main();

void fomenuKiir(WINDOW*, size_t, size_t, size_t);

void initialize(std::string&, Tarolo<Vonat>&);

void fajlba_ment(const std::string&, Tarolo<Vonat>&);
