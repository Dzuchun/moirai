SHELL = bash
CFLAGS += -I ./include -Wall

BUILD_DIR := build/
SRC_DIR := src/
BOT_BACKEND ?= "primitive"

UNIVERSAL_SRC := $(shell find $(SRC_DIR) -maxdepth 1 -name "*.c")
UNIVERSAL_OBJ := $(UNIVERSAL_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

PRIMITIVE_CLI_SRC := $(shell find $(SRC_DIR)primitive_cli -maxdepth 1 -name "*.c") $(SRC_DIR)player/primitive_io.c
PRIMITIVE_CLI_OBJ := $(PRIMITIVE_CLI_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

primitive-cli: universal-build $(PRIMITIVE_CLI_OBJ) exe-dir
	$(CC) $(PRIMITIVE_CLI_OBJ) $(UNIVERSAL_OBJ) -o $(BUILD_DIR)exe/$@ $(LDFLAGS)

RANDOM_GAME_SRC := $(shell find $(SRC_DIR)random_game -maxdepth 1 -name "*.c") $(SRC_DIR)player/random.c
RANDOM_GAME_OBJ := $(RANDOM_GAME_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

random-game: universal-build $(RANDOM_GAME_OBJ) exe-dir
	$(CC) $(RANDOM_GAME_OBJ) $(UNIVERSAL_OBJ) -o $(BUILD_DIR)exe/$@ $(LDFLAGS)

REFEREE_SRC := $(shell find $(SRC_DIR)referee -maxdepth 1 -name "*.c") $(SRC_DIR)player/random.c
REFEREE_OBJ := $(REFEREE_SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

referee: universal-build $(REFEREE_OBJ) exe-dir
	$(CC) $(REFEREE_OBJ) $(UNIVERSAL_OBJ) -o $(BUILD_DIR)exe/$@ $(LDFLAGS)

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

.PHONY: exe-dir
exe-dir:
	@ mkdir -p $(BUILD_DIR)exe

.PHONY: clean
clean:
	-rm -r $(BUILD_DIR)
