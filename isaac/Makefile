NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror

CPPFLAGS	+=	-Icomponents -Iscenes -Imanagers -Iheaders -I.

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image

INC		=	-I/usr/include/allegro5

SRCS		=	managers/EventManager.cpp \
			managers/SceneManager.cpp \
			managers/ImageManager.cpp \
			managers/FontManager.cpp \
			managers/IdManager.cpp \
			managers/CollisionManager.cpp \
			scenes/AScene.cpp \
			scenes/SceneMenu.cpp \
			components/Component.cpp \
			components/Image.cpp \
			components/Move.cpp \
			components/Position.cpp \
			components/Rotation.cpp \
			components/Sprite.cpp \
			components/Text.cpp \
			components/Visibility.cpp \
			components/RotationForce.cpp \
			components/ParticuleEmitter.cpp \
			components/TextInput.cpp \
			components/Input.cpp \
			components/Heros.cpp \
			components/BoundingBox.cpp \
			components/ForceResistance.cpp \
			components/Pistol.cpp \
			components/CollisionType.cpp \
			components/DangerType.cpp \
			components/Damage.cpp \
			components/Health.cpp \
			components/Death.cpp \
			components/PnjDeath.cpp \
			DrawCollection.cpp \
			Grid.cpp \
			Entity.cpp \
			Decor.cpp \
			Pnj.cpp \
			main.cpp

OBJS		=	$(SRCS:.cpp=.o)

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME) $(INC) $(LDFLAGS)
			@$(ECHO) '\033[1;37;44m> Compiled {\033[4m$(NAME)}\033[0m'

clean		:
			@$(RM) $(OBJS)
			@$(ECHO) '\033[1;37;41m> Directory cleaned\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[1;37;41m> Remove executable\033[0m'

re		:	fclean all

.PHONY		:	all clean re
