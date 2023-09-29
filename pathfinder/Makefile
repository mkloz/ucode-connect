CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

LIBMX_PATH = libmx
LIBMX = libmx.a
PATHFINDER = pathfinder

INC := -I$(INC_DIR) -I$(LIBMX_PATH)/inc
SRC := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
LINK := -L$(LIBMX_PATH) -lmx

.PHONY: all uninstall clean reinstall install run

all: reinstall

run: install
	./$(PATHFINDER)

install: $(LIBMX) $(PATHFINDER)
	@printf "\r\033[K\033[01;36m$(PATHFINDER) $@ \033[33;1mdone\033[01;36m\n"


$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r\033[K\033[01;36m$(PATHFINDER) \033[33;1mcompiling \033[01;36m$<"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBMX):
	@$(MAKE) -sC $(LIBMX_PATH) install

$(PATHFINDER): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LINK)
	@printf "\r\033[K\033[01;36m$@ \033[32;1mcreated\033[01;36m\n"

uninstall:
	@$(MAKE) -sC $(LIBMX_PATH) uninstall
	@rm -rf $(OBJ_DIR)
	@rm -rf $(PATHFINDER)
	@printf "\r\033[K$(PATHFINDER) \033[31;1muninstalled\033[01;36m\n"

clean:
	@$(MAKE) -sC $(LIBMX_PATH) clean
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[K$(OBJ_DIR) in $(PATHFINDER) \033[31;1mcleaned\033[01;36m\n"

reinstall: uninstall install
