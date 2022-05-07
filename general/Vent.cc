#include <iostream>
#include "Vent.h"


bool Vent::dans_champ(ObjetMobile const& M) const {
    Vecteur d(origine-M.getP());
    if ((d*normale>0) and (d*normale<profondeur)
    and (d*~longueur>0) and (d*~longueur<longueur.norme())
    and (d*~largeur>0) and (d*~largeur<largeur.norme())
    ) return true;
    return false;
}

void Vent::agit_sur(ObjetMobile& M) const {
    Vecteur df(0.0);
    if (this->dans_champ(M)) {
        df = 3.77*intensite*intensite*M.getRayon()*M.getRayon()*normale;
    }
    M.ajoute_force(df);
}
