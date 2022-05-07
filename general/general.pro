TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++11



SOURCES +=\
		Balle.cc \
		ChampForce.cc \
		constantes.cc\
		IntegrateurEulerCromer.cc\
		ObjetMobile.cc\
		Obstacle.cc\
		pendule.cc\
		Ressort.cc\
		Systeme.cc\
		Vecteur.cc\
                Vent.cc\
    ventilateur.cc

HEADERS += \
		Dessinable.h \
		Balle.h\
		ChampForce.h \
		constantes.h\
		Integrateur.h\
		IntegrateurEulerCromer.h\
		ObjetMobile.h\
		Obstacle.h\
		pendule.h\
		Ressort.h\
		Systeme.h\
		Vecteur.h\
		SupportADessin.h\
                Vent.h\
    ventilateur.h

