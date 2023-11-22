CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

LIBMX_PATH = libmx
LIBMX = libmx.a
TARGET = uls

INC_FILES := -I$(INC_DIR) -I$(LIBMX_PATH)/inc
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LINKS := -L$(LIBMX_PATH) -lmx

RED = \033[31;1m
GREEN = \033[32;1m
YELLOW = \033[33;1m
CYAN = \033[36;1m

BOLD = \033[1m
CLEAN_LINE = \033[K

.PHONY: all uninstall clean reinstall install run

all: reinstall

run: install
	./$(TARGET)

install: $(LIBMX) $(TARGET)
	@printf "\r$(CLEAN_LINE)$(CYAN)$(BOLD)$(TARGET) $@ $(YELLOW)done$(CYAN)\n"


$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\r$(CLEAN_LINE)$(CYAN)$(BOLD)$(TARGET) $(YELLOW)compiling $(CYAN)$<"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FILES)

$(LIBMX):
	@$(MAKE) -sC $(LIBMX_PATH) install

$(TARGET): $(OBJ_FILES)
	@printf "\r$(CLEAN_LINE)$(CYAN)$(BOLD)$@ $(YELLOW)files compiled$(CYAN)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(INC_FILES) $(LINKS)
	@printf "\r$(CLEAN_LINE)$(CYAN)$(BOLD)$@ $(GREEN)created$(CYAN)\n"

uninstall:
	@$(MAKE) -sC $(LIBMX_PATH) uninstall
	@rm -rf $(OBJ_DIR)
	@rm -rf $(TARGET)
	@printf "\r$(CLEAN_LINE)$(TARGET) $(RED)uninstalled$(CYAN)\n"

clean:
	@$(MAKE) -sC $(LIBMX_PATH) clean
	@rm -rf $(OBJ_DIR)
	@printf "\r$(CLEAN_LINE)$(OBJ_DIR) in $(TARGET) $(RED)cleaned$(CYAN)\n"

reinstall: uninstall install
