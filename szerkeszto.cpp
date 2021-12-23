

/**\file szerkeszto.cpp
 * \brief A szerkesztő menüjének megvalósítása
 * \details
 * Ebben a modulban valósítottam meg az összes olyan függvényt, ami ahhoz kellhet,
 * hogy a nyilvántartó rendszerben szerkesztő műveleteket lehessen végrehajani. Gondolok itt például arra, hogy
 * egy vonatot hozzáadjunk a már meglévő vonatok listájához, vagy egyed kivegyünk a listából. Ez a menürész egy
 * jelszóval érhető el a programban, ami kezdetben: 1234. A jelszó módosítható ebből a menüpontból.
 * A jelszó tartalmazhat kis-és nagybetűket, írásjeleket, számokat. A program a futás befejeztével az init.txt-be menti
 * a jelszót, igy az a következő induláskor sem állítódik el.
 * A menüben értelemszerűen lehet mozogni a billentyűzet nyilaival, illetve az ENTER és ESC billentyűk segítségével.
 * A rendszer könnyen végigvezeti a felhasználót a vonathozzáadás lépésein, illetve kifejezetten egyszerűen lehet
 * törölni egy adott vonatot a listából. Itt lehet szimplán csak megtekinteni a rendelkezésre álló vonatokat is.
 */


#include "szerkeszto.h"

/**@brief A függvény egy 'Window' tipusú elemre, amit pointerként vesz át, kiírja a redszerben szereplő vonatok listáját,
 * @param win a 'Window', amire kiirunk, pointerként átvéve
 * @param kezdo a lista azon elemének indexe, amelyiktől kezdődően szeretnénk annyit kiirni, amennyi kifér a kijelzőre
 * @param maxElemKifer hogy mennyi vonat fér ki a kijelzőre
 * @param mX a 'win' maximális szélessége
 * @param vonatok 'Vonat' tipusú objektumokat tároló tároló, referenciaként átvéve
 */
void megtekint_kiir(WINDOW* win,Tarolo<Vonat>& vonatok, size_t kezdo, size_t maxElemKifer, size_t mX){

    wclear(win);
    if(vonatok.empty()){
        mvwprintw(win,1, (int)(mX/2-strlen("Nincs megjelenítheto vonatod!")/2),
                  "Nincs megjelenítheto vonatod!\n");
        mvwprintw(win,2, (int)(mX/2-strlen("Nyomj ESC-et a visszalepeshes!")/2),
                  "Nyomj ESC-et a visszalepeshes!");

    }else {
        mvwprintw(win, 0, (int) (mX / 2 - strlen("Nyomj ESC-et a visszalepeshes! Lapozas: Bal-Jobb nyilak.") / 2),
                  "Nyomj ESC-et a visszalepeshes! Lapozas: Bal-Jobb nyilak.\n");

        if (vonatok.size() - kezdo > maxElemKifer) {
            for (size_t i = kezdo; i < kezdo + maxElemKifer; ++i)
                vonatok[i].kiir(win);
        } else {
            for (size_t i = kezdo; i < vonatok.size(); ++i)
                vonatok[i].kiir(win);
        }
    }

    wrefresh(win);
}

/**
 * Ezt a függvényt a program arra használja, hogy a felhasználó mozogni tudjon a kiírt listában a nyilak segitségével.
 * Bal nyil: balra lapozás, Jobb nyil: jobbra lapozás. Ebből a függvényből hívódik meg a "megtekint_kiir" függvény is.
 * ESC - el lehet kilépni a megtekintőből.
 * @param win 'Window' objektum, amire irni szeretnénk majd, pointerként
 * @param vonatok a 'Vonat' objektumokat tároló tároló, referenciaként átvéve
 * @param mX 'win' maximális szélessége
 * @param mY 'win' maximális magassága
 */
void vonatokat_megtekint(WINDOW*win, Tarolo<Vonat> & vonatok, size_t mX, size_t mY){
    int c;
    bool quit = false;
    size_t kezdo = 0;
    size_t maxElemszam = (mY-4)/3;

    //KEY_ENTER kellene, de a 10 a tuti
    while(!quit){

        wclear(win);
        megtekint_kiir(win,vonatok, kezdo,maxElemszam, mX);
        c = wgetch(win);

        switch (c) {
            case KEY_LEFT:
                if(kezdo > 0)
                    kezdo -= maxElemszam;
                break;
            case KEY_RIGHT:
                if(vonatok.size()-kezdo > maxElemszam)
                    kezdo += maxElemszam;
                break;
            case 27:
                quit = true;
                break;
            default:
                break;
        }
    }
}

/**
 * A függvény létrehoz egy új 'Vonat' objektumot, és hozzáadja az eddigi
 * vonatok listájához. Itt kéri be a program az új vonat, és a hozzá tartozó kocsik paramétereit a felhasználótól.
 * Létrehozza a megfelelő új objektumokat, majd a tárolóba helyezi őket.
 * @param win 'Window' objektum, amire irhat a program, és amiről olvashat be inputot, pointerként átvéve
 * @param vonatok a 'Vonat' objektumokat tároló tároló, referenciaként átvéve
 * @param mX 'win' maximális szélessége
 * @param mY 'win' maximális magassága
 * @param jelszo a szerkesztőhöz tartozó jelszó, hogy a változtatások után egyből lehessen fájlba menteni
 * @return az átvett táróló az új vonattal
 */
Tarolo<Vonat>& vonat_hozzaad(WINDOW * win, Tarolo<Vonat>& vonatok, size_t mX, size_t mY, std::string& jelszo){
    //Egy vonat paraméterei
    size_t vonatszam = 0;
    std::string honnan;
    std::string hova;
    Ido indulas;
    Ido erkezes;
    size_t jegyar = 0;

    //Hány kocsi tartozik a vonathoz
    size_t kocsikSzama = 0;

    //Egy kocsi paraméterei
    size_t kocsiszam = 0;
    size_t ferohely = 0;
    bool osztaly;

    //Egy változó, hogy letöröljük a kijelzőt,
    // ha már nem férne ki a következő kiírandó adat.
    size_t ell = 0;

    //Hogy látszódjanak a beírt karakterek.
    echo();
    nocbreak();
    //Hogy eltűnjön a menü
    wclear(win);

    wprintw(win, "Mi legyen a vonat szama?\n");
    wrefresh(win);
    wscanw(win, (char*)"%u", &vonatszam);
    ell+=2;

    wprintw(win, "\nHonnan indul a vonat?\n");
    wrefresh(win);
    int ch;
    ch = wgetch(win);
    while(ch != '\n'){
        honnan.push_back(ch);
        ch = wgetch(win);
    }
    ell+=3;

    wprintw(win, "\nHova tart a vonat?\n");
    wrefresh(win);
    ch = wgetch(win);
    while(ch != '\n'){
        hova.push_back(ch);
        ch = wgetch(win);
    }
    ell+=3;
    if(ell >= mY-4)
        wclear(win);

    wprintw(win, "\nHany ora hany perckor indul?\n");
    wprintw(win, "Ora: ");
    wrefresh(win);
    ch = wgetch(win);
    while(ch != '\n'){
        indulas.ora.push_back(ch);
        ch = wgetch(win);
    }
    ell+=3;


    wprintw(win, "\nPerc: ");
    wrefresh(win);
    ch = wgetch(win);
    while(ch != '\n'){
        indulas.perc.push_back(ch);
        ch = wgetch(win);
    }
    ell+=2;
    if(ell >= mY-4)
        wclear(win);


    wprintw(win, "\nHany ora, hany perckor erkezik a vonat?\n");
    wprintw(win, "Ora: ");
    wrefresh(win);
    ch = wgetch(win);
    while(ch != '\n'){
        erkezes.ora.push_back(ch);
        ch = wgetch(win);
    }
    ell+=3;


    wprintw(win, "\nPerc: ");
    wrefresh(win);
    ch = wgetch(win);
    while(ch != '\n'){
        erkezes.perc.push_back(ch);
        ch = wgetch(win);
    }
    ell+=2;
    if(ell >= mY-4)
        wclear(win);

    wprintw(win, "\nMennyibe kerul az alapjegy? (masodosztaly, kedvezmeny nelkul)\n");
    wrefresh(win);
    wscanw(win, (char*)"%u", &jegyar);
    ell+=3;
    if(ell >= mY-4)
        wclear(win);

    wprintw(win, "\nHany kocsival kozlekedik a vonat?\n");
    wrefresh(win);
    wscanw(win, (char*)"%u", &kocsikSzama);
    ell+=3;
    if(ell >= mY-4)
        wclear(win);

    Vonat v0(vonatszam,jegyar, honnan.c_str(), hova.c_str(),indulas, erkezes);

    int a = 0;

    //Kocsik paramétereinek bekérése
    for(size_t i = 0; i<kocsikSzama; ++i){
        wclear(win);
        echo();
        nocbreak();
         wprintw(win, "\nMi legyen a(z) %d. kocsi szama?\n", i+1);
         wrefresh(win);
         wscanw(win, (char*)"%u", &kocsiszam);

        wprintw(win, "\nHany ferohelyes a kocsi?\n");
        wrefresh(win);
        wscanw(win, (char*)"%u", &ferohely);

        wprintw(win, "\nMilyen osztalyu a kocsi? (2 - masod, 1 - elso)\n");
        wrefresh(win);
        wscanw(win, (char*)"%u", &a);

        //Aktuális kocsi hozzáadása a vonathoz.
        osztaly = a != 2;

        Kocsi k0(kocsiszam, ferohely, ferohely, osztaly);
        std::cout << k0.getSorsz() << k0.getSzabad() << k0.getMeret() << k0.getOsztaly() << "\n";
        std::cin.get();
        v0.kocsik.push_back(k0);

        wclear(win);
        mvwprintw(win,2, (int)(mX/2-strlen("A %d. kocsit hozzaadtam a vonathoz.")/2), "A %d. kocsit hozzaadtam a vonathoz.\n\n\n", i+1);
        if(i != kocsikSzama-1){
            mvwprintw(win,3, (int)(mX/2-strlen("Nyomj ENTER-t a %d. kocsi hozzaadasahoz")/2), "Nyomj ENTER-t a %d. kocsi hozzaadasahoz", i+1);
        }else{
            mvwprintw(win,3, (int)(mX/2-strlen("Nyomj ENTER-t a befejezeshez.")/2), "Nyomj ENTER-t a befejezeshez.", i+1);
        }
        wrefresh(win);

        noecho();
        cbreak();
        int c = 11;
        while(c != 10)
            c = wgetch(win);
    }

    //Ha esetleg 0. db kocsival közlekedne a vonat.
    noecho();
    cbreak();

    vonatok.push_back(v0);
    fajlba_ment(jelszo, vonatok);

    wclear(win);
    mvwprintw(win,2,
            (int)(mX/2-strlen("A vonatot hozzaadtam a vonatok listajahoz. Nyomj ENTER-t a visszalepeshez.")/2),
            "A vonatot hozzaadtam a vonatok listajahoz. Nyomj ENTER-t a visszalepeshez.");
    wrefresh(win);
    int c = 11;
    while(c != 10){
        c = wgetch(win);
    }

    return vonatok;
}

/**
 * A függvény a paraméterként átvett WINDOW objektumra negjelenít annyi Vonat objektumot, amennyi
 * kifér rá, és a paraméterként átvett indexű elemet máshogy színezi.
 * @param win -'Window' objektum, amire írni szeretnénk majd, pointerként
 * @param vonatok a 'Vonat' objektumokat tároló tároló, referenciaként átvéve
 * @param kezdo hogy a Tároló hányadik elemétől írjon ki annyit, amennyi kifér a kijelzőre
 * @param idx hogy melyik elemét színezze másképp a tárolónak
 * @param maxElemKifer hogy mennyi elem fér a kijelzőre
 * @param mX 'win' maximális szélessége
 */
void indexel_kiir(WINDOW* win, Tarolo<Vonat>& vonatok,size_t kezdo, size_t idx, size_t maxElemKifer, size_t mX){
    wclear(win);
    if(vonatok.empty()){
        mvwprintw(win,1, (int)(mX/2-strlen("Nincs megjelenítheto vonatod!")/2),
                  "Nincs megjelenítheto vonatod!\n");
        mvwprintw(win,2, (int)(mX/2-strlen("Nyomj ESC-et a visszalepeshes!")/2),
                  "Nyomj ESC-et a visszalepeshes!");

    }else {
        init_pair(1, COLOR_RED, COLOR_YELLOW);
        init_pair(2, COLOR_YELLOW, COLOR_RED);

        if (vonatok.size() - kezdo > maxElemKifer) {
            for (size_t i = kezdo; i < kezdo + maxElemKifer; ++i) {
                if (i == idx) {
                    vonatok[i].kiir(win, 1, 2);
                } else {
                    vonatok[i].kiir(win);
                }
            }
        } else {
            for (size_t i = kezdo; i < vonatok.size(); ++i) {
                if (i == idx) {
                    vonatok[i].kiir(win, 1, 2);
                } else {
                    vonatok[i].kiir(win);
                }
            }
        }
    }
    wrefresh(win);
}

/**
 * Ezt a függvényt használja a program, hogy töröljön egy adott elemet a vonatok tárolójából. Egyszerűen haszálható
 * a nyilak, és az ENTER segitségével. Kezeli azt is, hogyha nincs vonat a tárolóban.
 * @param win 'Window' objektum, amire az "indexel_kiir" függvény majd megejeleniteni fog, pointerként átvéve
 * @param vonatok a 'Vonat' objektumokat tároló tároló
 * @param mX 'win' maximális szélessége
 * @param mY 'win' maximális magassága
 * @param jelszo a szerkesztőhöz tartozó jelszó, hogy a változtatások után egyből lehessen fájlba menteni
 * @return az átvett tároló a kiválasztott vonat nélkül
 */
Tarolo<Vonat>& vonat_torol(WINDOW * win, Tarolo<Vonat>& vonatok, size_t mX, size_t mY, std::string& jelszo){

    mvwprintw(win,0, (int)(mX/2-strlen("Melyik vonatot toroljem? (Kivalasztas: ENTER, Lapozas: Bal-Jobb nyilak.)\n")/2) ,"Melyik vonatot toroljem? (Kivalasztas: ENTER, Lapozas: Bal-Jobb nyilak.)\n");
    mvwprintw(win, 1, (int)(mX/2-strlen("Nyomj ESC-et a visszalepeshez!")/2) ,"Nyomj ESC-et a visszalepeshez!\n\n\n");
    wrefresh(win);

    WINDOW * wIrasra = newwin((int)mY-4,(int)mX-2,3,1);
    keypad(wIrasra, true);

    size_t idx = 0;
    int ch;
    bool quit = false;
    size_t kezdo = 0;
    size_t maxElemszam = (mY-4)/3;

    while(!quit){
        wclear(wIrasra);
        indexel_kiir(wIrasra,vonatok,  kezdo, idx, maxElemszam,mX);
        ch = wgetch(wIrasra);

        switch (ch) {
            case KEY_UP:
                if(idx > 0)
                    --idx;
                if(idx < kezdo)
                    kezdo-=maxElemszam;
                break;
            case KEY_DOWN:
                if(idx < vonatok.size()-1)
                    ++idx;
                if(idx > kezdo+maxElemszam-1)
                    kezdo += maxElemszam;
                break;
            case KEY_RIGHT:
                if(vonatok.size()-kezdo > maxElemszam) {
                    kezdo += maxElemszam;
                    idx = kezdo;
                }
                break;
            case KEY_LEFT:
                if(kezdo > 0){
                    kezdo-=maxElemszam;
                    idx = kezdo;
                }
                break;
            case 10:
                quit = true;
                break;
            case 27:
                return vonatok;
            default:
                break;
        }
    }
    //wdeleteln(wIrasra);

    vonatok.pull(idx);

    fajlba_ment(jelszo, vonatok);

    wclear(win);
    mvwprintw(win,0,(int)(mX/2-strlen("A vonatot toroltem. Nyomj ENTER-t a visszalepeshez.")/2),
            "A vonatot toroltem. Nyomj ENTER-t a visszalepeshez.");
    wrefresh(win);

    int c = 11;
    while(c != 10){
        c = wgetch(win);
    }
    delwin(wIrasra);
    return vonatok;
}

/**
 * Ez a függvény rossz jelszó megadása esetén kiir egy paraméterként átvett 'Window' objektumra,
 * és nem engedi tovább a felhasználót, amíg nem nyom ESC-et.
 * @param win 'Window' objektum, amire írni szeretnénk majd, pointerként átvéve
 * @param mX 'win' maximális szélessége
 */
void rossz_jelszo(WINDOW* win, size_t mX){
    wclear(win);
    mvwprintw(win, 1, (int)mX/4, "HIBAS JELSZO! VISSZZALEPESHEZ NYOMJ ESC-ET!\n");
    wrefresh(win);

    int c = 11;
    while(c != 27){
        c = wgetch(win);
    }
}

/**
 * Ez a függvény a szerkesztő menü jelszavának módosításán vezeti végig a felhaszálót.
 * @param win 'Window' objektum, amire írhat a program, és amiről olvashat be inputot, pointerként átvéve
 * @param jelszo a jelszó std::string objektum, amit módositani szeretnénk, referenciaként átvéve
 * @param mX 'win' maximális szélessége
 * @param mY 'win' maximális magassága
 * @param vonatok a vonatok listája, hogy jelszóváltoztatás után egyből lehessen fájlba menteni az új adatokat
 */
void jelszo_modosit(WINDOW *win, std::string &jelszo, size_t mX, size_t mY, Tarolo<Vonat>& vonatok){
    wclear(win);
    const char*p = "Mi legyen az uj jelszo?";
    mvwprintw(win,(int)mY/2, (int)(mX/2-strlen(p)/2) ,p);
    mvwprintw(win, (int)mY/2+1, (int)(mX/2-10), "Uj jelszo: ");
    wrefresh(win);

    std::string uj;
    nocbreak();
    echo();
    int ch = mvwgetch(win, mY/2+1, mX/2+1);
    while(ch != '\n'){
        uj.push_back(ch);
        ch = mvwgetch(win, mY/2+1, mX/2+1);
    }

    noecho();
    cbreak();

    jelszo = uj;

    fajlba_ment(jelszo, vonatok);

    mvwprintw(win,(int)mY/2+3,(int)(mX/2-strlen("Az uj jelszot mentettem. Nyomj ENTER-t a visszalepeshez!")/2) , "Az uj jelszot mentettem. Nyomj ENTER-t a visszalepeshez!");
    wrefresh(win);

    int c = 11;
    while(c != 10){
        c = wgetch(win);
    }
}

/**
 * A főmeüből közvetlenül ebbe a függvénybe ugrik a program. Itt legelőször elkéri a jelszót a felhasználótól,
 *  majd helyes jelszó esetén továbblép a "szerkeszto_menu" függvénybe. Rossz jelszó esetén meghívja a
 *  "rossz_jelszo" függvényt, majd visszatér a főmenübe.
 * @param win 'Window' objektum, amire írni, amiről olvasni szeretnénk majd, pointerként átvéve
 * @param jelszo std::string jelszo objektum referenciaként, hogy módosítani is lehessen adott esetben
 * @param vonatok a Vonat objektumokat tároló tároló
 * @return az átvett tároló a rajta végzett módosítások után
 */
Tarolo<Vonat>& jelszo(WINDOW *win, std::string& jelszo, Tarolo<Vonat>& vonatok) {
    size_t maxX, maxY;
    getmaxyx(win,maxY, maxX);

    wclear(win);
    mvwprintw(win,(int)maxY/4,(int)(maxX/2-strlen("Kerem a jelszot!\n")/2), "Kerem a jelszot!\n");
    wrefresh(win);

    nocbreak();
    echo();

    std::string jel;

    int ch = mvwgetch(win, (int)maxY/4+1, (int)maxX/2);
    while(ch != '\n'){
        jel.push_back(ch);
        ch = mvwgetch(win, (int)maxY/4+1, (int)maxX/2);
    }
    noecho();
    cbreak();

    if (jel != jelszo) {
        rossz_jelszo(win, maxX);
        //HA rossz a jelszó, térjünk vissz a főmenübe.
        return vonatok;
    }

    //Ha jó a jelszó, nyissuk meg a szerkesztőmenüt.
    vonatok = szerkeszto_menu(win, jelszo, vonatok);
    return vonatok;
}

/**
 * Ez a függvény a szerkesztő menüjének menüpontjait hivatott kiírni egy paraméterként átvett 'Window' objektumra.
 * Hasonló az "indexel_kiir" függvényhez. A paraméterként átvett indexű elemre az ncurses könyvtár A_REVERSE
 * attribútumát alkalmazza.
 * @param win 'Window' objektum, amire írni szeretnénk majd, pointerként átvéve
 * @param idx hogy melyik indexű elemre alkalmazza az attribútumot
 * @param mX 'win' maximális szélessége
 * @param mY 'win' maximális magassága
 */
void szerkeszto_kiir(WINDOW * win, size_t idx, size_t mX, size_t mY){
    std::string szerkesztoMuveletek[5] = {"Vonatok megtekintese\n",
                                          "Vonat hozzaadasa\n",
                                          "Vonat torlese\n",
                                          "Jelszo modositasa\n",
                                          "Visszalepes"};

    for(size_t i = 0; i<5; ++i){
        if(i == idx)
            wattron(win, A_REVERSE);
        mvwprintw(win, (int)(mY/4+i), (int)(mX/2-szerkesztoMuveletek[i].size()/2), szerkesztoMuveletek[i].c_str());
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

/**
 * Ez a függvény a szerkesztő menü "motorja". Lényegében ugyanúgy működik, mint a "fomenu_main" függvény, csupán
 * más szubrutinokat hív meg.
 * @param menuWin 'Window' objektum, amire írni, amiről olvasni szeretnénk majd, pointerként átvéve
 * @param jelszo std::string jelszo objektum referenciaként, hogy módosítani is lehessen adott esetben
 * @param vonatok a Vonat objektumokat tároló tároló
 * @return az átvett tároló a rajta végzett módosítások után
 */
Tarolo<Vonat>& szerkeszto_menu(WINDOW * menuWin, std::string& jelszo, Tarolo<Vonat> & vonatok){

    bool quit = false;
    int c;
    int sorsz = 0;

    while (!quit) {


        wclear(menuWin);

        size_t mX,mY;
        getmaxyx(stdscr,mY,mX);

        szerkeszto_kiir(menuWin, sorsz, mX,mY);
        c = wgetch(menuWin);

        switch (c) {
            case KEY_UP:
                if(sorsz>0)
                    --sorsz;
                break;
            case KEY_DOWN:
                if(sorsz<4)
                    ++sorsz;
                break;
            case 10:
                switch (sorsz) {
                    case 0:
                        vonatokat_megtekint(menuWin,vonatok, mX-2, mY-2);
                        break;
                    case 1:
                        vonatok = vonat_hozzaad(menuWin,vonatok, mX, mY, jelszo);
                        break;
                    case 2:
                        vonatok = vonat_torol(menuWin,vonatok, mX, mY, jelszo);
                        break;
                    case 3:
                        jelszo_modosit(menuWin,jelszo, mX, mY, vonatok);
                        break;
                    case 4:
                        quit = true;
                        break;
                    default:
                        return vonatok;
                }
            default:
                break;
        }
    }
    return vonatok;
}
