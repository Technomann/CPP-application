
/**
 * \file jegy.cpp
 * \brief A 'jegy.h' fájlhoz tartozó definíciók, a konstruktor kivételével
 */

#include "jegy.h"

/*bool Jegy::joHely() {
    return !(hely.helyszam == -1 || hely.kocsiszam == -1);
}*/
//! 'Operator=' túlterhelése
Jegy& Jegy::operator=(const Jegy &j) {
    if(&j != this) {
        nev = j.nev;
        szulDatum = j.szulDatum;
        honnan = j.honnan;
        hova = j.hova;
        indulas = j.indulas;
        erkezes = j.erkezes;
        hely = j.hely;
        osztaly = j.osztaly;
        diak = j.diak;
        fizetendo = j.fizetendo;
    }
    return *this;
}

//! Másoló konstruktor
Jegy::Jegy(const Jegy &j) {
    nev = j.nev;
    szulDatum = j.szulDatum;
    honnan = j.honnan;
    hova = j.hova;
    indulas = j.indulas;
    erkezes = j.erkezes;
    hely = j.hely;
    osztaly = j.osztaly;
    diak = j.diak;
    fizetendo = j.fizetendo;
}

//! A kiíró függvény, ami a fájlbaírást könnyíti meg
std::ostream& Jegy::jegyetKiir(std::ostream& os){
    os << nev << "                   " << szulDatum << std::endl;
    os << "Indulo allomas: " << honnan << "    " << "Indulasi ido: " << indulas << std::endl;
    os << "Erkezo allomas: " << hova << "    " << "Erkezesi ido: " << erkezes << std::endl;
    os << "Osztaly: ";
    if(osztaly)
        os << "Elso\n";
    else
        os << "Masod\n";
    os << hely;
    os << "Kedvezmeny: ";
    if(diak)
        os << "Diak 50%\n";
    else
        os << "Nincs\n";
    os << "Fizetendo: " << fizetendo;

    return os;
}
