#pragma once

#include <iostream>
#include <fstream>

class Systeme;
class SupportADessin;
class VueOpenGL;

class Dessinable {  
public:
// CONSTRUCTEURS / DESTRUCTEURS
    virtual ~Dessinable() {}

// VIRTUELLE PURES
    virtual std::ostream& affiche(std::ostream& sortie) const =0;
    virtual void dessine_sur(SupportADessin& support) const=0;
    virtual void display_gnu(std::ofstream& flot) const =0;
    virtual void Draw(SupportADessin&) const =0;
    virtual void ajoute_a(Systeme& S) const =0;
};
/*
//######################################################################
//----------------------------------------------------------------------
// CONSTRUCTEURS / DESTRUCTEURS :
// VIRTUELLE PURES :


//----------------------------------------------------------------------
// DESSINABLE ->
    std::ostream& affiche(std::ostream&)              const override;
    virtual void dessine_sur(SupportADessin& support) const override
        {support.dessine(*this);}
    void display_gnu(std::ofstream&)                  const override;
    void Draw(SupportADessin&)                        const override;
    void ajoute_a(Systeme&)                           const override;
//----------------------------------------------------------------------
// OBJETMOBILE ->
    Vecteur evolution() override;

//######################################################################
// CLASS  :
    */
