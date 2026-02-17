# Colours (only used with printf, safe in dash)
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m
YELLOW = \033[33m
RED    = \033[31m

# Executable
NAME   = miniRT

# Compiler / flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I./libft

# Libft
LIBFT_DIR = ./libft
LIBFT_A   = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
LIBFT_LNK = -L$(LIBFT_DIR) -lft

# OS detection
UNAME_S := $(shell uname -s)

# sous_dossier
MLX_ROOT = mlx

ifeq ($(UNAME_S), Darwin)            # macOS
	MLX_DIR   = $(MLX_ROOT)/mlx_macOS
	MLX_A     = $(MLX_DIR)/libmlx.a
	MLX_INC   = -I$(MLX_DIR)
	MLX_LNK   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	# Evite les warnings OpenGL déprécié sur macOS
	CFLAGS   += -DGL_SILENCE_DEPRECATION
else ifeq ($(UNAME_S), Linux)        # Linux
	MLX_DIR   = $(MLX_ROOT)/minilibx-linux
	MLX_A     = $(MLX_DIR)/libmlx_Linux.a
	MLX_INC   = -I$(MLX_DIR)
	MLX_LNK   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
	# -Wno-cast-function-type is GCC-only; skip on clang
	ifeq ($(shell $(CC) -dumpversion 2>/dev/null | grep -c '^'),1)
		CFLAGS += $(shell $(CC) -Wno-bad-function-cast -x c -c /dev/null -o /dev/null 2>/dev/null && echo -Wno-bad-function-cast)
	endif
else                                  # Autre
	$(error OS non supporté automatiquement. Ajuste MLX_DIR/flags.)
endif

INCLUDES += $(MLX_INC) $(LIBFT_INC)

# Link flags (final ld)
LDFLAGS =
LIBS    = $(MLX_LNK) $(LIBFT_LNK)

# Directories
SRCDIR = ./src
OBJDIR = obj

# Find all .c files recursively in src directory
SRCS = $(shell find $(SRCDIR) -name "*.c" -type f)

# Generate object files automatically with same directory structure
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Rules
all: $(NAME)

# Create object directory and subdirectories dynamically
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(sort $(dir $(OBJS)))

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# libft
libft: $(LIBFT_A)
$(LIBFT_A):
	@printf "$(BLUE)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory > /dev/null
	@printf "$(GREEN)✓ libft built.$(RESET)\n"

# mlx
mlx: $(MLX_A)
$(MLX_A):
	@printf "$(BLUE)Building MiniLibX in $(MLX_DIR)...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) CC=gcc --no-print-directory > /dev/null || true
	@printf "$(GREEN)✓ MiniLibX ready (or already built).$(RESET)\n"

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)✓ $(NAME) created.$(RESET)\n"

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory > /dev/null || true
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null || true
	@printf "$(GREEN)✓ Objects removed.$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing $(NAME)...$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null || true
	@printf "$(GREEN)✓ Full clean done.$(RESET)\n"

re: fclean all

bonus: all

# Help rule
help:
	@printf "$(BLUE)Available targets:$(RESET)\n"
	@printf "  $(GREEN)make$(RESET)        - Build the $(NAME) program\n"
	@printf "  $(GREEN)make clean$(RESET)  - Remove object files (and clean libs)\n"
	@printf "  $(GREEN)make fclean$(RESET) - Remove all generated files\n"
	@printf "  $(GREEN)make re$(RESET)     - Rebuild everything (clean build)\n"
	@printf "  $(GREEN)make libft$(RESET)  - Build libft only\n"
	@printf "  $(GREEN)make mlx$(RESET)    - Build MiniLibX only\n"
	@printf "  $(GREEN)make help$(RESET)   - Show this help message\n"

.PHONY: all clean fclean re help libft mlx
