/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:29:33 by mobenhab          #+#    #+#             */
/*   Updated: 2026/03/16 10:37:56 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void parsing_input(t_stock *test, char **str)
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
    printf("%d\n", test.number_of_coders);
    printf("%d\n", test.time_to_burnout);
    printf("%d\n", test.time_to_compile);
    printf("%d\n", test.time_to_debug);
    printf("%d\n", test.time_to_refactor);
    printf("%d\n", test.number_of_compiles_required);
    printf("%d\n", test.dongle_cooldown);
    printf("%s\n", test.scheduler);
}