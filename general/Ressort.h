#pragma once

#include <iostream>
#include <fstream>
#include "ObjetMobile.h"
#include "Vecteur.h"
#include "SupportADessin.h"

class Ressort: public ObjetMobile{
private:
    Vecteur Origine;
    Vecteur D;
    double X;
    double dX;
    double L_vide;
    double frottement;
    double Raideur;

public:
// CONSTRUCTEURS / DESTRUCTEURS :
    Ressort(Vecteur O, Vecteur D, Vecteur f,double r, double m, double x, double dx,  double L, double Fr, double k, double a=1, double mu=0.7, Vecteur d2para={0.0})
    : ObjetMobile(O+x*~D, dx*D, f, r, m, a, mu, d2para), Origine(O),D(~D), X(x), dX(dx),
      L_vide(L), frottement(Fr), Raideur(k) {}

    Ressort(Ressort const& R)
     : ObjetMobile(R.P, R.getDP(), R.getForce(), R.getRayon(), R.getMasse(), R.getAlpha(), R.getMu(),  R.getD2P()),
       Origine(R.Origine), D(R.D), X(R.X), dX(R.dX),L_vide(R.L_vide),frottement(R.frottement), Raideur(R.Raideur) {}

    Ressort() = delete;
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
//----------------------------------------------------------------------
// RESSORT :
    void calculeP_balle();
    void calculedP_balle();
    Vecteur getPBalle()  const {return Origine+X*D;}
    Vecteur getOrigine() const {return Origine;    }
};

std::ostream& operator<<(std::ostream&, Ressort&);
