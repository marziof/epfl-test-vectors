#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>

class Vecteur{
private:
  std::vector<double> vecteur;

public:
//CONSTRUCTEURS
  Vecteur ()   {vecteur.push_back(0.0);vecteur.push_back(0.0); vecteur.push_back(0.0);}
  
  Vecteur(std::initializer_list<double> const& L)
      {for (auto el: L){
        vecteur.push_back(el);
       }
      }

  Vecteur(std::vector<double> V)
  :vecteur(V) {}

  Vecteur(std::size_t j) 
  :vecteur(j, 0.0) {}
  //{for (std::size_t i(0); i<=j;++i){
  //  vecteur.push_back(0.0);
  //  }
  //}
  
    
//----------------------------------------------------------------------
//CONSTRUCTEUR DE COPIE
  Vecteur (Vecteur const& V) 
  :vecteur(V.get_vect()){}

  
//----------------------------------------------------------------------
//OPERATEURS INTERNES
  Vecteur operator+=(Vecteur const& V2);
  Vecteur operator-=(Vecteur const& V2);
  Vecteur operator^(Vecteur const& V2)const;
  Vecteur operator~() const;
  double operator*(Vecteur const& V2)const;
  Vecteur operator*(double x)const ;

//----------------------------------------------------------------------
//METHODES PROPRES
  void augmente(double val=0){vecteur.push_back(val);}
  void set_coord(std::size_t pos, double val){vecteur[pos-1]=val;}
  void affiche(std::ostream&) const;
  std::vector<double> get_vect() const{return vecteur;}
  double distance(Vecteur const& V) const;

//----------------------------------------------------------------------
//OPERATIONS :
  bool compare(Vecteur vec, double erreur = 0.1) const;
  Vecteur addition(Vecteur autre) const;
  Vecteur soustraction(Vecteur autre) const;
  Vecteur oppose() const;
  Vecteur mult(double n) const;
  double prod_scal(Vecteur autre) const;
  Vecteur prod_vect(Vecteur) const;
  double norme() const;
  double norme2() const;
  Vecteur unitaire() const;

};

//----------------------------------------------------------------------
//OPERATEURS EXTERNES :
bool operator==(Vecteur const& V1, Vecteur const& V2);
std::ostream& operator<<(std::ostream& sortie, Vecteur const& V);
Vecteur operator-(Vecteur const& V);
Vecteur operator+(Vecteur V1, Vecteur const& V2);
Vecteur operator-(Vecteur V1, Vecteur const& V2);
Vecteur operator*(double x, Vecteur V);

