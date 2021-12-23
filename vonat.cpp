
/**
 * \file vonat.cpp
 * \brief A 'vonat.h' fájl definíciói a konstruktor kivételével
 */

#include "vonat.h"

/*!
 * Másoló konstruktor, a legegyszerűbben.
 */
Vonat::Vonat(const Vonat &v){
    sorsz = v.sorsz;
    induloAll = v.induloAll;
    erkezoAll = v.erkezoAll;
    indulas = v.indulas;
    erkezes = v.erkezes;
    alapAr = v.alapAr;
    kocsik = v.kocsik;
}

//! 'Operator==' túlterhelése a vonatok sorszámaira.
bool Vonat::operator==(const Vonat &v) const{
    return sorsz == v.sorsz;
}

//! 'Operator=' túlterhelése
Vonat& Vonat::operator=(const Vonat &v) {
    if(&v != this){
        sorsz = v.sorsz;
        induloAll = v.induloAll;
        erkezoAll = v.erkezoAll;
        erkezes = v.erkezes;
        indulas = v.indulas;
        alapAr = v.alapAr;
        kocsik = v.kocsik;
    }
    return *this;
}

//! A kiíró függvény
void Vonat::kiir(WINDOW* win,
        short elso,
        short masodik) const {
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);

    wprintw(win,"\n                         ");

    wattron(win, COLOR_PAIR(elso));

    wprintw(win, "%d -- %s-->%s", sorsz, induloAll.c_str(), erkezoAll.c_str());
    wprintw(win, "          Jegyar: %d\n", alapAr);
    wattroff(win,COLOR_PAIR(elso));

    wprintw(win,"                         ");

    wattron(win,COLOR_PAIR(masodik));
    wprintw(win, "            Indulas - Erkezes: %s:%s - %s:%s\n",
            indulas.ora.c_str(),
            indulas.perc.c_str(),
            erkezes.ora.c_str(),
            erkezes.perc.c_str());
    wattroff(win,COLOR_PAIR(masodik));
}

//! Getter a vonathoz tartozó kocsik darabszámára
size_t Vonat::kocsikSzama() const {
    return kocsik.size();
}

//! Getter a vonathoz tartozó alapárra
size_t Vonat::getAr() const {
    return alapAr;
}

//! Getter a vonathoz tartozó érkezőállmásra
const char* Vonat::getErkezoAll() const {
    return erkezoAll.c_str();
}

//! Getter a vonathoz tartozó indulóállomásra
const char* Vonat::getIndoloAll() const {
    return induloAll.c_str();
}

//! Getter a vonathoz tartozó indulási időre
Ido Vonat::getIndulas() const {
    Ido res(indulas.ora.c_str(), indulas.perc.c_str());
    return res;
}

//! Getter a vonathoz tartozó érkezési időre
Ido Vonat::getErkezes() const {
    Ido res(erkezes.ora.c_str(), erkezes.perc.c_str());
    return res;
}

//! Egy jegy elhelyezését szimuláló függvény
Helyezes Vonat::jegyetElhelyez(const bool osztaly){
    Helyezes res;
    for(size_t i = 0; i<kocsik.size(); ++i){
        if(kocsik[i].getOsztaly() == osztaly && kocsik[i].getSzabad() != 0){
            res.kocsiszam = kocsik[i].getSorsz();
            res.helyszam = (int)(kocsik[i].getMeret()-kocsik[i].getSzabad())+1;
            kocsik[i].csokkentSzabad();
            return res;
        }
    }
    return res;
}

//! Getter a vonathoz tartozó sorszámra
size_t Vonat::getSorsz() const {
    return sorsz;
}
