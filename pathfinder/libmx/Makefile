CC=clang
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wpedantic
INC_DIR= -Iinc
INC= $(wildcard inc/*.h)
SRC= $(wildcard src/*.c)
OBJ= $(subst src/,obj/,$(SRC:%.c=%.o))
LIBMX=libmx.a

all: install #RUN

run: install
	$(CC) main.c $(INC_DIR) -L. -lmx -o out
	./out

install: $(LIBMX)

$(subst src/,,$(SRC)):
	$(CC) $(CFLAGS) -c "src/$@" -o "obj/$(subst .c,.o,$@)" $(INC_DIR)

$(LIBMX): precomp $(subst src/,,$(SRC))
	ar rcs $(LIBMX) obj/*.o

precomp:
	rm -rf obj
	mkdir -p obj

uninstall: clean
	rm -f $(LIBMX)

clean:
	rm -rf obj

reinstall: uninstall install

.PHONY: all uninstall clean reinstall precomp install

