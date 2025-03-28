/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:17:12 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/10 09:53:53 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_env(t_env *env, char **args)
{
	if (ft_array_size(args) > 1)
	{
		ft_dprintf(2, "env: ‘%s‘: No such file or directory\n", args[1]);
		g_exit_status = 127;
		return ;
	}
	(void)args;
	while (env != NULL)
	{
		if (env->var_value)
			ft_dprintf(1, "%s=%s\n", env->var_name, env->var_value);
		env = env->next;
	}
	g_exit_status = 0;
}
