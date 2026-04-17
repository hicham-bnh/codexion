/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:22:09 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/16 23:55:00 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_params(t_env *env)
{
	env->stop = 0;
	env->thread_finish = 0;
	env->write_stop = 0;
}

int	init_env(t_env *env)
{
	int	i;

	init_params(env);
	env->coders = malloc(sizeof(t_coders) * env->pars.number_coders);
	if (!env->coders)
		return (1);
	env->dongles = malloc(sizeof(t_dongles) * env->pars.number_coders);
	if (!env->dongles)
	{
		free(env->coders);
		return (1);
	}
	i = 0;
	while (i < env->pars.number_coders)
	{
		env->coders[i].id = i + 1;
		env->coders[i].last_compile = get_time();
		env->dongles[i].free = 0;
		env->dongles[i].last_use = 0;
		env->dongles[i].priority = 0;
		if (pthread_mutex_init(&env->dongles[i].mutex, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_mutex_env(t_env *env)
{
	if (pthread_mutex_init(&env->lock, NULL))
		return (1);
	if (pthread_mutex_init(&env->write, NULL))
		return (1);
	if (pthread_mutex_init(&env->time_mutex, NULL))
		return (1);
	return (0);
}
