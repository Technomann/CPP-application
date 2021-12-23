
/**
 * \file kocsi.cpp
 * \brief A 'kocsi.h' fájl definíciói, a konstruktor kivételével
 */

#include "kocsi.h"

//! Getter a kocsihoz tartozó maximális méretre
size_t Kocsi::getMeret() const{
    return maxFerohely;
}

//! Getter a kocsihoz tartozó szabad helyek számára
size_t Kocsi::getSzabad() const{
    return szabadHelyek;
}

//! Getter a kocsihoz tartozó osztályra
bool Kocsi::getOsztaly() const{
    return osztaly;
}

//! 'Operator=' túlterhelése
Kocsi& Kocsi::operator=(const Kocsi &a) {
    if(&a != this){
        sorsz = a.sorsz;
        maxFerohely = a.maxFerohely;
        szabadHelyek = a.szabadHelyek;
        osztaly = a.osztaly;
    }
    return *this;
}

/*!
 * Másoló konstruktor, a legegyszerűbben.
 */
Kocsi::Kocsi(const Kocsi &a) {
    sorsz = a.sorsz;
    maxFerohely = a.maxFerohely;
    szabadHelyek = a.szabadHelyek;
    osztaly = a.osztaly;
}

/*!
 * Függvény a kocsi szabad helyeinek csökkentésére. Csak akkor csökkent, ha még van szabad hely a kocsiban.
 */
void Kocsi::csokkentSzabad() {
    if(szabadHelyek<maxFerohely)
        --szabadHelyek;
}

//! Getter a kocsihoz tartozó sorszámra
size_t Kocsi::getSorsz() const {
    return sorsz;
}
