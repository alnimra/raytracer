/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_helper_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 20:33:57 by mray              #+#    #+#             */
/*   Updated: 2018/03/25 20:33:57 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	solve_for_roots(double coef[3])
{
	double disc;
	double roots[2];

	disc = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (disc > 0)
	{
		roots[0] = ((-coef[1] - sqrt(disc)) / (2 * coef[0])) - 0.000001;
		if (roots[0] > 0)
			return (roots[0]);
		roots[1] = ((-coef[1] + sqrt(disc)) / (2 * coef[0])) - 0.000001;
		return (roots[1] > 0) ? (roots[1]) : -1;
	}
	return (-1);
}

int		get_num_of_args(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	error_if_not(char **str, int i)
{
	if (get_num_of_args(str) != i)
		errorify("Not a Valid File");
}
