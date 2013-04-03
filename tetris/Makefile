NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image

INC		=	-I. -I/usr/include/allegro5

SRCS		=	AScene.cpp \
			EventManager.cpp \
			SceneManager.cpp \
			ImageManager.cpp \
			FontManager.cpp \
			IdManager.cpp \
			SceneMenu.cpp \
			SceneMainGame.cpp \
			ScenePause.cpp \
			Entity.cpp \
			AContentComponent.cpp \
			ContentComponentImage.cpp \
			ContentComponentText.cpp \
			ContentComponentSprite.cpp \
			TetrisGrid.cpp \
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