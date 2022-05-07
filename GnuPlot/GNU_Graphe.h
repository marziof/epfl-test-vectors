#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "SupportADessin.h"

class Dessinable;
class Systeme;

//######################################################################
// CLASS  : GNU_GRAPHE
class GNU_Graphe: public SupportADessin{
private:
  std::ofstream flot;

public:
// CONSTRUCTEURS / DESTRUCTEURS :
    GNU_Graphe(std::string file_name = "Graphe.txt")
    { flot.open(file_name, std::ios::app);
        if (not flot.fail()){ std::cout << "Lien etablit correctement aveec le fichier Graphe.txt." <<std::endl;}
        else {std::cerr <<"Fichier non valide" <<std::endl;}
    }
// DESTRUCTEUR -> ON FERME LE FLUX !!!
    virtual ~GNU_Graphe(){
        flot.close();
    }
// on ne copie pas les GNU_Graphe
    GNU_Graphe(GNU_Graphe const&)            = delete;
    GNU_Graphe& operator=(GNU_Graphe const&) = delete;
// mais on peut les déplacer
    GNU_Graphe(GNU_Graphe&&)            = default;
    GNU_Graphe& operator=(GNU_Graphe&&) = default;
//----------------------------------------------------------------------
// SUPPORTADESSIM ->
  void dessine(Systeme const&)          override;
  void dessine(Dessinable const&)       override;
  void dessine(Plan const& P)           override;
  void dessine(Balle const& B)          override;
  void dessine(Pendule const&)          override;
  void dessine(Ressort const&)          override;
  void dessine(Brique const& brique)    override;
  void dessine(ChampForce const&)       override;
};
//######################################################################
