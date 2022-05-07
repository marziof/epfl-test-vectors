#include "TextViewer.h"

#include "Systeme.h"
#include "Dessinable.h"
#include "ChampForce.h"
#include "Balle.h"
#include "pendule.h"
#include "Ressort.h"
#include "Obstacle.h"

using namespace std;

//######################################################################
// CLASS TEXTVIEWER :
// SUPPORTADESSIN ->
void TextViewer::dessine(Systeme const& S) {
    S.affiche_evolution(flot);
}

void TextViewer::dessine(Dessinable const& D) {
    D.affiche(flot);
}

void TextViewer::dessine(Plan const& P) {
    P.affiche(flot);
}

void TextViewer::dessine(Balle const& B) {
    B.affiche(flot);
}

void TextViewer::dessine(Pendule const& p) {
    p.affiche(flot);
}

void TextViewer::dessine(Ressort const& r) {
    r.affiche(flot);
}

void TextViewer::dessine(Brique const& brique) {
    brique.affiche(flot);
}

void TextViewer::dessine(ChampForce const& c) {
    c.affiche(flot);
}
//######################################################################
