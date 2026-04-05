/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:29:33 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/05 12:17:12 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void* compil(void* arg) {
    (void)arg;
    printf("is compiling");
    return NULL;
}

pthread_t *create_threads(t_stock *stock)
{
    pthread_t *threads = malloc(sizeof(pthread_t) * stock->number_of_coders);
    return (threads);
}

int	check_parsing(t_stock *stock)
{
	if  (stock->number_of_coders < 1)
    	return (1);
	else if	(stock->time_to_burnout < 1)
	    return (1);
    else if	(stock->time_to_compile < 1)
    	return (1);
    else if	(stock->time_to_debug < 1)
        return (1);
    else if	(stock->time_to_refactor < 1)
        return (1);
    else if	(stock->number_of_compiles_required < 1)
        return (1);
    else if	(stock->dongle_cooldown < 1)
        return (1);
    else if	(strcmp(stock->scheduler, "fifo") != 0 && strcmp(stock->scheduler, "edf") != 0)
        return (1);
    return (0);
}

void	parsing_input(t_stock *stock, char **str)
{
    stock->number_of_coders = atoi(str[1]);
    stock->time_to_burnout = atoi(str[2]);
    stock->time_to_compile = atoi(str[3]);
    stock->time_to_debug = atoi(str[4]);
    stock->time_to_refactor = atoi(str[5]);
    stock->number_of_compiles_required = atoi(str[6]);
    stock->dongle_cooldown = atoi(str[7]);
    stock->scheduler = str[8];
}

int main(int ac, char **av)
{
    if (ac != 9)
    {
        printf("ERROR");
        return (0);
    }
    t_stock stock;
    parsing_input(&stock, av);
    if (check_parsing(&stock))
    {
        printf("ERROR");
        return (0);
    }
    pthread_t *threads = create_threads(&stock);
    free(threads);
}

// valgrind --tools=helgrind ou --tools=drd
