/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:39:02 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/08 14:24:44 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

pthread_mutex_t *create_mutex(t_env *env)
{
	pthread_mutex_t *mutexs;

        mutexs = malloc(sizeof(pthread_mutex_t) * env->params->number_of_coders);
        if (!mutexs)
                return (NULL);
        return (mutexs);
}
