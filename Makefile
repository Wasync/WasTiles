NAME = tiles

FLAGS = -fsanitize=address
INCLUDES = -I includes/ -I includes/SDL2/ -I includes/SDLX/

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_image.dylib $(LIB_DIR)libSDL2_ttf.dylib
STATIC_LIB = -L -l $(LIB_DIR)libSDLX.a

SRCS_DIR = srcs/

BIN_DIR = bin/

SRCS_NAMES =			\
	main 				\
	game				\
	buttons				\

C_FILES =				\
	$(addprefix $(SRCS_DIR), $(SRCS_NAMES))		\

SRCS = $(addsuffix .c, $(C_FILES))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

web:
	emcc -I includes/ -I includes/SDLX/ -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file Assets/ srcs/*.c srcs/SDLX/*.c -o tiles.html

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES) -L -l $(STATIC_LIB)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
