#ifndef					__COMPONENT_TYPE_HH__
# define				__COMPONENT_TYPE_HH__

#include				<fstream>
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
#include				"CollisionType.hh"
#include				"DangerType.hh"
#include				"Damage.hh"
#include				"Health.hh"
#include				"PnjHealth.hh"
#include				"Death.hh"
#include				"PnjDeath.hh"

typedef enum				EType
  {
    T_POSITION = 1,
    T_MOVE = 2,
    T_IMAGE = 3,
    T_SPRITE = 4,
    T_VISIBILITY = 5,
    T_ROTATION = 6,
    T_TEXT = 7,
    T_ROTATION_FORCE = 8,
    T_PARTICULE_EMITTER = 9,
    T_TEXT_INPUT = 10,
    T_INPUT = 11,
    T_HEROS = 12,
    T_BOUNDING_BOX = 13,
    T_FORCE_RESISTANCE = 14,
    T_PISTOL = 15,
    T_COLLISION_TYPE = 16,
    T_DANGER_TYPE = 17,
    T_DAMAGE = 18,
    T_HEALTH = 19,
    T_PNJ_HEALTH = 20,
    T_DEATH = 21,
    T_PNJ_DEATH = 22
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
Pistol					*PISTOL(Entity *entity)
{
  return entity->getComponent<Pistol>(T_PISTOL);
}

inline
CollisionType				*COLLISION_TYPE(Entity *entity)
{
  return entity->getComponent<CollisionType>(T_COLLISION_TYPE);
}

inline
DangerType				*DANGER_TYPE(Entity *entity)
{
  return entity->getComponent<DangerType>(T_DANGER_TYPE);
}

inline
Damage					*DAMAGE(Entity *entity)
{
  return entity->getComponent<Damage>(T_DAMAGE);
}

inline
Health					*HEALTH(Entity *entity)
{
  return entity->getComponent<Health>(T_HEALTH);
}

inline
PnjHealth				*PNJ_HEALTH(Entity *entity)
{
  return entity->getComponent<PnjHealth>(T_HEALTH);
}

inline
Death					*DEATH(Entity *entity)
{
  return entity->getComponent<Death>(T_DEATH);
}

inline
PnjDeath				*PNJ_DEATH(Entity *entity)
{
  return entity->getComponent<PnjDeath>(T_DEATH);
}

inline
void					unserializeComponent(int type, Entity *entity, std::ifstream *f)
{
  AComponent				*c = NULL;
  switch(type)
    {
    case T_POSITION:
      c = POSITION(entity);
      break;
    case T_MOVE:
      c = MOVE(entity);
      break;
    case T_IMAGE:
      c = IMAGE(entity);
      break;
    case T_SPRITE:
      c = SPRITE(entity);
      break;
    case T_VISIBILITY:
      c = VISIBILITY(entity);
      break;
    case T_ROTATION:
      c = ROTATION(entity);
      break;
    case T_TEXT:
      c = TEXT(entity);
      break;
    case T_ROTATION_FORCE:
      c = ROTATION_FORCE(entity);
      break;
    case T_PARTICULE_EMITTER:
      c = PARTICULE_EMITTER(entity);
      break;
    case T_TEXT_INPUT:
      c = TEXT_INPUT(entity);
      break;
    case T_INPUT:
      c = INPUT(entity);
      break;
    case T_HEROS:
      c = HEROS(entity);
      break;
    case T_BOUNDING_BOX:
      c = BOUNDING_BOX(entity);
      break;
    case T_FORCE_RESISTANCE:
      c = FORCE_RESISTANCE(entity);
      break;
    case T_PISTOL:
      c = PISTOL(entity);
      break;
    case T_COLLISION_TYPE:
      c = COLLISION_TYPE(entity);
      break;
    case T_DANGER_TYPE:
      c = DANGER_TYPE(entity);
      break;
    case T_DAMAGE:
      c = DAMAGE(entity);
      break;
    case T_HEALTH:
      c = HEALTH(entity);
      break;
    case T_PNJ_HEALTH:
      c = PNJ_HEALTH(entity);
      break;
    case T_DEATH:
      c = DEATH(entity);
      break;
    case T_PNJ_DEATH:
      c = PNJ_DEATH(entity);
      break;
    default:
      c = NULL;
      break;
    }
  if (c)
  c->unserialize(f);
}

#endif					// __COMPONENT_TYPE_HH__
