#include <iostream>
#include <cmath>
#include <vector>
#include "Vecteur.h"
using namespace std;


//OPERATEURS INTERNES 
Vecteur Vecteur::operator+=(Vecteur const& V2){
  Vecteur V1(*this);
  return (V1.addition(V2));
}

Vecteur Vecteur::operator-=(Vecteur const& V2){
  Vecteur V1(*this);
  return (V1.soustraction(V2));
}

Vecteur Vecteur::operator^(Vecteur const& V2)const{
  //Vecteur V1(*this);
  return(this->prod_vect(V2));
}

Vecteur Vecteur::operator~() const{
  return (this->unitaire());
}

double Vecteur::operator*(Vecteur const& V2)const{
  return(this->prod_scal(V2));
}

Vecteur Vecteur::operator*(double x)const{
  return(this->mult(x));
}



//----------------------------------------------------------------------
//METHODES PROPRES
void Vecteur::affiche(ostream& flot) const{
  flot <<"(";
  for (size_t i(0); i<(vecteur.size()-1);++i){
    flot <<vecteur[i] <<", ";
  }
  flot <<vecteur[vecteur.size()-1];
  flot <<")";
}

double Vecteur::distance(Vecteur const& V) const{
  Vecteur VV(vecteur);
  Vecteur xV(VV-V);
  double d( xV.norme());
  return d;
}



//----------------------------------------------------------------------
//OPERATIONS :

bool Vecteur::compare(Vecteur vec, double err) const{
  vector<double> v(vec.get_vect());
  if (vecteur.size()!= v.size()) return false;
  
  for (size_t i(0); i< v.size();++i){
    if(fabs(vecteur[i]-v[i])>(err)) return false;
  }
  //cout <<"TRUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUE" <<endl;
  return true;
}

Vecteur Vecteur::addition(Vecteur autre) const{
  vector<double> c(vecteur);
  vector<double> d(autre.get_vect());
  if (d.size() <= c.size()){
    for (size_t i(0) ; i<vecteur.size(); ++i){
      c[i] = c[i]+d[i];
    }
  } else {
    for (size_t i(0) ; i<d.size(); ++i){
      c[i] = c[i]+d[i];
    }
  }
  Vecteur D(c);
  return D;
}

Vecteur Vecteur::soustraction(Vecteur autre) const{
  vector<double> c(vecteur);
  vector<double> d(autre.get_vect());
  if (d.size() <= c.size()){
    for (size_t i(0) ; i<c.size(); ++i){
      c[i] = c[i]-d[i];
    }
  } else {
    for (size_t i(0) ; i<d.size(); ++i){
      c[i] = c[i]-d[i];
    }
  }
  Vecteur D(c);
  return D;
}


Vecteur Vecteur::oppose() const{
  Vecteur C(*this);
  return C*(-1);
}

Vecteur Vecteur::mult(double n) const{
  vector<double> vv(vecteur);
  for (auto& el:vv){
    el *=n;
  }
  Vecteur V(vv);
  return V;
}

double Vecteur::prod_scal(Vecteur autre) const{
  double p(0);
  vector<double> v(autre.get_vect());
  if (vecteur.size() == v.size()){
    for (size_t i(0); i<vecteur.size(); ++i){
      p += vecteur[i]*v[i];
    }
    return p;
  }else {
    cout <<"öLPOOIBJK";
    throw 1;
  }
}

Vecteur Vecteur::prod_vect(Vecteur v) const{
  Vecteur C(0.0);
  vector<double> l(v.get_vect());
  if ((vecteur.size()!=3) or l.size() !=3) throw 2;
  else{
    C.vecteur[0]=((vecteur[1]*l[2])-(vecteur[2]*l[1]));
    C.augmente((vecteur[2]*l[0])-(vecteur[0]*l[2]));
    C.augmente((vecteur[0]*l[1])-(vecteur[1]*l[0]));
  }
  return C;
}

double Vecteur::norme() const{
  double n(0.0);
  for (auto el : vecteur){
    n += pow(el, 2.0);
  }
  return sqrt(n);
}

double Vecteur::norme2() const{
  double n(0.0);
  for (auto el : vecteur){
    n += pow(el, 2.0);
  }
  return n;
}

Vecteur Vecteur::unitaire() const{
  Vecteur v(vecteur);
  v = v*(1/v.norme());
  return v;
}


//----------------------------------------------------------------------
//OPERATEURS EXTERNES :

Vecteur operator-(Vecteur const& V){
  return V.oppose();
}
  
bool operator==(Vecteur const& V1, Vecteur const& V2){
  return (V1.compare(V2));
}

std::ostream& operator<<(ostream& sortie, Vecteur const& V){
  V.affiche(sortie);
  return sortie;
}

Vecteur operator+(Vecteur V1, Vecteur const& V2){
  return (V1+=V2);
}

Vecteur operator-(Vecteur V1, Vecteur const& V2){
  return (V1-=V2);
}

Vecteur operator*(double x, Vecteur V){
  return V*x;
}
