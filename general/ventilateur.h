#pragma once
#include "Dessinable.h"
#include "Obstacle.h"
#include "ChampForce.h"
#include "Vent.h"


class Ventilateur {

private:
    Brique B;
    Vent V;

public:
    Ventilateur(Vecteur o, Vecteur n, Vecteur l, Vecteur L, Vecteur p, Vecteur i, double mu)
    :V(o, n, l, L, p, i),
     B(o, l, L,  mu)
    {}
};
