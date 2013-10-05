#ifndef				__IMAGE_SYSTEM_HPP__
# define			__IMAGE_SYSTEM_HPP__

#include			"System.hpp"
#include			"Components.hpp"

class				ImageSystem : public System
{
public:
  virtual ~ImageSystem(){};
  ImageSystem() : System()
  {}

  virtual void			init()
  {
    require<Img>();
    require<Position>();
    require<Rotation>();
    require<Scale>();
    require<Color>();
  }

  virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &ev)
  {
    Img				*img = entity.getComponent<Img>();
    Position			*pos = entity.getComponent<Position>();
    Rotation			*rot = entity.getComponent<Rotation>();
    Scale			*scale = entity.getComponent<Scale>();
    Color			*color = entity.getComponent<Color>();

    glPushMatrix();

    // glEnable(GL_TEXTURE_2D);

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTranslatef(pos->position.x, pos->position.y, pos->position.z);

    glScalef(scale->scale.x, scale->scale.y, scale->scale.z);

    glTranslatef(rot->axe.x,
		 rot->axe.y,
		 rot->axe.z);

    glRotatef(rot->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rot->rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rot->rotation.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(- rot->axe.x,
		 - rot->axe.y,
		 - rot->axe.z);

    glColor4f(color->r, color->g, color->b, color->a);
    glCallList(img->img->getDisplayList());
    glPopMatrix();
    // glDisable(GL_TEXTURE_2D);
    (void)color;
    (void)rot;
    (void)ev;
  }

private:
};

#endif				// __IMAGE_SYSTEM_HPP__
