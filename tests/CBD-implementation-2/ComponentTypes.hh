#ifndef					__COMPONENT_TYPE_HH__
# define				__COMPONENT_TYPE_HH__

#include				"Position.hh"
#include				"Move.hh"
#include				"Image.hh"
#include				"Sprite.hh"
#include				"Visibility.hh"
#include				"Rotation.hh"
#include				"Text.hh"

typedef enum				EType
  {
    T_POSITION,
    T_MOVE,
    T_IMAGE,
    T_SPRITE,
    T_VISIBILITY,
    T_ROTATION,
    T_TEXT
  }					EType;

inline
Move					*MOVE(Entity *entity)
{
  return entity->getComponent<Move>(T_MOVE);
}

inline
Position				*POSITION(Entity *entity)
{
  return entity->getComponent<Position>(T_POSITION);
}

inline
Image					*IMAGE(Entity *entity)
{
  return entity->getComponent<Image>(T_IMAGE);
}

inline
Sprite					*SPRITE(Entity *entity)
{
  return entity->getComponent<Sprite>(T_SPRITE);
}

inline
Visibility				*VISIBILITY(Entity *entity)
{
  return entity->getComponent<Visibility>(T_VISIBILITY);
}

inline
Rotation				*ROTATION(Entity *entity)
{
  return entity->getComponent<Rotation>(T_ROTATION);
}

inline
Text				*TEXT(Entity *entity)
{
  return entity->getComponent<Text>(T_TEXT);
}

#endif					// __COMPONENT_TYPE_HH__
