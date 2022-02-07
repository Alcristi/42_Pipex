/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:58:08 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/06 23:07:48 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_abs(int p1, int p2)
{
	if ((p1 - p2) < 0)
		return (p2 - p1);
	return (p1 - p2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	if ((ft_strlen(s + 1) < start))
		len = 0;
	if ((ft_strlen(s) + 1) < len + 1)
		sub = (char *)malloc(ft_strlen(s) + 1);
	else if (len == ft_strlen(s))
		sub = (char *)malloc(ft_abs((int)len, (int)start) + 1);
	else
		sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while ((i < len) && (start + i) < size)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	if (n == 0)
		return (0);
	c = 0;
	while ((s1[c] == s2[c]) && (s1[c] != '\0') && (s2[c] != '\0')
		&& (c < n - 1))
		c++;
	return ((unsigned char)s1[c] - (unsigned char)s2[c]);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static size_t	count_letters(char const *s, char c)
{
	int	amount_of_letters;

	amount_of_letters = 0;
	while (s[amount_of_letters] != c && s[amount_of_letters])
		amount_of_letters++;
	return (amount_of_letters);
}

static size_t	count_words(char const *s, char c)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		total++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (total);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	c_words;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	c_words = count_words(s, c);
	list = malloc(sizeof(char *) * (c_words + 1));
	if (!list)
		return (0);
	while (i < c_words && *s)
	{
		if (*s != c)
		{
			list[i] = ft_substr(s, 0, count_letters(s, c));
			if (!list[i++])
				return (0);
			s += count_letters(s, c);
		}
		else
			s++;
	}
	list[c_words] = NULL;
	return (list);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	conc = (char *)malloc(len + 1);
	if (!conc)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		conc[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		conc[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	conc[len] = '\0';
	return (conc);
}

typedef struct s_pipex{
	int		id;
	int		fd_inline;
	int		fd_outline;
	int		fd[2];
	int		size_path;
	char	*path;
	char	**path_cmd;
	char	**args_cmd;
}t_pipex;

void	check_and_init_var(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->size_path = 0;
	if (argc != 5)
		exit(2);
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	pipex->path = ft_strdup(envp[i] + 5);
	pipex->path_cmd = ft_split(pipex->path, ':');
	while (pipex->path_cmd[pipex->size_path])
		pipex->size_path++;
}

void	check_and_init_cmd(char *argv[], t_pipex *pipex, int pos_arg)
{
	int		i;
	char	*tmp;

	i = 1;
	pipex->args_cmd = ft_split(argv[pos_arg], ' ');
	tmp = ft_strdup(pipex->args_cmd[0]);
	free(pipex->args_cmd[0]);
	pipex->args_cmd[0] = ft_strjoin("/", tmp);
	free (tmp);
	tmp = ft_strdup(pipex->args_cmd[0]);
	free(pipex->args_cmd[0]);
	pipex->args_cmd[0] = ft_strjoin(pipex->path_cmd[0], tmp);
	while (access(pipex->args_cmd[0], F_OK) && i < pipex->size_path)
	{
		free(pipex->args_cmd[0]);
		pipex->args_cmd[0] = ft_strjoin(pipex->path_cmd[i], tmp);
		i++;
	}
	free(tmp);
}

void	clean_memory(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	while (pipex->args_cmd[i])
		free(pipex->args_cmd[i++]);
	free(pipex->args_cmd);
	i = 0;
	while (pipex->path_cmd[i])
		free(pipex->path_cmd[i++]);
	free(pipex->path_cmd);
	free(pipex->path);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pp;

	check_and_init_var(argc, argv, envp, &pp);
	pipe(pp.fd);
	pp.id = fork();
	if (pp.id == 0)
	{
		pp.fd_inline = open(argv[1], O_RDONLY);
		dup2(pp.fd[1], 1);
		close(pp.fd[0]);
		dup2(pp.fd_inline, 0);
		close(pp.fd_inline);
		check_and_init_cmd(argv, &pp, 2);
		execve(pp.args_cmd[0], pp.args_cmd, envp);
		clean_memory(&pp);
		printf("error");
	}
	else
	{
		wait(NULL);
		pp.fd_outline = open(argv[argc - 1],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		dup2(pp.fd[0], 0);
		close(pp.fd[1]);
		dup2(pp.fd_outline, 1);
		close(pp.fd_outline);
		check_and_init_cmd(argv, &pp, 3);
		execve(pp.args_cmd[0], pp.args_cmd, envp);
		clean_memory(&pp);
	}
	return (0);
}
