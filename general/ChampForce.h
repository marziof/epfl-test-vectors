#pragma once

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Vecteur.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "constantes.h"

class ObjetMobile;
class Systeme;

class ChampForce : public Dessinable{
private:
	Vecteur intensite;
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    ChampForce(Vecteur i)
     : intensite(i) {}
    ChampForce(ChampForce const& C) :intensite(C.intensite) {}
    ChampForce() : intensite(g) {}
    virtual ~ChampForce() = default;
//----------------------------------------------------------------------
// DESSINABLE ->
    std::ostream& affiche(std::ostream&)              const override;
    virtual void dessine_sur(SupportADessin& support) const override
        {support.dessine(*this);}
    void display_gnu(std::ofstream& flot)             const override {flot <<' ';}
    void Draw(SupportADessin&)                        const override;
    void ajoute_a(Systeme&)                           const override;
//----------------------------------------------------------------------
    void agit_sur(ObjetMobile& obj) const;
};

std::ostream& operator<<(std::ostream& sortie,ChampForce const& f);

