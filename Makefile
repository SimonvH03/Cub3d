NAME	=	cub3d

CC		=	cc
CFLAGS	=	-O3
CFLAGS	+=	-Wall -Werror -Wextra
#CFLAGS	+=	-g
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	./MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS =	./cub3d.h \
			./defs.h \
			./paths.h \

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/initialise/draw_game_images.c \
			$(SRCDIR)/initialise/draw_menu_images.c \
			$(SRCDIR)/initialise/init_game_images.c \
			$(SRCDIR)/initialise/init_game_structs.c \
			$(SRCDIR)/initialise/init_menu_images.c \
			$(SRCDIR)/initialise/init_menu_structs.c \
			$(SRCDIR)/initialise/read_cub_elements.c \
			$(SRCDIR)/initialise/read_map_init_camera.c \
			$(SRCDIR)/user_interface/arrowkey_turn.c \
			$(SRCDIR)/user_interface/keyhooks.c \
			$(SRCDIR)/user_interface/up_down_select.c \
			$(SRCDIR)/user_interface/view_manager.c \
			$(SRCDIR)/user_interface/wasd_move.c \
			$(SRCDIR)/user_interface/door_system.c \
			$(SRCDIR)/user_interface/health_bar.c \
			$(SRCDIR)/user_interface/ammo_display.c \
			$(SRCDIR)/frame_process/arithmetic.c \
			$(SRCDIR)/frame_process/draw_map_player.c \
			$(SRCDIR)/frame_process/draw_minimap_walls.c \
			$(SRCDIR)/frame_process/ray_init.c \
			$(SRCDIR)/frame_process/ray_collision.c \
			$(SRCDIR)/frame_process/texture_column_init.c \
			$(SRCDIR)/frame_process/texture_column_draw.c \
			$(SRCDIR)/frame_process/weapon_init.c \
			$(SRCDIR)/frame_process/weapon_animation.c \
			$(SRCDIR)/frame_process/weapon_draw.c \
			$(SRCDIR)/frame_process/modlx.c \
			#$(SRCDIR)/test.c

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< -I MLX42/include

$(NAME): $(LIBMLX) $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)
	rm -f $(LIBFT)
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all clean fclean re