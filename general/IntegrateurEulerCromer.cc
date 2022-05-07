#include <iostream>
#include "IntegrateurEulerCromer.h"
#include "ObjetMobile.h"
#include "Vecteur.h"
#include <fstream>

using namespace std;

void IntegrateurEulerCromer::evolue(ObjetMobile& obj, double dt) const{
	Vecteur dP(0.0);
	Vecteur P(0.0);
	
	Vecteur V( obj.getP().get_vect().size() );
	if (obj.getForce() == V) {
        P  = ( obj.getP() + dt*obj.evolution()    );
	} else {
        dP = ( obj.getDP() + (dt*obj.evolution()) ); // evolution pas def
        P  = ( obj.getP() + dt*dP                   );
        obj.setdP(dP);
  }
    obj.setP(P);
    obj.setd2P(obj.evolution());

    cout <<P << " #position" << endl;
    cout <<obj.getDP() << " #vitesse" << endl;
    cout << obj.evolution() << "#f()" << endl;
}

//----------------------------------------------------------------------
void IntegrateurEulerCromer::iteration(const unique_ptr<ObjetMobile>&  obj, size_t& i, double& dt) const {
    ofstream flot;
		flot.open("graphe.txt");
		if (not flot.fail()) {
			obj->display_gnu(flot);
			for(size_t j(1); j <= i; ++j) {
			evolue(*obj, dt);
			obj->display_gnu(flot);
			}
        } else { cerr << "Acces au fichier impossible ..." << endl;
		}

}
