#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "ObjetMobile.h"
#include "Vecteur.h"
#include "SupportADessin.h"

class Systeme;
	

class Balle: public ObjetMobile {
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    Balle(Vecteur para, Vecteur dpara, Vecteur f, double r,
          double m, double a=1, double mu=0.7, Vecteur d2para ={0.0})
         : ObjetMobile(para, dpara, f, r, m, a, mu, d2para) {}

	Balle(Balle const& b)
    : ObjetMobile(b.P, b.dP, b.force, b.rayon, b.masse, b.alpha, b.mu, b.d2P)
	{}

    Balle()  = delete;
//----------------------------------------------------------------------
// DESSINABLE ->
    std::ostream& affiche(std::ostream&)              const override;
    virtual void dessine_sur(SupportADessin& support) const override
        {support.dessine(*this);}
    void display_gnu(std::ofstream&)                  const override;
    void Draw(SupportADessin&)                        const override;
    void ajoute_a(Systeme&)                           const override;
//----------------------------------------------------------------------
// OBJETMOBILE ->
    Vecteur evolution() override;
};

std::ostream& operator<<(std::ostream& sortie, Balle const& b);



