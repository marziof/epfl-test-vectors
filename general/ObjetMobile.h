#pragma once

#include <iostream>
#include <math.h>
#include "Dessinable.h"
#include "Vecteur.h"
#include "constantes.h"

class ObjetMobile : public Dessinable {
protected:
    Vecteur P;
	Vecteur dP;
	Vecteur force;
	double rayon;
    double masse;
	double masse_volumique;
    double alpha;
    double mu;
    Vecteur d2P;
  
public:
// CONSTRUCTEURS / DESTRUCTEURS :
    ObjetMobile(Vecteur para, Vecteur dpara, Vecteur f,
                double r, double m, double a, double mu, Vecteur d2para)
     :P(para), dP(dpara), force(f), rayon(r), masse_volumique(3*m/(4*PI*pow(r,3))),
       masse(m), alpha(a), mu(mu), d2P(d2para)  {}

    ObjetMobile(ObjetMobile const& O)
     : P(O.P), dP(O.dP), force(O.force), rayon(O.rayon), masse_volumique(O.masse_volumique), masse(O.masse), alpha(O.alpha),mu(O.mu),  d2P(O.d2P) {}

    virtual ~ObjetMobile() = default;
    ObjetMobile() = delete;
//----------------------------------------------------------------------
// OBJETMOBILE :
    Vecteur getP()     const {return P;     }
    Vecteur getDP()    const {return dP;    }
    Vecteur getD2P()   const {return d2P;   }
    Vecteur getForce() const {return force; }
    double getRayon()  const {return rayon; }
    double getMasse()  const {return masse; }
    double getAlpha()  const {return alpha; }
    double getMu()     const {return mu;    }

    void setP(Vecteur const& v)     {P=v;     }
    void setdP(Vecteur const& v)    {dP=v;    }
    void setF(Vecteur const& v)     {force=v; }
    void setd2P(Vecteur const& v)   {d2P=v;   }

    double distance(ObjetMobile const&) const;
    void agit_sur(ObjetMobile&);
    void ajoute_force(Vecteur const&);

    //VIRTUELLES PURES
    virtual Vecteur evolution() =0;
};

std::ostream& operator<<(std::ostream&, ObjetMobile const&);


