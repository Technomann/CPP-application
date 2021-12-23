
/**
 * \file fomenu.cpp
 * \brief Ebben a faáljban található a program főmenüjének megvalósítása
 * \details Ebben a fájlban valósítottam meg az összes olyan függvényt, ami a főmenühöz kellhet. Van egy
 * kiíró függvény, egy olyan függvény, ami kezeli az inputot, és egy inicializáló, illetve egy 'saver' függvény.
 */

#include "fomenu.h"
/*!
 * Ez a függvény felel azért, hogy a program futása végén, illetve ha változtatások adódnak futás közben is,
 * elmentse a vonatok lisáján vagy a szerkesztőmenü jelszaván végzet módosításokat az 'init.txt'-be, aminek
 * a program forrásmappájában kell lennie.
 * @param jelszo az éppen akuális jelszó, referenciaként átvéve
 * @param vonatok a vonatok listája, referenciaként átvéve
 */
void fajlba_ment(const std::string& jelszo, Tarolo<Vonat>& vonatok){
    std::fstream fileOut;
    fileOut.open("init.txt", std::ios::trunc | std::ios::out);

    fileOut << jelszo.c_str() << "\n";

    for(size_t i = 0; i<vonatok.size(); ++i){
        fileOut<<"v" << "\n";
        fileOut << vonatok[i].getSorsz() << "\n";
        fileOut << vonatok[i].getAr()<< "\n";
        fileOut << vonatok[i].getIndoloAll()<< "\n";
        fileOut << vonatok[i].getErkezoAll()<< "\n";
        fileOut << vonatok[i].getIndulas().ora<< "\n";
        fileOut << vonatok[i].getIndulas().perc<< "\n";
        fileOut << vonatok[i].getErkezes().ora<< "\n";
        fileOut << vonatok[i].getErkezes().perc<< "\n";
        for(size_t k = 0; k<vonatok[i].kocsik.size(); k++){
            fileOut << "k"<< "\n";
            fileOut << vonatok[i].kocsik[k].getSorsz()<< "\n";
            fileOut << vonatok[i].kocsik[k].getSzabad()<< "\n";
            fileOut << vonatok[i].kocsik[k].getMeret()<< "\n";
            fileOut << vonatok[i].kocsik[k].getOsztaly()<< "\n";
        }
        fileOut << "e"<< "\n";
    }

    fileOut.close();

    //std::cout << "File saving escalated successfully.\n";
    //std::cin.get();
}

/*!
 * Ez a függvény azért felel, hogy a program indítása során létrehozza az 'init.txt' fájl alapján a vonatok
 * listáját, a kocsikkal együtt, és inicializálja a szerkesztő menü jelszavát.
 * @param jelsz a szerkesztő menü jelszavának tárolására szolgáló változó, referenciaként átvéve
 * @param vonatok a vonatok tárolására szolgáló tároló, referenciaként átvéve
 */
void initialize(std::string& jelsz, Tarolo<Vonat>& vonatok){
    // Egy Vonat paraméterei.
    size_t vonatszam;
    size_t alapar;
    std::string induloALl;
    std::string erkezoAll;
    Ido indulas;
    Ido erkezes;

    // Ellenőrző karakter a txt-ben lévő elválasztásokhoz.
    char check;

    // Egy Kocsi paraméterei.
    size_t szabad;
    size_t meret;
    bool osztaly;
    size_t sorsz;

    // Fájl objektum létrehozása, és az "init.txt" megnyitása.
    std::fstream fio;
    fio.open("init.txt", std::ios::in);


    // A tároló feltöltése a txt-ben lévő adatokkal.
    if(fio.is_open()){
        fio >> jelsz;
        while(fio) {

            fio >> check;
            //std::cout << "Phase 2 escalated" << std::endl;

            while (check == 'v') {
                //std::cout << "Phase 3 escalated" << std::endl;

                fio >> vonatszam;
                fio >> alapar;
                fio >> induloALl;
                fio >> erkezoAll;
                fio >> indulas.ora;
                fio >> indulas.perc;
                fio >> erkezes.ora;
                fio >> erkezes.perc;
                Vonat v0(vonatszam, alapar, induloALl.c_str(), erkezoAll.c_str(), indulas, erkezes);
                //std::cout << "Phase 4 escalated" << std::endl;

                fio >> check;
                while (check == 'k') {
                    //std::cout << "Phase 5 escalated" << std::endl;

                    fio >> sorsz;
                    fio >> szabad;
                    fio >> meret;
                    fio >> osztaly;

                    Kocsi k0(sorsz, szabad, meret, osztaly);

                    v0.kocsik.push_back(k0); //itt

                    fio >> check;
                }
                vonatok.push_back(v0); //itt
                //std::cout << "Phase 6 escalated" << std::endl;
            }
        }
    } /*else {
        //radir();
        std::cout << "Nem tudtam megnyitni a file-t!" << std::endl;
        std::cin.get();
    }*/

    fio.close();
}

/*!
 * Ez a függvény megjeleníti a főmenü opcióit egy 'Window' objektumon, amit pointerként vesz át. Az
 * opciók tömbje is ebben a szubrutinban található. A paraméterként átvett megfelelő indexű opcióra
 * alkalmazza az ncurses könyvtár 'A_REVERSE' attribútumát.
 * @param win a 'Window' tpusú objektum, amire írni szeretnénk
 * @param idx hogy hányadik opcióra alkalmazzuk az attribútumot, az első elem a 0.
 * @param maxSzel 'win' maximális szélessége
 * @param maxMag 'win' maximális magassága
 */
void fomenuKiir(WINDOW* win, size_t idx, size_t maxSzel, size_t maxMag) {
    std::string fomenuMezok[5] = {"Kezdes\n",
                              "Vonat szerkeszto\n",
                              "Kilepes"};

    for(size_t i = 0; i<3; ++i){
        if(i == idx)
            wattron(win, A_REVERSE);
        mvwprintw(win, (int)(maxMag/4+i), (int)(maxSzel/2-(fomenuMezok[i].size())/2), fomenuMezok[i].c_str());
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

/*!
 * E a függvény a program szíve. Innen tudunk átlépni a szerkesztőmenübe, vagy épen innen tudjuk elindítani a
 * jegyvételt. Ugyanakkor itt történik a vonatok listájának inicializálása a program indulása után, vagy
 * annak futása végén, itt is történik egy fájlba mentés a biztonság kedvéért. Erre nem lenne szükség, hisz
 * minden az 'init.txt' fájl tartalmát módosító lépés után történik egy mentés, de biztos, ami tuti! A program
 * ebben a függvényben kezeli le a főmenüre érkező inputokat. Itt  példányosítjuk a leendő tárolót
 * 'Vonat' objektumokra a 'STACK'-en, hogy a program futása végén meghívódjon annak destruktora, ezáltal felszabadítva
 * a program futása során használt dinamikusan foglalt memóriát. Itt inicializáljuk azt a 'Window' objektumot is
 * amivel alapértelmezetten dolgozni fogunk a program többi részében. Ennek paramétereit úgy határozzuk meg, hogy
 * a 'Standard screen' paramétereit kérje le, és ehhez viszonyítson. Itt indítjuk, ás zárjuk le az 'ncurses' könyvtárat is.
 */
void fomenu_main() {
    //ncurses START
    initscr();

    noecho();
    cbreak();
    //kurzor eltűntetése
    curs_set(0);
    start_color();
    init_pair(5, COLOR_CYAN, COLOR_RED);

    size_t maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    wattron(stdscr,COLOR_PAIR(5));
    wborder(stdscr, '|','|','-','-', 0,0,0,0);
    wattroff(stdscr,COLOR_PAIR(5));
    wrefresh(stdscr);

    WINDOW* menuWin = newwin((int)maxY-2, (int)maxX-2 , 1, 1);


    //Első inicializálása a keretnek
    refresh();
    keypad(menuWin, true);

    std::string jelsz;
    Tarolo<Vonat> vonatok;
    initialize(jelsz, vonatok);

    bool quit = false;
    int choice;
    int sorsz = 0;

    while (!quit) {
        /*
         * Második inicializálása a keretnek, hogy a
         * visszatérések után is kirajzolódjon. Az elsőt
         * nem bántja, a refresh() csak akkor "renderel", ha
         * van változás.
         */
        wclear(menuWin);

        fomenuKiir(menuWin, sorsz, maxX, maxY);
        choice = wgetch(menuWin);
        switch (choice) {
            case KEY_UP:
                if(sorsz > 0)
                    --sorsz;
                break;
            case KEY_DOWN:
                if(sorsz < 2)
                    ++sorsz;
                break;
                //A KEY_ENTER nem működött, a 10 biztosan jó
            case 10:
                switch (sorsz) {
                    case 0:
                        jegyvetel_begin(menuWin,vonatok, maxX, maxY);
                        break;
                    case 1:
                        vonatok = jelszo(menuWin, jelsz, vonatok);
                        break;
                    case 2:
                        quit = true;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    //delete menuWin;
    delwin(menuWin);
    fajlba_ment(jelsz, vonatok);

    //Ncurses END
    endwin();
}
