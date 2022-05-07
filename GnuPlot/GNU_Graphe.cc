#include "GNU_Graphe.h"

#include "Systeme.h"
#include "Dessinable.h"
#include "ChampForce.h"
#include "Balle.h"
#include "pendule.h"
#include "Ressort.h"

using namespace std;

//######################################################################
// CLASS  : GNU_GRAPHE
// SUPPORTADESSIN ->
void GNU_Graphe::dessine(Systeme const& S) {
    S.display_gnu(flot);
}

void GNU_Graphe::dessine(Dessinable const& a_dessiner) {
  a_dessiner.display_gnu(flot);
}

void GNU_Graphe::dessine(Plan const& P) {
    P.display_gnu(flot);
}

void GNU_Graphe::dessine(Balle const& B) {
    B.display_gnu(flot);
}

void GNU_Graphe::dessine(Pendule const& p) {
    p.display_gnu(flot);
}

void GNU_Graphe::dessine(Ressort const& r) {
    r.display_gnu(flot);
}

void GNU_Graphe::dessine(Brique const& brique) {
    brique.display_gnu(flot);
}

void GNU_Graphe::dessine(ChampForce const& c) {
    c.display_gnu(flot);
}
//######################################################################
