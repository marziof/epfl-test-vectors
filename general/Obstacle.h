#pragma once

#include <iostream>
#include "Vecteur.h"
#include "Dessinable.h"
#include "ObjetMobile.h"
#include "SupportADessin.h"

class Systeme;

//######################################################################
class Obstacle: public Dessinable{
protected:
    Vecteur P;
    double mu;
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    Obstacle(Vecteur V, double mu)
    : P(V), mu(mu){}

    Obstacle(Obstacle const& O)
    : P(O.P), mu(O.mu) {}
    Obstacle() = delete;
    virtual ~Obstacle() = default;
//----------------------------------------------------------------------
// DESSINABLE ->
    void display_gnu(std::ofstream& flot) const override {flot <<' ';}
//----------------------------------------------------------------------
// OBSTACLE :
    Vecteur getP() const {return P;}
    void agit_sur(ObjetMobile&) const;
// VIRTUELLES PURES :
    virtual Vecteur point_plus_proche(const ObjetMobile&) const =0;
    virtual double distance(const ObjetMobile&)           const =0;
};

//######################################################################
std::ostream& operator<<(std::ostream&, Obstacle const&);


//######################################################################
// CLASSE PLAN:
class Plan: public Obstacle{
private:
    Vecteur directeur1;
    Vecteur directeur2;
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    Plan(Vecteur v0, Vecteur v1, Vecteur v2, double mu=0.7)
    : Obstacle(v0, mu), directeur1(v1), directeur2(v2) {}
    
    Plan(Plan const& plan) :Obstacle(plan.P, plan.mu), directeur1(plan.directeur1),
                            directeur2(plan.directeur2) {}

    Plan()
        :Obstacle({0.0,0.0,0.0}, 0.7), directeur1({1,0,0}), directeur2({0,1,0}) {}
//----------------------------------------------------------------------
// DESSINABLE ->
    std::ostream& affiche(std::ostream&)              const override;
    virtual void dessine_sur(SupportADessin& support) const override
        {support.dessine(*this);}
    void Draw(SupportADessin&)                        const override;
    void ajoute_a(Systeme&)                           const override;
//----------------------------------------------------------------------
// OBSTACLE ->
    Vecteur point_plus_proche(const ObjetMobile&) const override;
    double distance(const ObjetMobile&)           const override;
//----------------------------------------------------------------------
// PLAN :
    Vecteur getV1() const {return directeur1;}
    Vecteur getV2() const {return directeur2;}
    Vecteur vect_normal() const;
};
//######################################################################
std::ostream& operator<<(std::ostream&, Plan const&);



//######################################################################
// CLASSE BRIQUE
class Brique: public Obstacle
{
private:
    Vecteur longueur;
    Vecteur largeur;
    double hauteur;
public:
    // CONSTRUCTEURS / DESTRUCTEURS :
    Brique(Vecteur V0, Vecteur V1, Vecteur V2, double h, double mu=0.7)
    : Obstacle(V0, mu), longueur(V1), largeur(V2), hauteur(h)
    { double V3(V1*V2);
      if((V3)<0.001)largeur=V2;
      else { Vecteur L(~V1);
             largeur =V2-(V2*L)*L;
      }
    }

    Brique(Brique const& B) : Obstacle(B.P, B.mu), longueur(B.longueur),
                              largeur(B.largeur),  hauteur(B.hauteur) {}

    Brique() = delete;
//----------------------------------------------------------------------
// DESSINABLE ->
    std::ostream& affiche(std::ostream&)              const override;
    virtual void dessine_sur(SupportADessin& support) const override
        {support.dessine(*this);}
    void Draw(SupportADessin&)                        const override;
    void ajoute_a(Systeme&)                           const override;
//----------------------------------------------------------------------
// OBSTACLE ->
    Vecteur point_plus_proche(const ObjetMobile&)     const override;
    double distance(const ObjetMobile&)               const override;
//----------------------------------------------------------------------
// BRIQUE :
    Vecteur getV1() const {return longueur;                      }
    Vecteur getV2() const {return largeur;                       }
    Vecteur getH() const  {return( hauteur*~(longueur^largeur)); }
    Vecteur ppp(Vecteur, Vecteur, Vecteur, Vecteur, Vecteur) const;
};
//######################################################################
std::ostream& operator <<(std::ostream&,Brique const&);
