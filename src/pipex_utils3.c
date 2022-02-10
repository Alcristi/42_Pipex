/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:04:40 by alcristi          #+#    #+#             */
/*   Updated: 2022/02/09 23:33:54 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_search_char(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_search_char(set, *s1))
	{
		s1++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_search_char(set, s1[i]))
	{
		i--;
	}
	str = ft_substr(s1, 0, i + 1);
	return (str);
}

void	replace_space(char *argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'')
		{
			j = ++i;
			while (argv[j] != '\'')
			{
				if (argv[j] == ' ')
					argv[j] = '`';
				i++;
				j++;
			}
		}
		i++;
	}
}

static char	*ft_trim(char *argv, int flag)
{
	char	*tmp;

	if (flag)
	{
		tmp = ft_strdup(argv);
		free(argv);
		argv = ft_strtrim(tmp, "\'");
		free(tmp);
		return (argv);
	}
	else
		return (argv);
}

char	*back_space(char *argv)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'')
		{
			j = ++i;
			while (argv[j] != '\'')
			{
				flag = 1;
				if (argv[j] == '`')
					argv[j] = ' ';
				i++;
				j++;
			}
		}
		i++;
	}
	return (ft_trim(argv, flag));
}
