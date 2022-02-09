/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 23:26:17 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/07 14:20:28 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		id;
	int		fd_inline;
	int		fd_outline;
	int		fd[2];
	int		size_path;
	int		wstatus;
	char	*path;
	char	**path_cmd;
	char	**args_cmd;
}			t_pipex;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
void	error(t_pipex *pp);
void	clean_memory(t_pipex *pipex);
void	error_file(t_pipex *pp);

#endif