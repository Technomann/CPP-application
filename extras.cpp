
/**
 * \file extras.cpp
 * \brief Ebben a fájlban valósítotam meg az 'extras.h' struktúráinak 'operator=' és 'operator<<' túlterheléseit.
 */

#include "extras.h"

Helyezes& Helyezes::operator=(const Helyezes &a) {
    if(&a != this){
        kocsiszam = a.kocsiszam;
        helyszam = a.helyszam;
    }
    return *this;
}

Ido& Ido::operator=(const Ido &a) {
    if(this != &a) {
        ora = a.ora;
        perc = a.perc;
    }
    return * this;
}



//! 'Operator<<' túlterhelése 'Ido' struktúrára
std::ostream& operator<<(std::ostream& os, const Ido& a)  {
    os << a.ora << ":" << a.perc;
    return os;
}

//! 'Operator<<' túlterhelése 'Helyezes' struktúrára
std::ostream& operator<<(std::ostream& os, const Helyezes& a){
    os << "Kocsiszam: " << a.kocsiszam << "  " << "\nHely: " << a.helyszam << "\n";
    return os;
}

//! 'Operator<<' túlterhelése 'Datum' struktúrára
std::ostream& operator<<(std::ostream& os, const Datum& a){
    os << a.ev << "." << a.ho << "." << a.nap << "." << std::endl;
    return os;
}