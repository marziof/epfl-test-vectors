#include "ChampForce.h"

#include "Systeme.h"
#include "ObjetMobile.h"

using namespace std;

//######################################################################
// CLASS CHAMPFORCE :
// DESSINABLE ->
ostream& ChampForce::affiche(ostream& sortie) const{
	sortie <<"Un champ de force :" <<endl 
         << intensite <<  " # intensite" << endl;
	return sortie;
}

void ChampForce::Draw(SupportADessin& Support) const{
    Support.dessine(*this);
}

void ChampForce::ajoute_a(Systeme& S) const {
  S.ajouter_champforce(new ChampForce(*this));
}

//----------------------------------------------------------------------
// CHAMPFORCE :
void ChampForce::agit_sur(ObjetMobile& obj) const{
    Vecteur df(0.0);
    df = (obj.getMasse() - 4*PI*rho_air*pow(obj.getRayon(), 3)/3)*intensite;
    obj.ajoute_force(df);
}
//######################################################################

ostream& operator<<(ostream& sortie,ChampForce const& f) {
    return (f.affiche(sortie));
}
