CC=clang
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wpedantic
INC= $(wildcard inc/*.h)
SRC= $(wildcard src/*.c)
OBJ= $(subst src/,obj/,$(SRC:%.c=%.o))
LIBMX_PATH=libmx
LIBMX=libmx.a
PATHFINDER=pathfinder
INC_DIR= -Iinc -I$(LIBMX_PATH)/inc
LINK_DIR= -L$(LIBMX_PATH) -lmx

all: install

run: install
	./$(PATHFINDER)

install: $(LIBMX) $(PATHFINDER)

$(subst src/,,$(SRC)):
	$(CC) $(CFLAGS) -c "src/$@" -o "obj/$(subst .c,.o,$@)" $(INC_DIR)

$(LIBMX):
	make -sC $(LIBMX_PATH)

$(PATHFINDER): precomp $(subst src/,,$(SRC))
	$(CC) $(CFLAGS) -o $(PATHFINDER) obj/*.o $(INC_DIR) $(LINK_DIR)

precomp:
	rm -rf obj
	mkdir -p obj

uninstall: clean
	make -sC $(LIBMX_PATH) uninstall
	rm -rf $(PATHFINDER)

clean:
	make -sC $(LIBMX_PATH) clean
	rm -rf obj

reinstall: uninstall install

.PHONY: all uninstall clean reinstall precomp install run

