/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:22:09 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 04:46:47 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_env(t_env *env)
{
	int	i;

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
		env->dongles[i].free = 0;
		env->dongles[i].last_use = env->pars.dongle_cooldown * 2;
		if (pthread_mutex_init(&env->dongles[i].mutex, NULL))
			return (1);
		i++;
	}
	env->start = get_time();
	env->stop = 0;
	env->thread_finish = 0;
	return (0);
}

int	init_mutex_env(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->pars.number_coders)
	{
		if (pthread_mutex_init(&env->coders[i].lock_doc, NULL))
				return (1);
	}
	if (pthread_mutex_init(&env->lock, NULL))
		return (1);
	if (pthread_mutex_init(&env->write, NULL))
		return (1);
	return (0);
}
