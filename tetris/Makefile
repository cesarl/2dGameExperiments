NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror

CPPFLAGS	+=	-Icomponents -Iscenes -Imanagers -Iheaders -Igui

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image

INC		=	-I. -I/usr/include/allegro5

SRCS		=	managers/EventManager.cpp \
			managers/SceneManager.cpp \
			managers/ImageManager.cpp \
			managers/FontManager.cpp \
			managers/IdManager.cpp \
			managers/SaveManager.cpp \
			managers/Option.cpp \
			managers/MainManager.cpp \
			gui/GuiComponent.cpp \
			gui/GuiNumber.cpp \
			gui/GuiRangeNumber.cpp \
			gui/GuiSelectable.cpp \
			gui/GuiSelectableGroup.cpp \
			gui/GuiSelectableNumber.cpp \
			gui/GuiSelectableText.cpp \
			gui/GuiText.cpp \
			scenes/AScene.cpp \
			scenes/SceneMenu.cpp \
			scenes/SceneMainGame.cpp \
			scenes/ScenePause.cpp \
			scenes/SceneGameOver.cpp \
			Vector3d.cpp \
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
			TetrisGrid.cpp \
			Entity.cpp \
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
