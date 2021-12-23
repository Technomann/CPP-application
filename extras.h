
/**
 * \file extras.h
 * \brief Az extra struktúrákat tartalmazó fájl
 * \details Ebben a fájlban valósítottam meg azokat a struktúrákat, amiket még célszerűnek láttam a feladathoz.
 * A struktúrák definícióit a konstruktorok kivételéve az 'extras.cpp' fájlban készítettem el. Mindegyik struktúrához
 * tartozik 'Operator<<' túlterhelés, hogy a jegy "nyomtatásako" könnyeb ki lehessen írni őket fájlba.
 */

#pragma once

#include <iostream>

#include "memtrace.h"


/*! \class Ido
 * \brief Időpontok tárolására alkalmas primitív struktúra.
 * \details Az időpontok tárolására 'std::string' típusú változókat használtam, így egyszerűbb a '00' megejeleítése.
 */
struct Ido{
    std::string ora; ///< 'std::string' típusú, órák tárolására alkalmas publikus attribútum
    std::string perc; ///< 'std::string' típusú, percek tárolására alkalmas publikus attribútum

    //!Konstruktor default paraméterekkel.
    /*!
     * Alapértelmezetten ""-re inicializálja az adattagokat.
     * @param ora hogy hány órára állítsuk az 'ora' változót, 'const char*'-ként átvéve
     * @param perc hogy hány percre állítsuk az 'perc' változót, 'const char*'-ként átvéve
     */
    Ido(const char* ora = "", const char* perc = "") : ora(ora), perc(perc){}

    //! 'Operator=' túlterhelése 'Ido' struktúrára
    Ido& operator=(const Ido& a);
};

/*!
 * \class Datum
 * \brief Egyszerű struktúra dátumok tárolására.
 * \details Minden adattagja 'size_t' típusú a biztonság kedvéért.
 */
struct Datum{
    size_t ev; ///< adattag az év tárolására
    size_t ho;///< adattag a hónap tárolására
    size_t nap;///< adattag a naőp tárolására

    //!Konstruktor default paraméterekkel.
    /*!
     * Kezdetben minden publikus attribútumot 0-ra állít.
     */
    Datum(): ev(0), ho(0), nap(0){}
};

/*!
 * \class Helyezes
 * \brief Egyszerű struktra egy vonatkocsiban történő elhelyezések tárolására.
 * \details 'Size_t' típusú adattagokat használtam, ez volt a leg kézenfekvőbb.
 */
struct Helyezes{
    size_t kocsiszam; ///< adattag a kocsiszám tárolására
    size_t helyszam; ///< adattag a helyszám tárolására

    //!Konstruktor default paraméterekkel.
    /*!
     * Kezdetben (-1;-1)-re inicializálja az adattagokat, akár innen is tudható, ha nem sikerült egy
     * elelyeezés a vonaton.
     */
    Helyezes() : kocsiszam(-1), helyszam(-1){}

    //! 'Operator=' túlterhelése 'Helyezes' struktúrára
    Helyezes& operator=(const Helyezes& a);
};

/*!
 * 'Operator<<' túlterhelése, hogy 'Ido' objektumot is könnyen ki lehessen írni egy 'std::ostream' típusú objektumra.
 * @param os ostream típusú objektum
 * @param a kiírandó Ido objektum
 * @return 'std::ostream&' (Hogy fűzhető legyen)
 */
std::ostream& operator<<(std::ostream& os, const Ido& a);

/*!
 * 'Operator<<' túlterhelése, hogy 'Datum' objektumot is könnyen ki lehessen írni egy 'std::ostream' típusú objektumra.
 * @param os ostream típusú objektum
 * @param a kiírandó Ido objektum
 * @return 'std::ostream&' (Hogy fűzhető legyen)
 */
std::ostream& operator<<(std::ostream& os, const Datum& a);

/*!
 * 'Operator<<' túlterhelése, hogy 'Helyezés' objektumot is könnyen ki lehessen írni egy 'std::ostream' típusú objektumra.
 * @param os ostream típusú objektum
 * @param a kiírandó Ido objektum
 * @return 'std::ostream&' (Hogy fűzhető legyen)
 */
std::ostream& operator<<(std::ostream& os, const Helyezes& a);

