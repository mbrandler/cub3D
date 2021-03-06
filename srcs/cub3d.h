#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../minilibx_opengl/mlx.h"
# define SCALE 16
# define ENTER 36
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define L 123
# define R 124
# define UP 126
# define DOWN 125

typedef struct s_params
{
	int			settings;
	int			width;
	int			height;
	int			t;
	int			r;
	int			g;
	int			b;
	int			floor_color;
	int			ceilling_color;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_texture;
	int			fd;
	char		**map;
	int			map_height;
	int			map_width;
	int			map_start;
	int			plr_found;
	double		wall_height;
	int			dir_h;
	int			dir_v;
	double		*dist_to_wall;
	double		hit_x;
	double		hit_y;
	int			sprites;
	int			screen_height;
	int			screen_width;
	int			key_w;
	int			key_up;
	int			key_down;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_l;
	int			key_r;
}				t_params;

typedef struct s_sprites
{
	double		x;
	double		y;
	double		dist;
	double		dir;
	double		sprite_size;
	double		offset_x;
	double		offset_y;
}				t_sprites;

typedef struct s_image
{
	int			texture_width;
	int			texture_height;
	void		*texture_img;
	int			*texture_addr;
	int			texture_bpp;
	int			texture_line_length;
	int			texture_endian;
	char		*texture_path;
}				t_image;

typedef struct s_player
{
	double		x;
	double		y;
	double		direction;
}				t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_search_cross
{
	double	new_x;
	double	new_y;
	int		delta_x;
	int		delta_y;
	double	dist_h;
	double	dist_v;
}				t_search_cross;

typedef struct s_all
{
	t_params		*params;
	t_data			*data;
	t_player		*plr;
	t_sprites		**spr;
	t_image			text[5];
}				t_all;

void	buff_textures(t_all *all);
void	cast_rays(t_all *all, int i);
void	check_first_last_lines(t_all *all, int i);
void	check_map(t_all *all);
void	check_player(t_all *all, char *line);
void	check_screen_size(t_all *all);
int		create_bmp(t_all *all);
int		create_trgb(int r, int g, int b);
void	define_color(char *line, t_all *all);
void	define_resolution(char *line, t_all *all);
void	define_textures(char *line, t_all *all);
void	dist_to_sprite(t_all *all, int num);
void	draw(t_all *all, int x, int side);
void	draw_map(t_all *all);
void	draw_sprite(t_all *all, int num);
void	draw_sprites(t_all *all);
void	draw_wall(t_all *all, int x, int y, int side);
void	error_close(t_all *all, int i);
int		exit_cub(t_all *all);
void	ft_cast_rays(t_all *all, int x);
void	init_player(t_all *all);
void	init_sprites(t_all *all);
void	key_events(t_all *all);
int		key_press(int key, t_all *all);
int		key_release(int key, t_all *all);
void	params_init(t_params *params);
void	parser(char *line, t_all *all);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	read_map(char *argv1, t_all *all);
void	scale_map(t_data *data, int x, int y, int color);
void	free_array(char **array);
int		pixel_take(t_all *all, int x, int y, int side);
void	sprite_dir(t_all *all, int num);
void	sprites_init(t_all *all);

#endif