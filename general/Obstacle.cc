#include "Obstacle.h"

#include <iostream>
#include "Systeme.h"

using namespace std;

//######################################################################
// CLASS OBSTACLE :
void Obstacle::agit_sur(ObjetMobile& M) const {
    Vecteur X1(M.getP());
    Vecteur D(~(X1-point_plus_proche(M)));
    Vecteur F(M.getForce());
    double delta(1+M.getAlpha());
    double Fn(F*D);
    if (Fn <0) M.setF(F-Fn*D);
    else M.setF(Fn*D);
    double v((-1*M.getDP())*D);
    Vecteur Vc(M.getDP()+v*D);
    double Mu(M.getMu()*mu);
    Vecteur dV(0.0);
    if (7*Mu*(delta)*v >= 2*Vc.norme()) dV = ((delta)*v*D - (2/7) *Vc);
    else dV = ((delta)*v*(D-Mu*~Vc));
    cout << "n " << D << endl;
    cout << "vstar" << v << endl;
    cout << "vc" << Vc << endl;
    cout << "dV" << dV << endl;
    M.setdP(M.getDP() + dV);
}
//######################################################################
ostream& operator<<(ostream& sortie, Obstacle const& O){
  return O.affiche(sortie);
}


//######################################################################
// CLASS  PLAN:
// DESSINABLE ->
ostream& Plan::affiche(ostream& sortie)const {
  sortie <<this->P <<"  #origine plan" <<endl
         <<this->vect_normal() <<"  #normale plan" <<endl;
  return sortie;
}

void Plan::Draw(SupportADessin& Support) const{
    Support.dessine(*this);
}

void Plan::ajoute_a(Systeme& S) const {
  S.ajouter_obstacle(new Plan(*this));
}
//----------------------------------------------------------------------
// OBSTACLE :
Vecteur Plan::point_plus_proche(const ObjetMobile& M) const{
    Vecteur N(this->vect_normal());
    Vecteur X1(M.getP());
    Vecteur X(X1+(((this->P-X1)*N)*N));
    return X;
}

double Plan::distance(const ObjetMobile& M)const{
    Vecteur X(this->point_plus_proche(M));
    double L((M.getP()-X).norme()-M.getRayon());
    return L;
}
//----------------------------------------------------------------------
// PLAN :
Vecteur Plan::vect_normal() const {
    Vecteur V(directeur1^directeur2);
    Vecteur N(~V);
    return N;
}
//######################################################################
ostream& operator<<(ostream& sortie, Plan const& plan){
  return (plan.affiche(sortie));
}


//######################################################################
// CLASS  BRIQUE :
// DESSINABLE ->
ostream& Brique::affiche(ostream& sortie) const{
    sortie <<this->P <<"  #origine brique " <<endl;
    sortie <<longueur <<"  #longueur brique" <<endl;
    sortie <<largeur <<"  #largeur brique" <<endl;
    sortie <<hauteur <<"   #hauteur brique" <<endl;
    return sortie;
}

void Brique::ajoute_a(Systeme& S) const {
    S.ajouter_obstacle(new Brique(*this));
}

void Brique::Draw(SupportADessin& Support) const{
    Support.dessine(*this);
}
//----------------------------------------------------------------------
// OBSTACLE ->
Vecteur Brique::point_plus_proche(const ObjetMobile& M) const{
  //point sur chaque face:
  Vecteur N(~(longueur^largeur));
  //cout <<N <<(largeur^longueur) <<(longueur^largeur) <<endl;
  Vecteur L(~longueur), l(~largeur);
  Vecteur MP(M.getP());
  //Face normal longueur largeur

  //Face 1 P           N  longueur    largeur   (+Z)
  Vecteur XF(ppp(P, MP, N, longueur, largeur));
  //Face 2 P          -l  longueur    hauteur*-N  (-l)
  Vecteur X2(ppp(P, MP, (-1*l), -hauteur*N, longueur));

  if(XF.distance(MP)>X2.distance(MP)) XF=X2;

  //Face 3 P          -L  largeur     hauteur*-N  (-L)
  Vecteur X3(ppp(P, MP, (-1*L), largeur, -hauteur*N));
  if(XF.distance(MP)>X3.distance(MP)) XF=X3;

  //Face4  P+longueur  L  largeur     hauteur*-N      (+L)
  Vecteur X4(ppp(P+longueur,MP, L, -hauteur*N, largeur));
  if(XF.distance(MP)>X4.distance(MP)) XF=X4;

  //Face 5 P-hauteur*N  -N  longueur    largeur   (-Z)
  Vecteur X5( ppp(P-(hauteur*N),MP, -N , largeur, longueur));
  if(XF.distance(MP)>X5.distance(MP)) XF=X5;

  //Face 6 P+largeur   l  longueur    hauteur*-N   (+l)
  Vecteur X6(ppp(P+largeur,MP, l, longueur, -hauteur*N));
  if(XF.distance(MP)>X6.distance(MP)) XF=X6;

  return XF;
}

double Brique::distance(const ObjetMobile& M) const{
    Vecteur V(M.getP()-this->point_plus_proche(M));
    return (V.norme()-M.getRayon());
}
//----------------------------------------------------------------------
// BRIQUE :
Vecteur Brique::ppp(Vecteur O, Vecteur MP, Vecteur N, Vecteur L, Vecteur l) const{
    double ll(l.norme()), LL(L.norme());
    Vecteur X2( MP + (((O-MP)*N)*N) );
    double X2L( (X2-O)*(~L) );
    double X2l( (X2-O)*(~l) );

    if     (X2L > LL)  { X2 = ( X2-(X2L-LL)*~L );      }
    else if(X2L < 0 )  { X2 = ( X2-X2L*~L      );      }

    if     (X2l > ll)  { X2 = ( X2 - (X2l-ll)*~l );   }
    else if(X2l < 0 )  { X2 = ( X2 - X2l*~l      );   }

    return X2;
}
//######################################################################
ostream& operator<<(ostream& sortie, Brique const& B){
  return  (B.affiche(sortie));
}
