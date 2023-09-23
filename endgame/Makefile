CC=clang
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wpedantic
INC_DIR= -Iinc
LINK_DIR_MAC= -F resource/frameworks -lm -rpath resource/frameworks -framework SDL2 \
    -framework SDL2_image \
    -framework SDL2_mixer \
    -framework SDL2_ttf
LINK_DIR_LINUX= -Lresource/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
INC= $(wildcard inc/*.h)
SRC= $(wildcard src/*.c)
OBJ= $(subst src/,obj/,$(SRC:%.c=%.o))
EXE_NAME=endgame
LINK_DIR= $(LINK_DIR_LINUX)

all: ENDGAME clean

$(subst src/,,$(SRC)):
	$(CC) $(CFLAGS) -c "src/$@" -o "obj/$(subst .c,.o,$@)" $(INC_DIR)
 
ENDGAME: precomp $(subst src/,,$(SRC))
	$(CC) $(CFLAGS) -o $(EXE_NAME) obj/*.o $(INC_DIR) $(LINK_DIR)

precomp:
	mkdir -p obj

uninstall: clean
	rm -f $(EXE_NAME)

clean:
	rm -rf obj

reinstall: uninstall all

