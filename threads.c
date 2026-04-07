/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:33:27 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/07 19:36:23 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//void* routine()
//{
//	// la routine des threads compile debug et factor
//        // lock le mutex au debut et le unlock a la fin
//        return (NULL);
//}



pthread_t       *create_threads(t_pars *stock, void *func)
{
	pthread_t	*threads;
        int     i;
        
        i = 0;
	threads = malloc(sizeof(pthread_t) * stock->number_of_coders);
	if (!threads)
		return (NULL);
        while (i < stock->number_of_coders)
        {
                if (pthread_create(&threads[i], NULL, &func, NULL))
                        return (NULL);
                if (pthread_join(threads[i], NULL))
                        return (NULL);
        }
	return (threads);
}
