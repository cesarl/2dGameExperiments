#ifndef				__OBJ_MODEL_SYSTEM_HPP__
# define			__OBJ_MODEL_SYSTEM_HPP__

#include			"System.hpp"
#include			"Components.hpp"

class				ObjModelSystem : public System
{
public:
	virtual ~ObjModelSystem(){};
	ObjModelSystem() : System()
	{}

	virtual void			init()
	{
		require<Model>();
		require<Position>();
		require<Shader>();
		require<Rotation>();
		require<Scale>();
		require<Color>();
	}

	virtual void			update(EntityData &entity, float, const ALLEGRO_EVENT &ev)
	{
		Model	        *model = entity.getComponent<Model>();
		Position		*pos = entity.getComponent<Position>();
		Shader			*shader = entity.getComponent<Shader>();
		Scale			*scale = entity.getComponent<Scale>();
		Rotation		*rot = entity.getComponent<Rotation>();
		Color			*color = entity.getComponent<Color>();

		glPushMatrix();

		// enable shader
		glUseProgram(shader->getProgram()->getId());

		glTranslatef(pos->position.x, pos->position.y, pos->position.z);

		glUniform3f(shader->getProgram()->getVarId("scale"), scale->scale.x, scale->scale.y, scale->scale.z);

		glColor4f(color->r, color->g, color->b, color->a);

		glTranslatef(rot->axe.x,
			rot->axe.y,
			rot->axe.z);

		glRotatef(rot->rotation.x, 1.0f, 0.0f, 0.0f);
		glRotatef(rot->rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(rot->rotation.z, 0.0f, 0.0f, 1.0f);

		glTranslatef(- rot->axe.x,
			- rot->axe.y,
			- rot->axe.z);

		shader->bindTextures();
		glBindBuffer(GL_ARRAY_BUFFER, model->obj->getVertexBuffer());    
		glVertexPointer(3, GL_FLOAT, 0, (void*)(0));
		shader->applyTexturesCoordinates();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glDrawArrays(GL_TRIANGLES, 0, model->obj->getVerticesNumber());

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// disable shader
		glUseProgram(0);

		glPopMatrix();

		(void)ev;
	}

private:
};

#endif				// __OBJ_MODEL_SYSTEM_HPP__
