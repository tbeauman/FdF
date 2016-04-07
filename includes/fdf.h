/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 13:41:23 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/08 14:40:26 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "fcntl.h"
# include "stdlib.h"
# include "math.h"
# include "string.h"
# define SIGN(x) x < 0 ? -1 : x == 0 ? 0 : 1
# define CAPPUCCINO x = e->ens->x; y = e->ens->y; z = e->ens->z * e->zfact

int					get_next_line(int fd, char **line);
int					ft_printf(const char *frm, ...);
void				exit_with_msg(char *msg);
typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				px;
	int				py;
	struct s_point	*next;
}					t_point;
typedef struct		s_eve
{
	void			*win;
	void			*mlx;
	void			*img;
	char			*img_address;
	int				length;
	int				width;
	int				max_h;
	int				min_h;
	t_point			*ens;
	double			p[2][3];
	int				d[3];
	double			t[3];
	int				c[3];
	int				persp;
	int				para;
	int				iso;
	double			omega;
	double			alpha;
	int				ec;
	int				x0;
	int				y0;
	float			zfact;
	int				bpp;
	int				sline;
	int				end;
}					t_eve;
int					mouse_button(int button, int x, int y, t_eve *e);
int					key_pressed(int keycode, t_eve *e);
void				init(t_eve *e, char *filename);
void				draw_line(t_point *p1, t_point *p2, t_eve *e);
void				draw_in_im(t_eve *e);
int					calc_px(int x, int y, t_eve *e);
int					calc_py(int x, int y, int z, t_eve *e);
t_point				*new_point(int x, int y, int z, t_eve *e);
void				add_point(t_point **pt, t_point *new);
int					ft_round(float x);
void				ft_putpixel(int x, int y, t_eve *e, int height);
void				init_matrice_proj(t_eve *e);
void				recalc_coords(t_eve *e);
void				recalc_persp_coords(t_eve *e);
void				clear_image(char **address);

void				debug(t_eve *e);
#endif
