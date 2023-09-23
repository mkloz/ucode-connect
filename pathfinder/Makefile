CC=clang
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wpedantic
INC_DIR= -Iinc -Ilibmx/inc
LINK_DIR= -Llibmx -lmx
INC= $(wildcard inc/*.h)
SRC= $(wildcard src/*.c)
OBJ= $(subst src/,obj/,$(SRC:%.c=%.o))
LIB_PATHS=libmx/libmx.a
LIBMX=LIBMX
EXE_NAME=pathfinder
PATHFINDER=PATHFINDER

all: install clean

run: install
	./$(EXE_NAME)

install: $(LIBMX) $(PATHFINDER)

$(subst src/,,$(SRC)):
	$(CC) $(CFLAGS) -c "src/$@" -o "obj/$(subst .c,.o,$@)" $(INC_DIR)

$(LIBMX):
	make -sC libmx

$(PATHFINDER): precomp $(subst src/,,$(SRC))
	$(CC) $(CFLAGS) -o $(EXE_NAME) obj/*.o $(INC_DIR) $(LINK_DIR)

precomp:
	mkdir -p obj

uninstall: clean
	make -sC libmx uninstall
	rm -rf $(EXE_NAME)

clean:
	make -sC libmx clean
	rm -rf obj

reinstall: uninstall install

.PHONY: all uninstall clean reinstall precomp install

