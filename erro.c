/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:21:24 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/07 14:21:54 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_pipex *pp)
{
	clean_memory(pp);
	exit(EXIT_FAILURE);
}

void	error_file(t_pipex *pp)
{
	int	i;

	i = 0;
	close(pp->fd[0]);
	close(pp->fd[1]);
	while (pp->path_cmd[i])
		free(pp->path_cmd[i++]);
	free(pp->path_cmd);
	free(pp->path);
	exit(EXIT_FAILURE);
}
