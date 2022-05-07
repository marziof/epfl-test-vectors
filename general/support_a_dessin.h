#pragma once
//#include "Vecteur.h"
//#include <vector>
//#include <memory>
//#include "Objet.h"
//#include "ObjetMobile.h"
//#include "obstacles.h"
//#include "ChampForces.h"
//#include "IntegrateurEulerCromer.h"

class Dessinable;

class SupportADessin {
public:
    virtual ~SupportADessin() = default;
    // on ne copie pas les Supports
    SupportADessin(SupportADessin const&)            = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
     // mais on peut les déplacer
    SupportADessin(SupportADessin&&)            = default;
    SupportADessin& operator=(SupportADessin&&) = default;

    SupportADessin() = default;


    virtual void dessine(Dessinable const&) = 0;



};
