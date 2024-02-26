/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/02/26 17:07:16 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_sjoin(char *s1, char *s2)
{
	char	*r;
	int		x;
	int		y;

	r = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)) + 2);
	if (!r)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		r[x++] = s1[y++];
	r[x] = ' ';
	x++;
	y = 0;
	while (s2[y])
		r[x++] = s2[y++];
	r[x] = '\0';
	return (r);
}

char	*ft_swap(char *cmd, char *inf)
{
	char	**tmp;
	char	*command;
	int		i;

	i = 1;
	tmp = ft_split(cmd, ' ');
	if (open(inf, O_RDONLY, 0644) < 0)
	{
		free (tmp);
		return ("ERROR INF");
	}
	command = ft_strjoin(tmp[0], " ");
	command = ft_strjoin(command, inf);
	while (tmp[i])
	{
		command = ft_strjoin(command, tmp[i]);
		i++;
	}
	ft_free_mtx(tmp);
	return (command);
}

char	*ft_take_size(char *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '>')
			break ;
		if (cmd[i] == '<')
		{
			i++;
			while (cmd[i] == ' ')
				i++;
			i--;
		}
		else
			j++;
	}
	tmp = ft_calloc((j + 1), sizeof(char));
	return (tmp);
}
