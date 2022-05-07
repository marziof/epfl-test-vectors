#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include "IntegrateurEulerCromer.h"
#include "Obstacle.h"
#include "ChampForce.h"
#include "ObjetMobile.h"


class Systeme {
private:
  IntegrateurEulerCromer I;
  
//ENSEMBLE = DESSINABLE
  std::vector<std::unique_ptr<ObjetMobile>> Objetmobiles;
  std::vector<std::unique_ptr<Obstacle>> Obstacles;
  std::vector<std::unique_ptr<ChampForce>> Champforces;
  
public:
  void init();

  std::ostream& afficher(std::ostream&) const;

  std::ostream& affiche_evolution(std::ostream&) const;

  void display_gnu(std::ofstream&) const;
  void Draw(SupportADessin&) const;
  void evolue(double dt = 0.01, size_t n=500);  
  
  void ajouter_objetmobile(ObjetMobile*);
  void ajouter_obstacle(Obstacle*);
  void ajouter_champforce(ChampForce*);
  
};

std::ostream& operator<<(std::ostream&, Systeme const&);


