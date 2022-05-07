#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "Vue_OpenGl.h"
#include "Systeme.h"
#include "Balle.h"
#include "Obstacle.h"
#include "pendule.h"

class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(QWidget* parent = nullptr)
    : QOpenGLWidget(parent)
  {
      Pendule p({0,0,7}, {1,1,0}, {0,0,0}, 20, 0, 0.6, 5, 2, 0.5);
      Brique br({8, 0, 7}, {2,0,0}, {0,3,0}, 4);
      Balle B({0,2,2}, {0,0,0}, {0,0,0}, 1, 1);
      Plan plan({10,0,10}, {0,1,0}, {0,0,1});
      B.ajoute_a(c); p.ajoute_a(c);plan.ajoute_a(c);br.ajoute_a(c);

  }
  virtual ~GLWidget() = default;
  Systeme c;
private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;

  // objets à dessiner, faire évoluer
};
