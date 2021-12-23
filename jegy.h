
/**
 * \file jegy.h
 * \brief A 'Jegy' osztály definícióját tartalmazó header fájl
 * \details Ebben a fájlban valósítottam meg a 'Jegy' osztályt, ami egy vonatjegyet modellez le. Egy 'Jegy'
 * objektum rendelkezik minden olyan adattal, aminek majd rá kell kerülnie a jegyre. Például a jegyvásárló
 * neve, születési dátuma, vagy a vonat sorszáma, amire a jegyet váltották. Ezen vonat adatait akár lekérhettem
 * volna mindig nyomtatás előtt az adott 'Vonat' objektumból, de egyszerűbbnek, ás tömörebbnek láttam, hogy
 * a jegy magában tartalmazza ezeket.
 */

#pragma once

#include "vonat.h"
#include <iostream>
#include "extras.h"

#include "memtrace.h"


/*!
 *  \class Jegy
 *  \brief A vonatjegyet reprezentáló osztály
 */
class Jegy{
    std::string nev; ///< a jegy felhasználójának neve
    Datum szulDatum;///< a jegy felhasználójának születési dátuma
    std::string honnan;///< a vonat indulási állomása
    std::string hova;///< a vonat érkezési állomása
    Ido indulas;///< a vonat indulási ideje
    Ido erkezes;///< a vonat érkezési ideje
    Helyezes hely;///< a hely-és kocsiszám, ahova a jegy szól
    bool osztaly;///< a kocsi osztálya, ahova a jegy szól
    bool diak;///< van-e diákkedvezménye a vásárlónak, 'true' van, egyékbént 'false'
    size_t fizetendo;///< a jegyért fizetendő összeg
public:
    //! A 'Jegy' osztály konstruktora default paraméterekkel
    Jegy(const char* nev = "",Datum szulDatum = Datum(), const char* honnan = "", const char* hova = "",
            Ido indulas = Ido(), Ido erkezes = Ido(), Helyezes hely = Helyezes(),
            bool osztaly = false, bool diak = false, size_t fizetendo = 0) :
    nev(nev),
    szulDatum(szulDatum),
    honnan(honnan),
    hova(hova),
    indulas(indulas),
    erkezes(erkezes),
    hely(hely),
    osztaly(osztaly),
    diak(diak),
    fizetendo(fizetendo){}

    //bool joHely();
    //! 'Operator=' túlterhlés a könnyeb kezelhetőség érdekében
    Jegy&operator=(const Jegy&);

    /*!
     * Másoló konstruktor, a könnyebb kezelhetőség érdekében
     */
    Jegy(const Jegy&);

    /*!
     * Egy kiíró függvény, ami egy paraméterként átvett 'std::ostream' típusú objektumra írja a jegy adatait.
     * Ennek azért láttam értelmét, mert az 'std::fstream' is ilyen objektum, így sokkal egyszerűbb egy jegynek
     * a fájlbaírása.
     */
    std::ostream& jegyetKiir(std::ostream& os);

    //! Default destruktor
    ~Jegy(){}
};
