/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:09:28 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 20:11:03 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_pars(t_env *env)
{
	if (2 > env->pars.number_coders || env->pars.number_coders > 2147483647)
		return (1);
	if (0 > env->pars.to_burnout)
		return (1);
	if (0 > env->pars.to_compile)
		return (1);
	if (0 > env->pars.to_refactor)
		return (1);
	if (0 > env->pars.to_debug)
		return (1);
	if ((0 > env->pars.compiles_required)
		|| (env->pars.compiles_required > 2147483647))
		return (1);
	if (0 > env->pars.dongle_cooldown)
		return (1);
	if (!env->pars.shceduler)
		return (1);
	if ((strcmp(env->pars.shceduler, "fifo"))
		&& (strcmp(env->pars.shceduler, "edf")))
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
	if (check_pars(env))
	{
		return (1);
	}
	return (0);
}
