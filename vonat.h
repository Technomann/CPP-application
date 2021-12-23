
/**
 * \file vonat.h
 * \brief A 'Vonat' osztály tartalmazó header fájl
 * \details Ebben a fájlban valósítottam meg a 'Vonat' osztályt. Ez tartalmazza az osztály működéséhez szükséges
 * 'include'-okat. A vonat.cpp fájl tartalmazza a 'Vonat' osztály metódusainak definícióit.
 */


#pragma once

#include <iostream>
#include "tarolo.h"
#include "kocsi.h"
#include "extras.h"
#include "ncurses.h"
#include "curses.h"

#include "memtrace.h"


/*!
 * \class Vonat
 * \brief Egy vonatszerelvényt reprezentáló osztály
 * \details Az osztály egy a való életben is használatos vonatot próbál meg reprezentálni. Tartozik az objektumhoz
 * vonatsorszám, jegyár, induló- és érkező állomás, indulási- és érkezési idő, és egy 'Kocsi' objektumokat tároló
 * tároló. Az objektumnak főként getterei, és szokványos konstruktorai, operátor últerhelései vannak, illetve két
 * "extrább" tagfüggvény ki1ráshoz, és jegy elhelyezéshez. A default destruktor tökéletesen megfelel.
 */
class Vonat{
    size_t sorsz; ///< a vonat sorszáma
    size_t alapAr; ///< a vonathoz tartozó alapár, másodosztály, kedvezmény nélkül. Ebből kerül kiszámításra az elsőosztálybeli, vagy diákkedvezményes ár.
    std::string induloAll; ///< az indulóállomás neve
    std::string erkezoAll;///< az érkezőállomás neve
    Ido indulas; ///< 'Ido' típusú attribútum, az indulási idő tárolására
    Ido erkezes;///< 'Ido' típusú attribútum, az érkezési idő tárolására
public:
    Tarolo<Kocsi> kocsik; ///< a kocsik tárolására alkalmas tároló. 'Public', mert szeretnénk hozzáférni és dolgozni vele
public:
    //! Az osztály konstruktora default paraméterekkel.
    Vonat(size_t vonatszam = 0, size_t alapar = 0, const char* indulo = "Innen", const char* erkezo = "Ide",
            Ido indulas = Ido(), Ido erkezes = Ido()) :
    sorsz(vonatszam), alapAr(alapar), induloAll(indulo), erkezoAll(erkezo), indulas(indulas), erkezes(erkezes),
    kocsik(){}

    /*!
     * 'Operator=' túlterhelés, hogy könnyebb legyen dolgozni a 'Vonat' objektumokkal.
     */
    Vonat& operator=(const Vonat&);

    /*!
     * Másoló konstruktor
     */
    Vonat (const Vonat&);

    /*!
     * 'Operator==' túlterhelés, ami két vonatot akkor tekint egyenlőnek, ha sorszámuk megegyezik.
     * @return 'true', ha egyezik a két sorszám, egyébként 'false'
     */
    bool operator==(const Vonat&)const;

    /*!
     * A függvény visszaadja a kocsikat tároló áoló elemszámát.
     * @return az elemszám, 'size_t' típusban
     */
    size_t kocsikSzama() const;

    /*!
     * A függvény visszaadja a vonathoz tartozó alapárt.
     * @return az ár, 'size_t' típusban
     */
    size_t getAr()const;

    /*!
     * A függvény visszaadja a vonathoz tartozó indulóállomást.
     * @return az indulóállomás, 'const char*' típusban
     */
    const char* getIndoloAll()const;

    /*!
     * A függvény visszaadja a vonathoz tartozó érkezőállomást.
     * @return az árkezőállomás, 'const char*' típusban
     */
    const char* getErkezoAll()const;

    /*!
     * A függvény visszaadja a vonathoz tartozó indulási időpontot.
     * @return az indulási idő, 'Ido' struktúrában
     */
    Ido getIndulas() const;

    /*!
     * A függvény visszaadja a vonathoz tartozó érkezési időpontot.
     * @return az érkezési idő, 'Ido' struktúrában
     */
    Ido getErkezes()const;

    /*!
     * A függvény visszaadja a vonat sorszámát.
     * @return a sorszám, 'size_t' típusban
     */
    size_t getSorsz() const;

    /*!
     * Ez a függvény elhelyez egy jegyet a vonaton, abbanaz osztályú kocsiban, amit paraméterként vesz át
     * ('true' első, 'false' másod). Ami azt jelenti, hogy egy 'Helyezés' objektumot ad vissza, ami
     * tartalmazza az adott jegyre írandó hely-és kocsiszámot, emellett csökkenti az adott kocsi szabad helyeinek számát
     * egyel. A függvény a megfelelő osztályú kocsik közül az első nem nulla szabad hellyel rendelkezőt választja ki. A
     * függvény nem véd az ellen, ha a vonaton nincs a paramétereknek megfelelő szabad hellyel rendelkező kocsi. Ebben az
     * esetben a 'Helyezes' objektum konstruktorában lévő default paramétereket fogja visszaadni, ami (-1;-1).
     * @return 'Helyezes' ojbektum, a megfelelő hely-és kocsiszámokkal
     */
    Helyezes jegyetElhelyez(bool);


    /*!
     * A függvény kiír egy 'Window' típusú objektumra, amit paraméterként, pointerként vesz át. A függvény alapértelmezetten
     * az ncurses könyvtár 'COLOR_PAIR' attribútumait használja, és ennek segítségével színezi az adott vonatot.
     * Alapesetben a 'BLUE-WHITE' & 'WHITE-BlUE' párokat használja, ezek vannak a default paraméterezésben, de
     * ha a programban máshol definiálunk két új 'COLOR_PAIR'-t, akkor ezek sorszámát átadva más színnel ír ki.
     * Ez megkönnyíti az 'index_kiir' függvényben a válozó színű kiírást.
     * @param elso
     * @param masodik
     * \warning A két alap attribútum sorszáma 3 és 4. Ezeken a program a függvény definíciójában hozza létre, így, ha
     * valaki ugyanilyen sorszámmal hoz létre attribútumokat a kiíráshoz, azok felül lesznek definiálva.
     */
    void kiir(WINDOW*,
            short elso = 4,
              short masodik = 3) const ;

    /*!
     * Default destruktor.
     */
    ~Vonat(){}
};
