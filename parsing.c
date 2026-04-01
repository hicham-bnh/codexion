/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:29:33 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/01 13:47:35 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_parsing(t_stock *test)
{
	if  (test->number_of_coders < 0)
    	return (1);
	else if	(test->time_to_burnout < 0)
	    return (1);
    else if	(test->time_to_compile < 0)
    	return (1);
    else if	(test->time_to_debug < 0)
        return (1);
    else if	(test->time_to_refactor < 0)
        return (1);
    else if	(test->number_of_compiles_required < 0)
        return (1);
    else if	(test->dongle_cooldown < 0)
        return (1);
    else if	(strcmp(test->scheduler, "fifo") != 0 && strcmp(test->scheduler, "edf") != 0)
        return (1);
    return (0);
}

void	parsing_input(t_stock *test, char **str)
{
    test->number_of_coders = atoi(str[1]);
    test->time_to_burnout = atoi(str[2]);
    test->time_to_compile = atoi(str[3]);
    test->time_to_debug = atoi(str[4]);
    test->time_to_refactor = atoi(str[5]);
    test->number_of_compiles_required = atoi(str[6]);
    test->dongle_cooldown = atoi(str[7]);
    test->scheduler = str[8];
}

int main(int ac, char **av)
{
    t_stock test;
    parsing_input(&test, av);
    if (check_parsing(&test))
    {
        printf("ERROR");
        return (0);
    }
    printf("%d\n", test.number_of_coders);
    printf("%d\n", test.time_to_burnout);
    printf("%d\n", test.time_to_compile);
    printf("%d\n", test.time_to_debug);
    printf("%d\n", test.time_to_refactor);
    printf("%d\n", test.number_of_compiles_required);
    printf("%d\n", test.dongle_cooldown);
    printf("%s\n", test.scheduler);
}
