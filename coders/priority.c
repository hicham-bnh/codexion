/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 01:36:42 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/16 05:18:18 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	priotiy_dongle(t_env *env, int i)
{
	pthread_mutex_lock(&env->lock);
	if (ft_time(env->coders[i].last_compile) > ft_time(env->coders[(i + 1)
				% env->pars.number_coders].last_compile))
	{
		env->dongles[i].priority = env->coders[(i + 1)
			% env->pars.number_coders].id;
	}
	else
		env->dongles[i].priority = env->coders[i].id;
	pthread_mutex_unlock(&env->lock);
}

int	check_priority(t_env *env, int i)
{
	if (ft_time(env->coders[i].last_compile) > ft_time(env->coders[(i + 1)
				% env->pars.number_coders - 1].last_compile)
		&& (ft_time(env->coders[i].last_compile) > ft_time(env->coders[(i - 1)
					% env->pars.number_coders - 1].last_compile)))
	{
		return (1);
	}
	return (0);
}
