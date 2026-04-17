/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 01:36:42 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/17 00:01:39 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	priotiy_dongle(t_env *env, int i)
{
	pthread_mutex_lock(&env->time_mutex);
	if (ft_time(env->coders[i].last_compile) > ft_time(env->coders[(i + 1)
				% env->pars.number_coders].last_compile))
	{
		env->dongles[i].priority = env->coders[(i + 1)
			% env->pars.number_coders].id;
	}
	else
		env->dongles[i].priority = env->coders[i].id;
	pthread_mutex_unlock(&env->time_mutex);
}

int	check_priority(t_env *env, int i)
{
	pthread_mutex_lock(&env->time_mutex);
	if (ft_time(env->coders[i].last_compile) < ft_time(env->coders[(i + 1)
				% env->pars.number_coders].last_compile)
		&& (ft_time(env->coders[i].last_compile) > ft_time(env->coders[(i + 1)
					% env->pars.number_coders].last_compile)))
	{
		pthread_mutex_unlock(&env->time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&env->time_mutex);
	return (0);
}
