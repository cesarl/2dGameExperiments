#ifndef					__SKYBOX_MEDIA_HPP__
# define				__SKYBOX_MEDIA_HPP__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Vector3d.hh"
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"

class					SkyboxMedia : public Resource
{
public:
  SkyboxMedia(GLuint tex, ALLEGRO_BITMAP **bmp, std::string const & name, bool force) :
    Resource(name, force),
    tex_(tex),
    bmp_(bmp)
  {};

  virtual void				operator=(SkyboxMedia & o)
  {
    this->tex_ = o.tex_;
  }

  void					draw(const Vector3d & rotation) const
  {

    glEnable(GL_TEXTURE_CUBE_MAP);
    glDepthMask(GL_FALSE);

    // Taille du cube
    float t = 100.0f;

    // Utilisation de la texture CubeMap
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->tex_);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // Réglage de l'orientation
    glPushMatrix();
    glLoadIdentity();
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f );

    //    glTranslatef(position.x,position.y,position.z);

    // Rendu de la géométrie
    glBegin(GL_TRIANGLE_STRIP);// X Négatif
    glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
    glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
    glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
    glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);// X Positif
    glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
    glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
    glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
    glTexCoord3f(t,t,t); glVertex3f(t,t,t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);// Y Négatif
    glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
    glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
    glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
    glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);// Y Positif
    glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
    glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
    glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
    glTexCoord3f(t,t,t); glVertex3f(t,t,t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);// Z Négatif
    glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
    glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
    glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
    glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);// Z Positif
    glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
    glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
    glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
    glTexCoord3f(t,t,t); glVertex3f(t,t,t);
    glEnd();

    // Réinitialisation de la matrice ModelView
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glDepthMask(GL_TRUE);
    glDisable(GL_TEXTURE_CUBE_MAP);
    // glEnable(GL_LIGHTING);

    (void)rotation;

  }

  virtual ~SkyboxMedia()
  {
    for (int i = 0; i < 6; ++i)
      {
	if (this->bmp_[i])
	  al_destroy_bitmap(this->bmp_[i]);
      }
    delete [] this->bmp_;
    glDeleteTextures(1, &tex_);
  };
private:
  GLuint				tex_;
  ALLEGRO_BITMAP			**bmp_;
};

typedef					SmartPtr<SkyboxMedia, InternalRef> SkyboxMediaPtr;

#endif					// __SKYBOX_MEDIA_HPP__
