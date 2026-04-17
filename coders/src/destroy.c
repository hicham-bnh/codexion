/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 05:19:18 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/17 00:02:45 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	finish(t_env *env)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&env->write);
	pthread_mutex_destroy(&env->lock);
	pthread_mutex_destroy(&env->time_mutex);
	while (++i < env->pars.number_coders)
		pthread_mutex_destroy(&env->dongles[i].mutex);
	free(env->coders);
	free(env->dongles);
}
