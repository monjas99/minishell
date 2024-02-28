/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:50:00 by rofuente          #+#    #+#             */
/*   Updated: 2024/02/28 15:11:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*ft_out_chech(t_command *cmd)
{
	if (ft_strchr(cmd->command, '>'))
		cmd = cmd->next;
	if (ft_strchr(cmd->command, '>'))
		cmd = cmd->next;
	if (cmd->next != NULL)
		return (cmd->next);	
	return (NULL);
}

/* static char	*ft_sjoin(char *s1, char *s2)
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
} */



/* char	*ft_take_size(char *cmd)
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
} */
