/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristi <alcristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:56:10 by alcristi          #+#    #+#             */
/*   Updated: 2021/12/14 11:22:56 by alcristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
