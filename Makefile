NAME	= cub3D
CC		= cc
CFLAGS	:= -g3 -Wextra -Wall -Werror

SRC_PATH	= src
MLX_PATH	:= ./.lib/MLX42
LIBFT	:= ./libft/libft.a
MLX42_LIB = $(MLX_PATH)/build/libmlx42.a
LIBFLAGS := -ldl -lglfw -pthread -lm
LIBS	= $(MLX42_LIB) $(LIBFT)


BIN		:= bin

SRCS	= $(addprefix  $(SRC_PATH)/, $(FILES))
FILES	= main.c \
			free.c \
			init_cub3d.c \
			graphics/background.c \
			graphics/frame_loop.c \
			graphics/raycasting.c \
			graphics/vector_operations.c \
			graphics/walls.c \
			graphics/minimap.c \
			graphics/element_raycast.c \
			graphics/element_raycast_utils.c \
			graphics/elements_sorting.c \
			graphics/first_person.c \
			graphics/ui.c \
			graphics/progress_bar.c \
			action/action_key_hook.c \
			action/move_logic.c \
			action/mouse_hook.c \
			action/shooting.c \
			action/shooting_utils.c \
			action/enemy_shots.c \
			action/life_check.c \
			action/objective.c \
			action/damage_animation.c \
			init/texture.c \
			init/utils.c \
			validation/map_validation.c \
			validation/map_validation_utils.c \
			validation/map_validation_aux.c \
			validation/read_and_save_metadata.c \
			validation/metadata_validation.c \
			validation/metadata_validation_utils.c \
			validation/get_map.c \
			validation/process_map_info.c \

HEADERS	= -I ./include -I $(MLX_PATH)/include -I ./libft
OBJS = $(SRCS:$(SRC_PATH)/%.c=$(BIN)/%.o)

# COLORS
GREEN       := \033[1;32m
RED         := \033[1;31m
WHITE       := \033[1;37m
YELLOW      := \033[1;33m
BOLD        := \033[1;1m
ORANGE      := \033[38;2;255;165;0m
BLUE        := \033[1;34m
MAGENT      := \033[1;35m
CYAN        := \033[1;36m
RESET       := \033[0m


all: $(BIN) mlx42 $(NAME)

mlx42: $(MLX42_LIB)

$(LIBFT):
	@make -sC ./libft

$(NAME): $(LIBFT) $(OBJS) $(MLX42_LIB)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFLAGS) \
		&& printf "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️\n" \
		&& printf "⬜️$(BOLD)$(RED)\/\/\/\/ $(YELLOW)COMPILED$(RED) \/\/\/\/$(RESET)⬜️\n" \
		&& printf "⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️⬜️\n"

$(MLX42_LIB):
ifeq ($(wildcard $(MLX_PATH)/build/ ), )
	@if [ ! -d "$(MLX_PATH)" ]; then \
		mkdir .lib && cd ./.lib && git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cd ./.lib/MLX42/ && cmake -B build
	@cd ./.lib/MLX42/ && make -s -C build -j4
endif

$(BIN):
	@mkdir -p $(BIN)

$(BIN)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "$(YELLOW)Compiling: $(ORANGE)$(notdir $<)$(RESET)\n"

clean:
	@rm -rf $(BIN)
	@make -sC ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -sC ./libft fclean

mlxclean:
	@rm -rf ./.lib

re: fclean all

.PHONY: all, clean, fclean, re