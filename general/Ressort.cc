#include "Ressort.h"

#include <iostream>
#include <fstream>
#include "Systeme.h"

using namespace std;

//######################################################################
// CLASS RESSORT:
// DESSINABLE ->
ostream& Ressort::affiche(ostream& sortie) const {
    sortie <<"Un ressort " <<endl
           << masse <<  " # masse ressort" << endl
           << Raideur << " # raideur ressort" << endl
           << frottement << " #  frottement ressort" << endl
           << Origine << " # origine ressort" << endl
           << D << " # direction ressort" << endl
           << X << " # X ressort" << endl
           << dX << " # X point ressort" << endl
           << P << " # position bout ressort" << endl
           << force << " # f()" << endl;
    return sortie;
}

void Ressort::display_gnu(ofstream& flot) const {
// X dX
    flot <<X << " ";
    flot <<dX <<" ";
    //return flot;
}

void Ressort::Draw(SupportADessin& Support) const {
    Support.dessine(*this);
}

void Ressort::ajoute_a(Systeme& S) const {
    S.ajouter_objetmobile(new Ressort(*this));
}
//----------------------------------------------------------------------
// OBJETMOBILE ->
Vecteur Ressort::evolution() {
    Vecteur d2X( (1/masse)*(force*D - Raideur*X - frottement*dX) );
    cout << d2X << " # f()" << endl;
    return d2X;
}
//----------------------------------------------------------------------
// RESSORT :
void Ressort::calculeP_balle() {
    setP( Origine + X*D );
}

void Ressort::calculedP_balle() {
    setdP( dX*D );
}
//######################################################################

ostream& operator<<(ostream& sortie, Ressort& R) {
    R.calculeP_balle();
    R.calculedP_balle();
    return (R.affiche(sortie));
}
