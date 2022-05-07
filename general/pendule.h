#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include "ObjetMobile.h"
#include "Vecteur.h"
#include "SupportADessin.h"

class Systeme;

class Pendule: public ObjetMobile{
private:
	double longueur;
	double frottement;
	Vecteur origine;
	Vecteur direction;
	Vecteur P_balle;
	Vecteur dP_balle;
	
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    Pendule(Vecteur O, Vecteur D, Vecteur f, double th, double th_pt, double r,
            double m, double l, double fr, double a=1, double mu=0.7,Vecteur d2th = {0.0})
    : ObjetMobile(th, th_pt, f, r, m, a, mu, d2th), longueur(l), frottement(fr), origine(O), direction(D),
                P_balle(O + l*cos(th)*~g + l*sin(th)*D), dP_balle(l*th_pt * (cos(th)*D - sin(th)*~g))
	{force -= frottement*direction;}
  
    Pendule(Pendule const& D) : ObjetMobile(D.P, D.getDP(), D.getForce(), D.getRayon(), D.getMasse(),
                                D.getAlpha(), D.getMu(), D.getD2P()), longueur(D.longueur), frottement(D.frottement),
                                origine(D.origine), direction(D.direction), P_balle(D.P_balle), dP_balle(D.dP_balle) {}

    Pendule()  = delete;
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
// PENDULE :
	void calculeP_balle();
    void calculedP_balle();
    Vecteur getPBalle()  const {return P_balle;}
    Vecteur getOrigine() const {return origine;}
};

std::ostream& operator<<(std::ostream&, Pendule&);
