/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:22:09 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/09 22:18:33 by mobenhab         ###   ########.fr       */
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
		if (pthread_mutex_init(&env->dongles[i].mutex, NULL))
			return (1);
		if (pthread_cond_init(&env->dongles->cond, NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&env->lock, NULL);
	env->start = get_time();
	return (0);
}
