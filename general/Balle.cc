#include "Balle.h"

#include "Systeme.h"
#include <iomanip>

using namespace std;

//######################################################################
// CLASSE BALLE :
// DESSINABLE ->
ostream& Balle::affiche(ostream& sortie) const{
    sortie <<"Une balle : " <<endl;
    sortie << masse           <<setfill(' ') <<right <<setw(20) << "# masse" << endl
           << rayon           <<setfill(' ') <<right <<setw(20) << "# rayon" << endl
           << masse_volumique <<setfill(' ') <<right <<setw(20) << "# masse volumique" << endl
           << P               <<setfill(' ') <<right <<setw(25) << "# position       " << endl
           << dP              <<setfill(' ') <<right <<setw(25) << "# vitesse        " << endl
           << force           <<setfill(' ') <<right <<setw(25) << "# force          " << endl;
    return sortie;
}



void Balle::display_gnu(std::ofstream& flot) const {
// P.x P.y P.z dP.x dP.y dP.z
    for(auto element: P.get_vect()) {
        flot << element << " ";
    }
    for(auto element: dP.get_vect()) {
        flot << element << " ";
    }
}

void Balle::Draw(SupportADessin& Support) const{
    Support.dessine(*this);
}

void Balle::ajoute_a(Systeme& S) const {
  S.ajouter_objetmobile(new Balle(*this));
}
//----------------------------------------------------------------------
// OBJETMOBILE ->
Vecteur Balle::evolution() {
    Vecteur	D2P((1/masse)*force);
    d2P = D2P;
    return d2P;
}
//######################################################################

ostream& operator<<(ostream& sortie, Balle const& b) {
	return b.affiche(sortie);
}


