NAME	= cub3D
CC		= cc
CFLAGS	:= -g3 -Wextra -Wall -Werror
LIBMLX	:= ./.lib/MLX42
BIN		:= bin

FILES	= main.c init_cub3d.c

M_PATH	= src

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= $(addprefix  $(M_PATH)/, $(FILES))
OBJS	= $(patsubst %, $(BIN)/%, $(notdir $(SRCS:.c=.o)))

all: $(BIN) $(LIBS) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBS):
ifeq ($(wildcard $(LIBMLX)/build/ ), )
	@if [ ! -d "$(LIBMLX)" ]; then \
		mkdir .lib && cd ./.lib && git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	# @cd ./.lib/MLX42/ && sed -i "s/(VERSION 3.18.0)/(VERSION 3.16.0)/" CMakeLists.txt
	@cd ./.lib/MLX42/ && cmake -B build
	@cd ./.lib/MLX42/ && cmake --build build -j4
endif

$(BIN):
	@mkdir -p $(BIN)

$(BIN)/%.o: $(M_PATH)/%.c | $(BIN)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf $(BIN)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re