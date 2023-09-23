CC=clang
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wpedantic
INC_DIR= -Iinc
INC= $(wildcard inc/*.h)
SRC= $(wildcard src/*.c)
OBJ= $(subst src/,obj/,$(SRC:%.c=%.o))
LIB_NAMES=libmx.a
LIBMX=LIBMX

all: install #RUN

RUN:
	$(CC) main.c $(INC_DIR) -L. -lmx -o out
	./out
install: $(LIBMX)

$(subst src/,,$(SRC)):
	$(CC) $(CFLAGS) -c "src/$@" -o "obj/$(subst .c,.o,$@)" $(INC_DIR)

$(LIBMX): precomp $(subst src/,,$(SRC))
	ar rcs $(LIB_NAMES) obj/*.o

precomp:
	mkdir -p obj

uninstall: clean
	rm -f $(LIB_NAMES)

clean:
	rm -rf obj

reinstall: uninstall install

.PHONY: all uninstall clean reinstall precomp install

