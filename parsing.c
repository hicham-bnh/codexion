/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:29:33 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/08 14:23:00 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_parsing(t_env *env)
{
	if ((env->params->number_of_coders < 1) || (
			env->params->number_of_coders > 2147483647))
		return (1);
	else if ((env->params->time_to_burnout < 1) || (
			env->params->time_to_burnout > 2147483647))
		return (1);
	else if ((env->params->time_to_compile < 1) || (
			env->params->time_to_compile > 2147483647))
		return (1);
	else if ((env->params->time_to_debug < 1) || (
			env->params->time_to_debug > 2147483647))
		return (1);
	else if ((env->params->time_to_refactor < 1) || (
			env->params->time_to_refactor > 2147483647))
		return (1);
	else if ((env->params->number_of_compiles_required < 1) || (
			env->params->number_of_compiles_required > 2147483647))
		return (1);
	else if ((env->params->dongle_cooldown < 1) || (
			env->params->dongle_cooldown > 2147483647))
		return (1);
	else if ((strcmp(env->params->scheduler, "fifo") != 0) && (
			strcmp(env->params->scheduler, "edf") != 0))
		return (1);
	return (0);
}

int	parsing_input(t_env *env, char **str)
{
	env->params->number_of_coders = atoi(str[1]);
	env->params->time_to_burnout = atoi(str[2]);
	env->params->time_to_compile = atoi(str[3]);
	env->params->time_to_debug = atoi(str[4]);
	env->params->time_to_refactor = atoi(str[5]);
	env->params->number_of_compiles_required = atoi(str[6]);
	env->params->dongle_cooldown = atoi(str[7]);
	env->params->scheduler = str[8];
	return (check_parsing(env));
}
