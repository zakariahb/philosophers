/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:43:40 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/14 12:48:34 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_for_double_operators(int *cmd_type)
{
	int		i;

	i = 0;
	while (cmd_type[i])
	{
		if (cmd_type[i] == PIPE && cmd_type[i + 1] == PIPE)
		{
			ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
			return (false);
		}
		i++;
	}
	return (true);
}
