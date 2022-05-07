#pragma once

class Systeme;
class Dessinable;
class Pendule;
class ChampForce;
class Brique;
class Plan;
class Balle;
class Ressort;

class SupportADessin {
public:
    virtual ~SupportADessin()                        = default;
    // on ne copie pas les Supports
    SupportADessin(SupportADessin const&)            = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
     // mais on peut les déplacer
    SupportADessin(SupportADessin&&)                 = default;
    SupportADessin& operator=(SupportADessin&&)      = default;

    SupportADessin() = default;

//METHODE GENERALE
    virtual void dessine(Systeme const&)        = 0;
    virtual void dessine(Dessinable const&)     = 0;
//CHAQUE OBJET SERA DESSINER/AFFICHER D0'UNE MANIERE DISTINCTE
    virtual void dessine(Plan const& P)         =0;
    virtual void dessine(Balle const& B)        =0;
    virtual void dessine(Pendule const&)        =0;
    virtual void dessine(Ressort const&)        =0;
    virtual void dessine(Brique const& brique)  =0;
    virtual void dessine(ChampForce const&)     =0;
};
