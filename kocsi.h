
/** \file kocsi.h
 * \brief A 'Kocsi' osztály deklarációja, és adattagjainak definíciója
 * \details Ebbena  fájlban valósítottam meg a 'Kocsi' osztály, és annak priát adattagjait, illetve
 * konstruktorát. A metódusok definiíciói a 'kocsi.cpp' fájlban találhatóak. Ez az objektum egy vonatkocsi
 * paramétereit próbálja reprezentálni, köztük a kocsi sorszámával, szabad helyeinek számával, maximális méretével,
 * és, hogy a kocsi első- vagy másodosztályú.
 */

#pragma once

#include <iostream>

#include "memtrace.h"

/*!
 * \class Kocsi
 * \brief A vonatkocsit reprezentáló osztály
 */
class Kocsi{
    size_t sorsz; ///< a kocsi sorszáma
    size_t szabadHelyek; ///< a kocsiban lévő maradék szabad helyek száma
    size_t maxFerohely; ///< a kocsiban maximálisan elhelyezhető utasok száma
    bool osztaly; ///< a kocsi osztály, 'true', a első, 'false', ha másod
public:
    //! Az osztály konstruktora default paraméterekkel.
    Kocsi(size_t sorsz = 4, size_t szabadHelyek = 10, size_t maxHely = 30, bool osztaly = false) :
    sorsz(sorsz),
    szabadHelyek(szabadHelyek),
    maxFerohely(maxHely),
    osztaly(osztaly){}

    /*!
     * 'Operator=' túlterhelés, hogy könnyebben lehessen dolgozni az osztállyal.
     */
    Kocsi& operator=(const Kocsi& a);

    //! Másoló konstruktor, hogy könnyebben lehessen dolgozni az osztállyal.
    Kocsi (const Kocsi& a);

    /*!
     * Ez a függvény felelős azért, hogy egyel csökkentse a szabad helyek számát. EZt a függvényt hívja meg
     * az 'jegyetElhelyez' függvény is a 'Vonat' objektumokban.
     */
    void csokkentSzabad();

    /*!
     * Getter az aktuális szabad helyek számára.
     * @return a szabad helyek száma, 'size_t' típusban
     */
    size_t getSzabad() const;

    /*!
     * Getter a maximális méretre.
     * @return a maximális helyek száma, 'size_t' típusban
     */
    size_t getMeret() const;

    /*!
     * Getter a kocsi sorszámára.
     * @return a kocsi sorszáma, 'size_t' típusban
     */
    size_t getSorsz() const;

    /*!
     * Getter a kocsi osztályára.
     * @return 'true', ha első, 'false', ha második
     */
    bool getOsztaly() const;

    //!Default destruktor
    ~Kocsi(){}
};
