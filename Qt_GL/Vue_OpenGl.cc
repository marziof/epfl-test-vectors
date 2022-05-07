#include <vector>
#include "Vue_OpenGl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Dessinable.h"
#include "Vecteur.h"
#include <cmath>
#include "Balle.h"
#include "Obstacle.h"
#include "pendule.h"
#include "Ressort.h"
#include "Systeme.h"

using namespace std;

// ======================================================================
void VueOpenGL::dessine(Dessinable const& a_dessiner)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    a_dessiner.Draw(*this);
}
void VueOpenGL::dessine(Systeme const& a_dessiner)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    a_dessiner.Draw(*this);
}

// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();                                      // initialise la sphère
  initializePosition();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // efface l'écran

}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -7.0);
  matrice_vue.rotate(60.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue, array<double, 3> Couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}


// ======================================================================
void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue, array<double, 3> Couleur){
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

// ======================================================================


void VueOpenGL::dessineCarre(QMatrix4x4 const& point_de_vue, Vecteur const& L, Vecteur const& l, array<double, 3> Couleur)
{

  Vecteur D1(L+l), D2(L-l),D3(l-L),D4((-1*L)-l);
  vector<double> d1(D1.get_vect()), d2(D2.get_vect()), d3(D3.get_vect()), d4(D4.get_vect());

  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_TRIANGLES);
      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId,  d4[0], d4[1], d4[2]);

      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId, d3[0], d3[1], d3[2]);

      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId, d1[0], d1[1], d1[2]);
  glEnd();

  glBegin(GL_TRIANGLES);
      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId, d1[0], d1[1], d1[2]);

      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId, d2[0], d2[1], d2[2]);

      prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
      prog.setAttributeValue(SommetId, d4[0], d4[1], d4[2]);
  glEnd();

}
// ======================================================================

void VueOpenGL::dessine(Plan const& plan){
    QMatrix4x4 point_de_vue;
    vector<double> p(plan.getP().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.translate(p[0],p[1], p[2]);
    point_de_vue.scale(20);
    dessineCarre(point_de_vue, plan.getV1(), plan.getV2());
}


// ======================================================================

void VueOpenGL::dessine(Balle const& B){
    QMatrix4x4 point_de_vue;
    vector<double> p(B.getP().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.scale(B.getRayon());
    point_de_vue.translate(p[0],p[1], p[2]);
    dessineSphere(point_de_vue);
}

// ======================================================================
void VueOpenGL::dessine(Pendule const& pendule ){
    QMatrix4x4 point_de_vue;

// ON DESSINE D'ABORD LA BALLE (BOUT DU PENDULE)
    vector<double> p(pendule.getPBalle().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.scale(pendule.getRayon());
    point_de_vue.translate(p[0],p[1], p[2]);
    dessineSphere(point_de_vue);

// ON DESSINE ENSUITE UN PETIT CUBE A L'ORIGINE
    vector<double> O(pendule.getOrigine().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.scale(0.5);
    point_de_vue.translate(O[0], O[1], O[2]);
    dessineCube(point_de_vue);
}

// ======================================================================
void VueOpenGL::dessine(Ressort const& ressort){
    QMatrix4x4 point_de_vue;
// ON DESSINE D'ABORD LA BALLE (BOUT DU PENDULE)
    vector<double> p(ressort.getPBalle().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.scale(ressort.getRayon());
    point_de_vue.translate(p[0],p[1], p[2]);
    dessineSphere(point_de_vue);

// ON DESSINE ENSUITE UN PETIT CUBE A L'ORIGINE
    vector<double> O(ressort.getOrigine().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.scale(0.2);
    point_de_vue.translate(O[0], O[1], O[2]);
    dessineCube(point_de_vue);
}

// ======================================================================

void VueOpenGL::dessine(Brique const& brique){
    QMatrix4x4 point_de_vue;
    vector<double> p(brique.getP().get_vect());
    point_de_vue.setToIdentity();
    point_de_vue.translate(p[0],p[1], p[2]);
    dessineRectangle(point_de_vue, brique.getV1(), brique.getV2(), brique.getH());
}


void VueOpenGL::dessineRectangle(QMatrix4x4 const& point_de_vue, Vecteur const& L,
                                 Vecteur const& l, Vecteur const& H, array<double, 3> Couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  Vecteur A{0,0,0}, B(L), C(l), D(L+l), E(-H), F(-H+L), J(-H+l), K(-H+L+l);
  vector<double> a(A.get_vect()), b(B.get_vect()), c(C.get_vect()), d(D.get_vect()),
                 e(E.get_vect()), f(F.get_vect()), j(J.get_vect()), k(K.get_vect());

  glBegin(GL_QUADS);
  // face ABCD (+Z)
  prog.setAttributeValue(CouleurId, Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, a[0], a[1], a[2]);
  prog.setAttributeValue(SommetId, b[0], b[1], b[2]);
  prog.setAttributeValue(SommetId, c[0], c[1], c[2]);
  prog.setAttributeValue(SommetId, d[0], d[1], d[2]);

  // face EFJK (-Z)
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, e[0], e[1], e[2]);
  prog.setAttributeValue(SommetId, f[0], f[1], f[2]);
  prog.setAttributeValue(SommetId, j[0], j[1], j[2]);
  prog.setAttributeValue(SommetId, k[0], k[1], k[2]);
  // face BDFK (+L)
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, b[0], b[1], b[2]);
  prog.setAttributeValue(SommetId, d[0], d[1], d[2]);
  prog.setAttributeValue(SommetId, f[0], f[1], f[2]);
  prog.setAttributeValue(SommetId, k[0], k[1], k[2]);
  // face ACEJ (-L)
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, a[0], a[1], a[2]);
  prog.setAttributeValue(SommetId, c[0], c[1], c[2]);
  prog.setAttributeValue(SommetId, e[0], e[1], e[2]);
  prog.setAttributeValue(SommetId, j[0], j[1], j[2]);
  // face CDJK (+l)
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, c[0], c[1], c[2]);
  prog.setAttributeValue(SommetId, d[0], d[1], d[2]);
  prog.setAttributeValue(SommetId, j[0], j[1], j[2]);
  prog.setAttributeValue(SommetId, k[0], k[1], k[2]);
  // face ABEF (-l)
  prog.setAttributeValue(CouleurId,  Couleur[0], Couleur[1], Couleur[2]);
  prog.setAttributeValue(SommetId, a[0], a[1], a[2]);
  prog.setAttributeValue(SommetId, b[0], b[1], b[2]);
  prog.setAttributeValue(SommetId, e[0], e[1], e[2]);
  prog.setAttributeValue(SommetId, f[0], f[1], f[2]);
  glEnd();
}

void VueOpenGL::dessine(ChampForce const&){
  QMatrix4x4 point_de_vue;
  point_de_vue.setToIdentity();
  point_de_vue.translate(0,0, 10);
  dessineCube(point_de_vue);
}
