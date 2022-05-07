#pragma once

#include <iostream>
#include "SupportADessin.h"

class Dessinable;
class Systeme;
class Plan;
class Balle;
class Pendule;
class Ressort;
class Brique;
class ChampForce;

//######################################################################
// CLASS  : TEXTVIEWER
class TextViewer: public SupportADessin{
private:
    std::ostream& flot;

public:
    TextViewer(std::ostream& flot)
       : flot(flot)  {}

    virtual ~TextViewer()                    = default;
    // on ne copie pas les TextViewer
    TextViewer(TextViewer const&)            = delete;
    TextViewer& operator=(TextViewer const&) = delete;
     // mais on peut les déplacer
    TextViewer(TextViewer&&)                 = default;
    TextViewer& operator=(TextViewer&&)      = default;
//----------------------------------------------------------------------
// SUPPORTADESSIN ->
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
