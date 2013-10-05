#include				"Logger.hpp"

#include				"AnimationLoader.hpp"
#include				"ImageLoader.hpp"
#include				"SkyboxLoader.hpp"
#include				"ShaderLoader.hpp"
#include				"ShaderProgramLoader.hpp"
#include				"ObjLoader.hpp"
#include				"TextureLoader.hpp"

#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"
#include				<exception>

#include				"EntityManager.hpp"
#include				"SystemManager.hpp"

#include				"Systems.hpp"

#include				"MapGenerator.hpp"

#include				"Components.hpp"


int					main()
{

	////////////////////
	// initialisation //
	////////////////////

	if (!MainManager::getInstance().init())
		return 0;
	if (!MainManager::getInstance().launch(1344, 704))
		return 0;

	//////////
	// main //
	//////////

	MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
	MediaManager::getInstance().registerLoader(new SkyboxLoader, ".skybox");
	MediaManager::getInstance().registerLoader(new AnimationLoader, ".anim");
	MediaManager::getInstance().registerLoader(new ShaderLoader, ".vert,.pix");
	MediaManager::getInstance().registerLoader(new ShaderProgramLoader, ".prgm");
	MediaManager::getInstance().registerLoader(new ObjLoader, ".obj");
	MediaManager::getInstance().registerLoader(new TextureLoader, ".text");
	MediaManager::getInstance().addSearchPath("./main/assets/imgs/");
	MediaManager::getInstance().addSearchPath("./main/assets/animations/");
	MediaManager::getInstance().addSearchPath("./main/assets/shaders/");
	MediaManager::getInstance().addSearchPath("./main/assets/models/");
	MediaManager::getInstance().addSearchPath("./main/assets/textures/");

	SystemManager::getInstance().add<InputSystem>(0);
	SystemManager::getInstance().add<PistolSystem>(0);
	SystemManager::getInstance().add<InputMovementSystem>(10);
	SystemManager::getInstance().add<LifetimeSystem>(12);
	SystemManager::getInstance().add<VelocityFrictionSystem>(20);
	SystemManager::getInstance().add<BoundingBoxSystem>(30);
	SystemManager::getInstance().add<BulletSystem>(31);
	SystemManager::getInstance().add<RotationForceSystem>(31);
	SystemManager::getInstance().add<PhysicSystem>(40);
	SystemManager::getInstance().add<VelocitySystem>(90);
	SystemManager::getInstance().add<ColorEasingSystem>(90);
	SystemManager::getInstance().add<ImageSystem>(100, true);
	SystemManager::getInstance().add<SpriteSystem>(100, true);
	SystemManager::getInstance().add<ObjModelSystem>(100, true);

	std::cout << BoundingBox::getTypeId() << " "
		<< Collision::getTypeId() << " "
		<< ColorEasing::getTypeId() << " "
		<< Color::getTypeId() << " "
		<< Death::getTypeId() << " "
		<< Img::getTypeId() << " "
		<< InputMovement::getTypeId() << " "
		<< Lifetime::getTypeId() << " "
		<< NullCpt::getTypeId() << " "
		<< Physic::getTypeId() << " "
		<< Pistol::getTypeId() << " "
		<< Position::getTypeId() << " "
		<< RotationForce::getTypeId() << " "
		<< Rotation::getTypeId() << " "
		<< Scale::getTypeId() << " "
		<< VelocityFriction::getTypeId() << " "
		<< Velocity::getTypeId() << std::endl;

	try
	{
		BoundingBoxSystem *s = SystemManager::getInstance().getSystem<BoundingBoxSystem>();
		if (s)
			s->addException("Good", "Good");


		////////////////////
		// GENRATE PLAYER //
		////////////////////

		EntityData				&e = EntityManager::getInstance().newEntity();

		e.setLayer("Good");

		e.addComponent<Rotation>();
		Position *posC = e.addComponent<Position>();
		Scale *scaleC = e.addComponent<Scale>();
		Color *colorC = e.addComponent<Color>();
		BoundingBox *bbC = e.addComponent<BoundingBox>();
		Physic *phy = e.addComponent<Physic>();
		e.addComponent<InputMovement>()->speed = 1000.0f;
		e.addComponent<VelocityFriction>()->friction = 0.99f;
		e.addComponent<Velocity>();
		e.addComponent<Pistol>();

		*colorC = Color(1.0f, 0.0f, 0.0f, 1.0f);
		bbC->set(glm::vec3(50.0f, 45.0f, 0.0f));
		posC->position = glm::vec3(64.0f * 2.0f, 64.0f * 2.0f, 0.1f);
		Sprite *spriteC = e.addComponent<Sprite>();
		spriteC->animation = ResourceManager::getInstance().get<AnimationMedia>("herosWalkSide.anim");
		scaleC->scale = glm::vec3(50.0f, 45.0f, 0.0f);
		phy->fixed = false;


		MapGenerator g;
		g.generate(21, 11);

		// ShaderProgramPtr p = ResourceManager::getInstance().get<ShaderProgram>("test.prgm");
		// p->enable();
		// glUniform1i(p->getVarId("varTest"), 2);

		/////////////////////////////////////
		// test new graphic implementation //
		/////////////////////////////////////

		/*e = EntityManager::getInstance().newEntity();
		ComponentManager::getInstance().addComponent<Position>(e).position = glm::vec3(64.0f * 2.0f, 64.0f * 2.0f, 50.0f);
		ComponentManager::getInstance().addComponent<Model>(e).obj = ResourceManager::getInstance().get<ObjModelMedia>("cube.obj");
		ComponentManager::getInstance().addComponent<Scale>(e).scale = glm::vec3(50.0f, 50.0f, 50.0f);
		ComponentManager::getInstance().addComponent<Rotation>(e).rotation = glm::vec3(45.0f,0.0f,0.0f);
		ComponentManager::getInstance().addComponent<Color>(e) = Color(0.0f, 0.0f, 1.0f, 1.0f);
		ComponentManager::getInstance().addComponent<RotationForce>(e).force = glm::vec3(10.0f,15.0f,6.0f);

		Shader &shader = ComponentManager::getInstance().addComponent<Shader>(e);
		shader.setShader("cube.prgm");


		e = EntityManager::getInstance().newEntity();
		ComponentManager::getInstance().addComponent<Position>(e).position = glm::vec3(64.0f * 4.0f, 64.0f * 2.0f, 50.0f);
		ComponentManager::getInstance().addComponent<Model>(e).obj = ResourceManager::getInstance().get<ObjModelMedia>("plane.obj");
		ComponentManager::getInstance().addComponent<Scale>(e).scale = glm::vec3(30.0f, 30.0f, 30.0f);
		ComponentManager::getInstance().addComponent<Rotation>(e).rotation = glm::vec3(45.0f,0.0f,0.0f);
		ComponentManager::getInstance().addComponent<Color>(e) = Color(0.0f, 1.0f, 0.0f, 1.0f);
		ComponentManager::getInstance().addComponent<RotationForce>(e).force = glm::vec3(10.0f,15.0f,6.0f);

		Shader &shader2 = ComponentManager::getInstance().addComponent<Shader>(e);
		shader2.setShader("plane.prgm");*/

		EventManager::getInstance().play();
	}
	catch (const std::exception &e)
	{
		ILogger::log(e.what());
	}
	return 0;
}
