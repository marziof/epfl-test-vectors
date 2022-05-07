#include "ObjetMobile.h"

#include <iostream>
#include <math.h>

using namespace std;

//OBJETMOBILE
void ObjetMobile::ajoute_force(Vecteur const& df) {
    cout <<"On ajoute les forces des champs de force ..." <<endl
         <<force <<"df + f" << endl;
    force = force + df;
}


double ObjetMobile::distance(ObjetMobile const& M) const {
    double T(P.Vecteur::distance(M.getP()));
    T -= (rayon + M.getRayon());
    return T;
}


void ObjetMobile::agit_sur(ObjetMobile& M){
    Vecteur X2(M.P);
    Vecteur D(~(P-X2));
    Vecteur F2(M.force);
    double delta( (1+M.alpha) * M.masse/(masse*M.masse) );
    double Mu(M.mu*mu);
    double Fn1(force*D), Fn2(M.force*D);

    if (Fn1<0){
    force = force - Fn1*D ;
    M.force = M.force + Fn1*D;
    } if (Fn2 >0) {
    force = force + Fn2*D ;
    M.force = M.force - Fn2*D;
    }

    double v((M.dP-dP)*D);
    Vecteur Vc(dP-M.dP+v*D);
    Vecteur dV(0.0);
    if (7*Mu*(1+delta)*v >= 2*Vc.norme()) dV = ( delta*v*D-(2*M.masse/(7*(masse+M.masse)))*Vc );
    else                                  dV = ( delta*v*(D-Mu*~Vc) );
    dP   =   ( dP + dV );
    M.setdP(( M.getDP() - (masse/M.masse)*dV ));

    cout << "D: " << D << endl;
    cout << "delta " << delta << endl;
    cout << "Fn1 " << Fn1 <<  endl;
    cout << "Fn2 " << Fn2 <<  endl;
    cout << "v " << v << endl;
    cout << "Vc " << Vc << endl;
    cout << "dv " << dV << endl;
}




std::ostream& operator<<(std::ostream& sortie, ObjetMobile const& b) {
	b.affiche(sortie);
	return sortie;
}
