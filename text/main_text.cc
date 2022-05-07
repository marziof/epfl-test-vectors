#include <iostream>
#include "TextViewer.h"
#include "constantes.h"
#include "Systeme.h"
#include "Balle.h"
#include "ChampForce.h"
#include "Obstacle.h"
using namespace std;

int main()
{
  TextViewer ecran(cout);
  Systeme S;
  Plan Plan({0,0,0}, {1,0,0}, {0,1,0});
  Balle baballe({0,0,4}, {0,0,1}, {0,0,0}, 1, 6);
  ChampForce Champ;

   baballe.ajoute_a(S);//Plan.ajoute_a(S); Champ.ajoute_a(S);
  S.init();
  cout << "Au départ :" << endl;
  ecran.dessine(S);
  for (size_t i(1); i<3; ++i){
      S.evolue(0.05, 1);
      cout << "Apres " <<i <<" pas de calcul :" << endl;
      ecran.dessine(S);
  }

  return 0;
}
