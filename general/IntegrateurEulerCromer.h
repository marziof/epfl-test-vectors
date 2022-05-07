#pragma once
#include <memory>
#include "Integrateur.h"

class ObjetMobile;

class IntegrateurEulerCromer: public Integrateur{
public:
	void evolue(ObjetMobile&, double) const;

    void iteration(const std::unique_ptr<ObjetMobile>&, std::size_t&, double&) const;
};


