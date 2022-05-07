#include <iostream>
#include <fstream>
#include "pendule.h"
#include "Systeme.h"

using namespace std;

//######################################################################
// CLASS BALLE :
// DESSINABLE ->
ostream& Pendule::affiche(ostream& sortie) const {
	sortie << masse <<  " # masse pendule" << endl
		   << longueur << " # longueur pendule" << endl
		   << frottement << " #  frottement pendule" << endl
		   << origine << " # origine pendule" << endl
		   << direction << " # direction pendule" << endl
		   << P << " # theta pendule" << endl
		   << dP << " # theta point pendule" << endl
		 //<< << " # f() pendule " << endl
		   << P_balle << " # position bout pendule" << endl
		   << force << " # force" << endl;
	return sortie;
}

void Pendule::display_gnu(ofstream& flot) const {
//  theta  dtheta  P(balle) : x y z  d2theta
    for(auto element: P.get_vect()) {
        flot << element <<' ';
    }
    for(auto element: dP.get_vect()) {
        flot << element <<' ';
    }
    for (auto el : P_balle.get_vect()) {
        flot <<el <<' ';
    }
    for (auto el : d2P.get_vect()) {
        flot <<el <<' ';
    }
}

void Pendule::Draw(SupportADessin& Support) const {
    Support.dessine(*this);
}

void Pendule::ajoute_a(Systeme& S) const {
  S.ajouter_objetmobile(new Pendule(*this));
}

//----------------------------------------------------------------------
// OBJETMOBILE ->
Vecteur Pendule::evolution() {
	Vecteur d2Theta( (1/(masse*longueur)) * (cos(P.get_vect()[0])*(force)*direction-sin(P.get_vect()[0])*force*~g-frottement/longueur*dP.get_vect()[0]) ); 
    d2P = d2Theta;
	return d2Theta;
}

void Pendule::calculeP_balle() {
	P_balle = (origine + longueur*cos(P.norme())*~g + longueur*sin(P.norme())*direction);
}	


void Pendule::calculedP_balle() {
	dP_balle = (longueur*dP.norme() * (cos(P.norme())*direction - sin(P.norme())*~g));
}

//######################################################################

ostream& operator<<(ostream& sortie, Pendule& p) {
    p.calculeP_balle();
    p.calculedP_balle();
    return p.affiche(sortie);
}


