#ifndef					__COMPONENT_TYPE_HH__
# define				__COMPONENT_TYPE_HH__

#include				"Position.hh"
#include				"Move.hh"
#include				"Image.hh"
#include				"Sprite.hh"
#include				"Visibility.hh"
#include				"Rotation.hh"
#include				"Text.hh"
#include				"RotationForce.hh"
#include				"ParticuleEmitter.hh"
#include				"TextInput.hh"
#include				"Input.hh"
#include				"Heros.hh"
#include				"BoundingBox.hh"
#include				"ForceResistance.hh"
#include				"Pistol.hh"

typedef enum				EType
  {
    T_POSITION,
    T_MOVE,
    T_IMAGE,
    T_SPRITE,
    T_VISIBILITY,
    T_ROTATION,
    T_TEXT,
    T_ROTATION_FORCE,
    T_PARTICULE_EMITTER,
    T_TEXT_INPUT,
    T_INPUT,
    T_HEROS,
    T_BOUNDING_BOX,
    T_FORCE_RESISTANCE,
    T_PISTOL
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
Text					*TEXT(Entity *entity)
{
  return entity->getComponent<Text>(T_TEXT);
}

inline
RotationForce				*ROTATION_FORCE(Entity *entity)
{
  return entity->getComponent<RotationForce>(T_ROTATION_FORCE);
}

inline
ParticuleEmitter			*PARTICULE_EMITTER(Entity *entity)
{
  return entity->getComponent<ParticuleEmitter>(T_PARTICULE_EMITTER);
}

inline
TextInput				*TEXT_INPUT(Entity *entity)
{
  return entity->getComponent<TextInput>(T_TEXT_INPUT);
}

inline
Input					*INPUT(Entity *entity)
{
  return entity->getComponent<Input>(T_INPUT);
}

inline
Heros					*HEROS(Entity *entity)
{
  return entity->getComponent<Heros>(T_HEROS);
}

inline
BoundingBox				*BOUNDING_BOX(Entity *entity)
{
  return entity->getComponent<BoundingBox>(T_BOUNDING_BOX);
}

inline
ForceResistance				*FORCE_RESISTANCE(Entity *entity)
{
  return entity->getComponent<ForceResistance>(T_FORCE_RESISTANCE);
}

inline
Pistol				*PISTOL(Entity *entity)
{
  return entity->getComponent<Pistol>(T_PISTOL);
}

#endif					// __COMPONENT_TYPE_HH__
