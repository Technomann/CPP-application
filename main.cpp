
/** \file main.cpp
 * \brief A "felesleges" 'main.cpp'
 * \details Ebben a fájlban csupán egyetlen függvényhívás található, ami a 'fomenu_main' függvényt hívja meg.
 * \attention
 * A program futásához fontos feltétel, hogy az 'ncurses' könyvtár elérhetp legyen, enélkül nem fog elindulni a program.
 * A programhoz mellékelek egy egyszerű 'Makefile'-t is, ami segít a program telepítésében. A "telepítés" után
 * a program a './Vonatjegy paranccsal indítható a forrásmappából. A program futásához még feltétlenül szükséges
 * az 'init.txt' megléte, ami a kezdeti adatokat tartalmazza minden egyes indításhoz. Kezdetben a szerkesztőmenühöz
 * tartozó jelszó az '1234', ez a későbbiekben könnyen megváltoztatható.
 */

#include "fomenu.h"

int main() {
    fomenu_main();
}
