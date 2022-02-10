/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:58:08 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/09 23:39:48 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	check_and_init_var(int argc, char *envp[], t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->size_path = 0;
	if (argc != 5)
	{
		write(2, "Quantidade de argumentos inválidos\n", 37);
		exit(EXIT_FAILURE);
	}
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	pipex->path = ft_strdup(envp[i] + 5);
	pipex->path_cmd = ft_split(pipex->path, ':');
	while (pipex->path_cmd[pipex->size_path])
		pipex->size_path++;
}

static void	check_and_init_cmd(char *argv[], t_pipex *pipex, int pos_arg)
{
	int		i;
	char	*tmp;

	i = 0;
	replace_space(argv[pos_arg]);
	pipex->args_cmd = ft_split(argv[pos_arg], ' ');
	pipex->cmd = ft_strdup(pipex->args_cmd[0]);
	while (pipex->args_cmd[i])
	{
		pipex->args_cmd[i] = back_space(pipex->args_cmd[i]);
		i++;
	}
	tmp = ft_strjoin("/", pipex->args_cmd[0]);
	free(pipex->args_cmd[0]);
	pipex->args_cmd[0] = ft_strjoin(pipex->path_cmd[0], tmp);
	while (access(pipex->args_cmd[0], F_OK) && i < pipex->size_path)
	{
		free(pipex->args_cmd[0]);
		pipex->args_cmd[0] = ft_strjoin(pipex->path_cmd[i], tmp);
		i++;
	}
	if (access(pipex->args_cmd[0], F_OK))
		error_cmd(pipex, ": comando não encontrado");
	free(tmp);
}

static void	child(t_pipex *pp, char *argv[], char *envp[])
{
	dup2(pp->fd[1], 1);
	close(pp->fd[0]);
	dup2(pp->fd_inline, 0);
	close(pp->fd_inline);
	check_and_init_cmd(argv, pp, 2);
	execve(pp->args_cmd[0], pp->args_cmd, envp);
	clean_memory(pp);
	exit(EXITNOTCMD);
}

static void	parent(t_pipex *pp, char *argv[], char *envp[])
{
	dup2(pp->fd[0], 0);
	close(pp->fd[1]);
	dup2(pp->fd_outline, 1);
	close(pp->fd_outline);
	check_and_init_cmd(argv, pp, 3);
	execve(pp->args_cmd[0], pp->args_cmd, envp);
	clean_memory(pp);
	exit(EXITNOTCMD);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pp;

	check_and_init_var(argc, envp, &pp);
	pipe(pp.fd);
	pp.id = fork();
	if (pp.id == 0)
	{
		pp.fd_inline = open(argv[1], O_RDONLY);
		if (pp.fd_inline < 0)
			error_file(&pp, "bash: ", argv[1]);
		child(&pp, argv, envp);
	}
	else
	{
		pp.fd_outline = open(argv[argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pp.fd_outline < 0)
			error_file(&pp, "bash: ", argv[argc - 1]);
		parent(&pp, argv, envp);
	}
	return (0);
}
