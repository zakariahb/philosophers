/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouis-j <alouis-j@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:09:08 by alouis-j          #+#    #+#             */
/*   Updated: 2023/02/12 16:09:22 by alouis-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <dirent.h>

bool	check_dir(char *cmd)
{
	DIR	*dirp;

	if (!cmd)
		return (false);
	dirp = opendir(cmd);
	if (dirp)
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", cmd);
		g_exit_status = 126;
		closedir(dirp);
		return (true);
	}
	return (false);
}
