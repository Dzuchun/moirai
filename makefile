SHELL = bash
CFLAGS += -I ./include -Wall

BUILD_DIR := build/
SRC_DIR := src/
BOT_BACKEND ?= "primitive"

UNIVERSAL_SRC := $(shell find $(SRC_DIR) -maxdepth 1 -name "*.c")
UNIVERSAL_OBJ := $(UNIVERSAL_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

PRIMITIVE_CLI_SRC := $(shell find $(SRC_DIR)primitive_cli -maxdepth 1 -name "*.c") src/player/primitive_io.c
PRIMITIVE_CLI_OBJ := $(PRIMITIVE_CLI_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

primitive-cli: universal-build $(PRIMITIVE_CLI_OBJ)
	$(CC) $(PRIMITIVE_CLI_OBJ) $(UNIVERSAL_OBJ) -o $@ $(LDFLAGS)

RANDOM_GAME_SRC := $(shell find $(SRC_DIR)random_rame -maxdepth 1 -name "*.c")
RANDOM_GAME_OBJ := $(RANDOM_GAME_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

.PHONY: universal-build
universal-build: $(UNIVERSAL_OBJ)
	@ echo "General build suceeded"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: show-config
show-config:
	@ echo "Universal sources: " $(UNIVERSAL_SRC)
	@ echo "Universal objects: " $(UNIVERSAL_OBJ)
	@ echo "Primitive cli sources:" $(PRIMITIVE_CLI_SRC)
	@ echo "Primitive cli objects:" $(PRIMITIVE_CLI_OBJ)
	@ echo "Random game sources:" $(RANDOM_GAME_SRC)
	@ echo "Random game objects:" $(RANDOM_GAME_OBJ)

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR)
	-rm ./primitive-cli
