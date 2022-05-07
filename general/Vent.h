#pragma once
#include "ChampForce.h"


class Vent: public Champforce{
	
private:
	Vecteur origine;
	Vecteur normale;
    Vecteur largeur;
    Vecteur longueur;
    Vecteur profondeur;
	
public:
    bool dans_champ(ObjetMobile const& M) const;
    void agit_sur(ObjetMobile&) const;
};
