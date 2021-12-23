
/**
 * \file vetel.cpp
 * \brief A jegyvétel menetének megvalósítása
 * \details
 * Ebben a modulban valósítottam meg azt, hogy hogyan tud a felhasználó jegyet venni a rendszerben szereplő vonatkora.
 * Itt található az összes olyan függvénynek a definíciója, ami ehhez kellhet. Itt a többi modultól eltően nem egy
 * menürendszer található, hanem lineárisan tudunk végighaladni a jegyvétel lépésein. Itt kéri el a program a
 * jegy felhasználójának adatait, illetve könnyen kiválasztható, hogy melyik vonatra szeretnénk jegyet venni. A
 * folyamaton való végighaladás szintén egyértelmű, néhol a nyilakat, ENTER-t, ESC-et kell használni, néhol pedig
 * a billentyűzet egyéb gombjait. A jegyet vásárlás után a program egy .txt fájlba helyezi el a program mappájában, ahol
 * a felhasználó által bevitt 'Név' lesz a fájl neve. Ezután visszatérhetünk a főmenübe, vagy kezdhetjük előről a
 * jegyvételt.
 */

#include "vetel.h"

/**
 * A függvény visszaadja, hogy van-e a paraméterként átvett vonatban, a megfelelő osztályon még szabad hely.
 * @param v a 'Vonat' objektum, amiben keresünk, referenciaként átvéve
 * @param osztaly hogy első- vagy másodosztályon keresünk szabad helyet. 'True', ha elsőn.
 * @return 'true', ha van hely, egyébként 'false'
 */
bool van_meg_helyO(const Vonat &v, bool osztaly) {
    for (size_t i = 0; i < v.kocsik.size(); ++i) {
        if (v.kocsik[i].getOsztaly() == osztaly) {
            if (v.kocsik[i].getSzabad() != 0)
                return true;
        }
    }
    return false;
}

/**
 * A függvény visszaadja, hogy van-e szabad hely a paraméterként átvett vonaton, tetszőleges osztályon.
 * @param v a 'Vonat' objektum, amiben keresünk, referenciaként átvéve
 * @return 'true', ha van hely, egyébként 'false'
 */
bool van_meg_hely(const Vonat &v) {
    for (size_t i = 0; i < v.kocsik.size(); ++i) {
        if (v.kocsik[i].getSzabad() != 0)
            return true;
    }
    return false;
}

/**
 * Ez a függvény egy "igen-nem" opciót jelenít meg a paraméterként átvett 'Window' objektumon. Paraméterként veszi át
 * azt is, hogy az Igen-re, vagy a Nem-re alkalmazza az 'ncurses' könyvtár 'A_REVERSE' attribútumát. Paraméterezhető
 * az is, hogy milyen szöveget jelenítsen meg az opciók felett (pl.: "Akarsz még jegyet venni?").
 * @param win 'Window' objektum, amire írni szeretnénk, pointerként átvéve
 * @param idx hogy melyik elemre alkalmazzuk az attribútumot, 0 esetén az Igen-re, 1 esetén a Nem-re
 * @param mX 'win' maximális szélessége
 * @param szoveg a szöveg, amit az opciók felett szeretnénk megjeleníteni
 */
void ynKiir(WINDOW * win, int idx, size_t mX, const char* szoveg){
    std::string yn[2] = {"Igen\n", "Nem\n"};

    wclear(win);
    mvwprintw(win,0, (int)(mX/2-strlen(szoveg)/2) ,szoveg);

    for(int i = 0; i<2; ++i){
        if( i == idx)
            wattron(win, A_REVERSE);
        mvwprintw(win, i+1, i+1, yn[i].c_str());
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

/**
 * Ez a függvény kezeli le, egy "igen-nem" választás esetén a billentyűrol érkező inputot (Le-Fel nyilak, ENTER).
 * @param win 'Window' objektum, amire írni szeretnénk majd a 'yn_kiir' függvénnyel
 * @param mX 'win' maximális szélessége
 * @param szoveg a szöveg, amit ki szeretnénk írni az "igen-nem" opciók fölé (pl.: "Akarsz még jegyet venni?")
 * @return 'true', ha az Igen-re nyomott a felhasználó, 'false', ha a Nem-re
 */
bool yn(WINDOW* win,size_t mX, const char* szoveg){

    int c;
    bool quit = false;
    int idx = 0;

    while(!quit) {
        wclear(win);
        ynKiir(win, idx, mX, szoveg);
        c = wgetch(win);
        switch (c) {
            case KEY_DOWN:
                if(idx < 1)
                    ++idx;
                break;
            case KEY_UP:
                if(idx > 0)
                    --idx;
                break;
            case 10:
                quit = true;
                break;
            default:
                break;
        }
    }
    wclear(win);
    return idx == 0;
}

/**
 * Egy visszalépési "csapda", ami paraméterként veszi át, hogy mivel lehessen ki/visszalépni, és, hogy mit írjon ki
 * ehhez.
 * @param win 'Window' objektum, amire írni szeretnénk majd, amiről várjuk az inputot
 * @param mivel Az ASCII kódja, hogy melyik billentyűvel szeretnénk visszalépni
 * @param mX 'win' maximális szélessége
 * @param szoveg a kiírandó szöveg (pl.: "Visszalépéshez nyomj ESC-et!")
 */
void vissza(WINDOW *win, int mivel, size_t mX,const char *szoveg) {
    int c = 11;
    wclear(win);
    mvwprintw(win,0, (int)(mX/2-strlen(szoveg)/2) ,szoveg);
    wrefresh(win);
    while (c != mivel) {
        c = wgetch(win);
    }
}

/**
 * Maga a jegyvásárlás itt történik. A függvény végigvezeti a felhasználót a jegyvásárlás lépésein, értelemszerűen.
 * A függvény kezeli azt is, ha nincs már hely az adott vonaton, vagy az adott osztályon. Utóbbi esetben felkínálja
 * a felhasználónak, hogy akar-e a másik osztályra inkább jegyet venni, és ha nem, akkor visszalép a 'jegyvetel_begin'
 * függvénybe. Jegyvétel után megkérdezi a felhasználót, hogy szeretne-e egy másik jegyet is venni. Itt készül el
 * a jegyet tartalmazó .txt is.
 * @param win 'Window' objektum, amire kiírni fogunk majd, és ahonnan várjuk az inputot, pointerként átvéve
 * @param mX 'win' maximális szélessége
 * @param v a kiválasztott 'Vonat' objektum, amire jegyet szeretnénk venni
 * @return 'true, ha nem szeretnénk már jegyet venni, 'false', ha igen
 */
bool vasarlas(WINDOW * win,size_t mX, Vonat &v) {

    bool vanSzabadHely = van_meg_hely(v);
    if (!vanSzabadHely) {
        vissza(win, 10,mX, "Nincs hely ezen a vonaton. Visszalepeshez nyomj ENTER-t!");
        return false;
    }

    std::string nev;
    wclear(win);
    echo();
    nocbreak();
    wprintw(win, "Milyen nevre szeretnel jegyet venni?\n");
    wrefresh(win);
    int ch = wgetch(win);
    while(ch != '\n'){
        nev.push_back(ch);
        ch = wgetch(win);
    }

    Datum dat;
    wprintw(win, "\nMi a szuletesi datumod? (pl.: 2000.01.01)\n");
    wprintw(win, "Ev: ");
    wrefresh(win);
    wscanw(win, (char *)"%d", &dat.ev);

    wprintw(win, "Honap: ");
    wrefresh(win);
    wscanw(win, (char*)"%d", &dat.ho);

    wprintw(win, "Nap: ");
    wrefresh(win);
    wscanw(win, (char*)"%d", &dat.nap);

    wprintw(win, "\nMilyen osztalyra szeretnel jegyet venni? (1 - elso, 2 - masod)\n");
    wrefresh(win);

    bool osztaly;
    int a = 2;
    wscanw(win, (char*)"%d", &a);
    osztaly = a != 2;

    vanSzabadHely = van_meg_helyO(v, osztaly);

    if (!vanSzabadHely){
        noecho();
        cbreak();
        wclear(win);

        bool szeretne = yn(win,mX,"Erre az osztalyra nincs hely. Esetleg a masikra?\n");
        if(!szeretne){
            wclear(win);
            return false;
        }else{
            if(osztaly){
                osztaly = false;
            } else
                osztaly = true;
        }
        echo();
        nocbreak();
    }

    wclear(win);
    wprintw(win, "Van diakkedvezmenyed? (0 - nincs, 1 - van)\n");
    wrefresh(win);

    bool diak;
    wscanw(win, (char*)"%d", &a);

    diak = a == 1;
    size_t fizetendo = v.getAr();
    if (osztaly)
        fizetendo *= 1.4;
    if (diak)
        fizetendo /= 2;

    Jegy jegy(nev.c_str(), dat, v.getIndoloAll(),
              v.getErkezoAll(), v.getIndulas(), v.getErkezes(),
              v.jegyetElhelyez(osztaly), osztaly, diak, fizetendo);

    nev += ".txt";
    std::fstream file;
    file.open(nev, std::ios::out);
    file.seekg(0, std::ios::beg);
    jegy.jegyetKiir(file);
    file.close();

    wclear(win);
    mvwprintw(win,0, (int)(mX/2-strlen("A jegyet kinyomtattam. Nyomj ENTER-t a továbblépéshez.")/2),
            "A jegyet kinyomtattam. Nyomj ENTER-t a továbblépéshez.");
    wrefresh(win);
    cbreak();
    noecho();
    int c = 11;
    while(c != 10){
        c = wgetch(win);
    }

    bool szeretne = yn(win, mX, "Szeretnel meg jegyet venni?\n");
    wclear(win);
    return !szeretne;
}

/**
 * Ide ugrunk a 'fomenu_main' függvényből, amennyiben a felhasználó el szeretné kezdeni a jegyvásárlás folyamatát.
 * Itt jelenítődnek meg a listában szereplő vonatok, és itt kezelődik le a kiválasztás is.
 * @param menuWin 'Window' objektum, amire írni fogunk, amiről várjuk az inputot, pointerként átvéve a 'fomenu_main'-től
 * @param vonatok a rendszerben szereplő 'Vonat' objektumokat tároló tároló, referenciaként átvéve, de nem módosítjuk
 * @param mX 'menuWin' maximális szélessége
 * @param mY 'menuWin' maximális magassága
 */
void jegyvetel_begin(WINDOW * menuWin, Tarolo<Vonat> &vonatok, size_t mX, size_t mY) {
    WINDOW * wIrasra = newwin((int)mY-4,(int)mX-2,3,1);
    keypad(wIrasra, true);

    int idx = 0;
    int c;
    bool quit = false;
    size_t kezdo = 0;
    size_t maxElemszam = (mY-4)/3;

    while (!quit) {
        mvwprintw(menuWin,0, (int)(mX/2-strlen("Melyik vonatra szeretnel jegyet venni? (Kivalasztas: ENTER) Lapozas: Bal-Jobb nyilak.\n")/2) ,"Melyik vonatra szeretnel jegyet venni? (Kivalasztas: ENTER) Lapozas: Bal-Jobb nyilak.\n");
        mvwprintw(menuWin, 1, (int)(mX/2-strlen("Nyomj ESC-et a visszalepeshez!")/2) ,"Nyomj ESC-et a visszalepeshez!\n\n\n");
        wrefresh(menuWin);
        wclear(wIrasra);

        indexel_kiir(wIrasra,vonatok , kezdo,idx,maxElemszam,mX);
        c = wgetch(wIrasra);

        switch (c) {
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
                //KEY_ENTER kéne, de a 10 mindig működik (CR).
            case 10:
                if(!vonatok.empty()) {
                    wclear(menuWin);
                    quit = vasarlas(menuWin, mX, vonatok[idx]);
                }
                break;
                //Hogy ESC-el ki lehessen lépni.
            case 27:
                quit = true;
                break;
            default:
                break;
        }
    }
}
