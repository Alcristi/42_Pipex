/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:21:24 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/09 23:37:37 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_cmd(t_pipex *pp, char *msg)
{
	msg = ft_strjoin(pp->cmd, msg);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	free(pp->cmd);
	clean_memory(pp);
	exit(EXITNOTCMD);
}

void	error_file(t_pipex *pp, char *msg, char *file)
{
	int		i;
	char	*tmp;

	i = 0;
	close(pp->fd[0]);
	close(pp->fd[1]);
	while (pp->path_cmd[i])
		free(pp->path_cmd[i++]);
	free(pp->path_cmd);
	free(pp->path);
	tmp = ft_strjoin(msg, file);
	if (!access(file, F_OK))
		msg = ft_strjoin(tmp, ": Permissão negada");
	else
		msg = ft_strjoin(tmp, ": Arquivo ou diretório inexistente");
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	free(tmp);
	exit(EXIT_FAILURE);
}
