/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MSI <MSI@student.42.fr>                    +#+  +:+       +#+        */
/*                                                    +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 22:38:09 by MSI               #+#    #+#             */
/*   Updated: 2026/04/07 22:38:09 by MSI              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long       ft_get_time()
{
        struct timeval  tv;
        if (gettimeofday(&tv, NULL))
                return (0);
        return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void    ft_sleep(long long time, t_env *env)
{
        long long       start;
        
        start = ft_get_time();
        while ((ft_get_time() - start) < time)
        {
                pthread_mutex_lock(&env->status_lock);
                if (env->stop)
                {
                        pthread_mutex_unlock(&env->status_lock);
                        break;
                }
                pthread_mutex_unlock(&env->status_lock);
                usleep(500);
        }
}

void    init_env(t_env *env)
{
        
}