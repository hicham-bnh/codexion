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

void parsing_input(t_stock t_stock, char **str)
{
    t_stock.number_of_coders = atoi(str[1]);
    
}