#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "GlSphere.h"
#include "SupportADessin.h"
#include <array>
class Systeme;
class Vecteur;
class Dessinable;
class Balle;
class Plan;
class Ressort;
class Pendule;
class Brique;
class ChampForce;

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  void dessine(Dessinable const&) override;
  void dessine(Systeme const&) override;
  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4(), std::array<double, 3> = {0,0.6,0});
  void dessineSphere(QMatrix4x4 const& point_de_vue, std::array<double, 3> = {0, 0.8, 0.8});
  void dessineRectangle(QMatrix4x4 const& ,Vecteur const&,Vecteur const&,Vecteur const&, std::array<double, 3> = {0.7, 0.2, 0.8});
  void dessineCarre(QMatrix4x4 const& point_de_vue, Vecteur const& d1, Vecteur const& d2, std::array<double, 3> ={0.3,0.3,0.3});

  void dessine(Plan const& P) override;
  void dessine(Balle const& B) override;
  void dessine(Pendule const&) override;
  void dessine(Ressort const&) override;
  void dessine(Brique const& brique) override;
  void dessine(ChampForce const&) override;
private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra
  QMatrix4x4 matrice_vue;
};
