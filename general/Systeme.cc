#include <iostream>
#include "Systeme.h"

using namespace std;

void Systeme::init(){
    //ON AJOUTE TOUS LES CHAMPS AUAX OBJETS MOBILES
      if (Champforces.size() != 0){
        for (auto const& el : Champforces){
          for (auto const& obj : Objetmobiles){
            el->agit_sur(*obj);
          }
        }
      }
}
// ======================================================================

void Systeme::evolue(double dt, size_t t){
  if(Objetmobiles.size() !=0){
  //OBJETS MOBILES - OBJETS MOBILES (CHOCS)
    for (size_t i(0); i<Objetmobiles.size() ; ++i){
      for (size_t j(i+1); j<Objetmobiles.size() ; ++j){
        if (Objetmobiles[i]->distance(*Objetmobiles[j]) <0.01){
          Objetmobiles[i]->agit_sur(*Objetmobiles[j]);
          cout << "balle " << i << " agit sur balle " << j << endl;
        }
      }
      cout << "vitesse " << i+1 << " : "  << Objetmobiles[i]->getDP() << endl;
  //OBJETS MOBILES - OBSTACLES (CHOCS)
      if (Obstacles.size() != 0){
        for (auto const& el: Obstacles){
        cout << "Distance: " << el->distance(*Objetmobiles[i]) << endl;
        cout << "Point plus priche " << el->point_plus_proche(*Objetmobiles[i]) << endl;
          if (el->distance(*Objetmobiles[i]) < 0.01){
            el->agit_sur(*Objetmobiles[i]);
            cout << "J'agit sur balle" << endl;
          }
        }
      }
  }
//FINALEMENT METHODE EEVOLUTION
  for (auto const& obj: Objetmobiles) {
    I.iteration(obj,t, dt);
  }
  }else {cout <<"Objets Mobiles : VIDE";};
}
// ======================================================================

ostream& Systeme::afficher(ostream& sortie) const{
  sortie <<"Le systeme est constitue de :" <<endl <<endl;
  if (Objetmobiles.size() != 0){
    sortie <<"Objets mobiles :" <<endl;
    for (auto const& el : Objetmobiles){
        sortie <<*el <<endl;
    }
  }
  
  if (Obstacles.size() != 0){
    sortie <<"Obstacles :" <<endl;
    for (auto const& el : Obstacles){
        sortie <<*el <<endl;
    }
  }

  if (Champforces.size() != 0){
    sortie <<"Champs de force :" <<endl;
    for (auto const& el : Champforces){
        sortie <<*el <<endl;
    }
  }
  
  sortie << endl;
  return sortie;
}

// ======================================================================

ostream& Systeme::affiche_evolution(ostream& sortie) const{
    if (Objetmobiles.size() != 0){
      sortie <<"Objets mobiles :" <<endl;
      for (auto const& el : Objetmobiles){
          sortie <<*el <<endl;
      }
    }
    return sortie;

}
void Systeme::display_gnu(std::ofstream& flot) const{
    for (auto const& el : Objetmobiles){
        el->display_gnu(flot);
    }
    flot <<endl;
}

void Systeme::ajouter_objetmobile(ObjetMobile* nouveau){
  if (nouveau != nullptr){
    Objetmobiles.push_back(unique_ptr<ObjetMobile>(nouveau));
  }
}

void Systeme::ajouter_obstacle(Obstacle* nouveau){
  if (nouveau != nullptr){
    Obstacles.push_back(unique_ptr<Obstacle>(nouveau));
  }
}

void Systeme::ajouter_champforce(ChampForce* nouveau){
  if (nouveau != nullptr){
    Champforces.push_back(unique_ptr<ChampForce>(nouveau));
  }
}

ostream& operator<<(ostream& sortie, Systeme const& S){
  return S.afficher(sortie);
}

// ======================================================================

void Systeme::Draw(SupportADessin& Support) const{
    if (Objetmobiles.size() != 0){
      for (auto const& el : Objetmobiles){
          el->Draw(Support);
      }
    }

    if (Obstacles.size() != 0){
      for (auto const& el : Obstacles){
          el->Draw(Support);
      }
    }

    if (Objetmobiles.size() != 0){
      for (auto const& el : Champforces){
          el->Draw(Support);
      }
    }
}
