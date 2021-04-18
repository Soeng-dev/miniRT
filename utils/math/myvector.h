/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myvector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYVECTOR_H
# define MYVECTOR_H
# define TRUE	1
# define FALSE	0
# include <math.h>
# include <stdio.h>
# include "math_tools.h"

struct			s_vector
{
	double		x;
	double		y;
	double		z;
};
typedef struct s_vector	t_vector;
/*
**		vector
*/
void			init_vector(t_vector *v, double x, double y, double z);
t_vector		get_vector(double x, double y, double z);
int				vector_is_same(t_vector v1, t_vector v2);
int				is_valid_vector(t_vector v, double min, double max);
/*
** 		vector calculation
*/
t_vector		add(t_vector v1, t_vector v2);
t_vector		minus(t_vector v1, t_vector v2);
t_vector		power(t_vector v, double n);
t_vector		multi(t_vector v, double n);
t_vector		divide(t_vector v, double n);
/*
** 		vector operation
*/
t_vector		normalize(t_vector v);
double			dot(t_vector v1, t_vector v2);
t_vector		cross(t_vector v1, t_vector v2);
t_vector		rotate_vector(t_vector target, t_vector axis, double angle);
/*
** 		vector tools
*/
double			sum_of_elements(t_vector v1);
double			distance(t_vector v1, t_vector v2);
t_vector		multi_corresponds(t_vector v1, t_vector v2);
t_vector		vec_clamp(t_vector v, double min, double max);
void			prt_vector(char *pre, t_vector target, char *post);
#endif
