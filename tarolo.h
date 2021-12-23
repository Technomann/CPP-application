
/**
 * \file tarolo.h
 * \brief A sablon tárolót tartalmazó header file
 * \details
 * Ez a fájl tartalmazza a program fő elemeként használt sablonos tároló definícióját. Lévén, ez egy sablon,
 * nem készült hozzá külön .cpp fájl, mert amikor példányosítani szeretnénk a tárolót valamelyik .cpp fájlban,
 * mondjuk a szerkeszto.cpp-ben, akkor fordító nem tudja legenerálni a megfelelő példányt, mert a definíció nem
 * lenne ismert, de amikor a tarolo.cpp-t fordítaná, azt se tudja egyáltalán, hogy a szerkeszto.cpp-ben mi
 * használni szeretnénk, így nem tudja létrehozni a megfelelő példányt, tehát csak sablon header fájljában,
 * azaz ebben a fájlban lehet a definíció. A tároló az STL tárolókra hasonlít. Természetesen nem valósítottam meg
 * az STL tárolók összes metódusát, de a feladat szempontjából hasznosabbakat igen.
 */

#pragma once

#include <iostream>
#include "ncurses.h"
#include "curses.h"

#include "memtrace.h"


//! A 'Tarolo' osztály
/*!
 * Ebben az osztályban valósítottam meg a STL tároló "utánzatát"
 * @tparam T hogy milyen típusra példányosodjon
 */
template <typename T>
class Tarolo{
    size_t elemszam; ///< A tároló aktuális elemszámát tároló size_t típusú változó
    T * tarolo; ///< Sablonparaméter típusokra mutató pointer, a tárolóban eltárolt objektumokra mutat
public:
    //! A tároló konstruktora
    /*!
     * Kezdetben az elemszámot 0-ra, a 'tarolo' pointert 'nullptr'-re inicializálja
     */
    Tarolo() : elemszam(0), tarolo(nullptr){}

    //! Beillesztő függvény tetszőleges indexű helyre.
    /*!
     * Az első hely indexe 0. Ha nagyobb indexű helyre szretnénk beilleszteni, mint ahány elem van a tárolóban,
     * 'const char*' kivételt dob "OUT OF RANGE INSERT" szöveggel.
     * @param mit a sablontípusú objektum, ami be szeretnénk illeszteni, referencia szerint átvéve
     * @param idx hogy milyen indexű helyre szeretnénk behelyezni, 'size_t' típusként átvéve
     */
    void insert(T& mit, const size_t idx){
        if(idx > elemszam)
            throw "OUT OF RANGE INSERT";

        T* uj = new T[elemszam+1];

        for(size_t i = 0; i < idx; i++)
            uj[i] = tarolo[i];

        uj[idx] = mit;

        for(size_t i = idx; i <elemszam; i++)
            uj[i+1] = tarolo[i];

        ++elemszam;

        tarolo = uj;
    }

    //! Függvény egy tetszőleges indexű elem kivételére a tárolóból.
    /*!
     * Az első elem indexe 0. Ha a tároló elemszáma 0, vagy ilyen indexű elem nem lehet a tárolóban 'const char*'
     * kivételt dob "OUT OF RANGE - PULL" szöveggel.
     * @param idx melyik indexű elemet szeretnénk kivenni a tárolóból, 'size_t' típust vesz át
     */
    void pull(const size_t idx){
        if(elemszam == 0 || idx >= elemszam)
            //std::cout << "Ennyire ne legyél buta" << std::endl;
            throw std::out_of_range("OUT OF RANGE - PULL");

        T* uj = new T[elemszam-1];

        /*for(size_t i =0; i<idx; ++i)
            uj[i] = tarolo[i];*/

        /*for(size_t i = idx+1; i<elemszam; ++i)
            uj[i-1] = tarolo[i];*/

        //A felső két for egybeírása
        for(size_t i = 0; i<elemszam; ++i){
           if(i < idx)
               uj[i] = tarolo[i];
           else if(i > idx)
               uj[i-1] = tarolo[i];
        }

        delete[] tarolo;
        tarolo = uj;
        --elemszam;
    }

    //! Az STL-ekéhez hasonló 'push_back' függvény
    /*!
     * @param mit sablontípusú objektum, amit be szeretnénk helyezni a tárolóba, referenciaként átvéve
     */
    void push_back(T& mit){
        T* uj = new T[elemszam+1];

        for(size_t i = 0; i<elemszam; ++i)
            uj[i] = tarolo[i];

        uj[elemszam] = mit;

        delete[] tarolo;

        ++elemszam;

        tarolo = uj;
    }

    //! Az STL-ekéhez hasonló 'push_front' függvény
    /*!
     * @param mit sablontípusú objektum, amit be szeretnénk helyezni a tárolóba, referenciaként átvéve
     */
    void push_front(T& mit){
        T* uj = new T[elemszam + 1];

        for(size_t i =0; i< elemszam; ++i)
            uj[i+1] = tarolo[i];

        uj[0] = mit;

        delete[] tarolo;

        ++elemszam;

        tarolo = uj;
    }

    //! Az STL-ekéhez hasonló 'pop_back' függvény
    void pop_back(){
        T* uj = new T[elemszam-1];
        --elemszam;
        for(size_t i =0; i<elemszam; i++)
            uj[i] = tarolo[i];
        delete[] tarolo;
        tarolo = uj;
    }

    //! Az STL-ekéhez hasonló 'pop_front' függvény
    void pop_front(){
        T* uj = new T[elemszam-1];
        for(size_t i =1; i<elemszam; i++)
            uj[i-1] = tarolo[i];

        --elemszam;

        delete[] tarolo;
        tarolo = uj;
    }

    //! Operator[ ] túlterhelése, a könnyebb kezelhetőség érdekében
    /*!
     * Nem kezel túlindexelést, ez a hívó feladata.
     */
    T& operator[](const size_t idx){
        //if(idx >= elemszam) throw "Out of order";
        //if(idx == elemszam);
        return tarolo[idx];
    }

    //! Operator[ ] túlterhelése, a könnyebb kezelhetőség érdekében, 'const' változat
    /*!
     * Nem kezel túlindexelést, ez a hívó feladata.
     */
    T operator[](const size_t idx) const{
        //if(idx >= elemszam) throw "Out of order";
        return tarolo[idx];
    }

    //! Operator= túlterhelése
    Tarolo& operator=(const Tarolo& rhs){
        if(&rhs != this){
            T* uj = new T[rhs.size()];
            for(size_t i =0; i<rhs.size(); ++i)
                uj[i] = rhs[i];
            elemszam = rhs.size();
            delete[] tarolo;
            tarolo = uj;
        }
        return *this;
    }

    //! Törlő metódus
    /*!
     * Ez a függvény törli a tárolóban lévő elemeket, ha nem 0 az elemszám., majd az elemszámot 0-ra állítja.
     */
    void clear(){
        if(elemszam > 0)
            delete tarolo;
        elemszam = 0;
    }

    //! A tároló másoló konstruktora
    Tarolo (const Tarolo& rhs){
        T* uj = new T[rhs.size()];
        for(size_t i =0; i<rhs.size(); ++i)
            uj[i] = rhs[i];
        elemszam = rhs.elemszam;
        delete[] tarolo;
        tarolo = uj;
    }


    /*!
     * Ez a függvény a tároló minden elemére meghívja azok 'kiir' függvényét. Ehhez az kell, hogy a tárolt
     * objektum típusoknak létezzen ilyen nevű függvénye. Ezért van a 'Vonat' objektumnak is ilyenje,
     * @param win a 'Window' típusú objektum, amire szeretnénk, hogy a 'kiir' kiírjon
     */
    void listaz(WINDOW*win) const {
        for(size_t i = 0; i< elemszam; ++i){
            tarolo[i].kiir(win);
        }
    }

    /*!
     * A függvény visszatér egy igaz/hamis értékkel, annak függvényében, hogy
     * üres-e a tároló
     * @return 'true', ha üres, 'false', ha nem üres
     */
    bool empty() const {
        return elemszam == 0;
    }

    /*!
     * A függvény visszatér a tárolóban lévő elemek számával.
     * @return elemszám, 'size_t' típus
     */
    size_t size() const {
        return elemszam;
    }

    /*!
     * "Okos" destruktor. Csak akkor hívja meg a 'delete'-et a 'tarolo' pointerre, ha a tárolóban nem 0 elem van.
     */
    ~Tarolo(){
        if(elemszam != 0)
            delete[] tarolo;
    }
};
