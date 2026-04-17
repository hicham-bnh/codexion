/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:09:28 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/16 22:53:17 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_pars(t_env *env)
{
	if (1 > env->pars.number_coders || env->pars.number_coders > 2100000000)
		return (1);
	if (1 > env->pars.to_burnout)
		return (2);
	if (1 > env->pars.to_compile)
		return (3);
	if (1 > env->pars.to_refactor)
		return (4);
	if (1 > env->pars.to_debug)
		return (5);
	if ((1 > env->pars.compiles_required)
		|| (env->pars.compiles_required > 2147483647))
		return (6);
	if (1 > env->pars.dongle_cooldown)
		return (7);
	if (!env->pars.shceduler)
		return (8);
	if ((strcmp(env->pars.shceduler, "fifo"))
		&& (strcmp(env->pars.shceduler, "edf")))
		return (8);
	if (!(strcmp(env->pars.shceduler, "edf")))
		env->edf = 1;
	return (0);
}

static int	check_digit(char **arg)
{
	if (ft_isdigit(arg[1]))
		return (1);
	if (ft_isdigit(arg[2]))
		return (1);
	if (ft_isdigit(arg[3]))
		return (1);
	if (ft_isdigit(arg[4]))
		return (1);
	if (ft_isdigit(arg[5]))
		return (1);
	if (ft_isdigit(arg[6]))
		return (1);
	if (ft_isdigit(arg[7]))
		return (1);
	return (0);
}

int	pars_input(t_env *env, char **arg)
{
	env->pars.number_coders = atoi(arg[1]);
	env->pars.to_burnout = atoi(arg[2]);
	env->pars.to_compile = atoi(arg[3]);
	env->pars.to_debug = atoi(arg[4]);
	env->pars.to_refactor = atoi(arg[5]);
	env->pars.compiles_required = atoi(arg[6]);
	env->pars.dongle_cooldown = atoi(arg[7]);
	env->pars.shceduler = arg[8];
	if (check_pars(env) || check_digit(arg))
	{
		return (1);
	}
	return (0);
}
