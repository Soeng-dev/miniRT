/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:48:22 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "../utils/math/myvector.h"

struct	s_light
{
	t_vector	pos;
	t_vector	color;
	double		bright;
};
typedef struct s_light	t_light;
struct	s_lightdata
{
	t_light		*light_arr;
	t_vector	ambient;
	int			count;
};
typedef struct s_lightdata	t_lightdata;

#endif
