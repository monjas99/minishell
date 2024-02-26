/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:46:02 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/26 17:47:00 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_del_node(t_command *aux)
{
	t_command	*cmd;

	cmd = aux;
	if (aux->next->next)
		cmd = aux->next->next;
	else
		cmd = NULL;
	if (aux)
	{
		free (aux->next->command);
		free(aux->next);
		aux->next = NULL;
		free (aux->command);
		free(aux);
	}
	return (cmd);
}
static void	ft_lstclear_shell(t_command **lst)
{
	t_command	*aux;
	t_command	*aux_next;

	aux = *lst;
	while (aux)
	{
		aux_next = aux->next;
		free(aux);
		aux = aux_next;
	}
	*lst = NULL;
}

char	*ft_cp_out(t_command *aux)
{
	char		*out;
	t_command	*aux2;

	aux2 = aux;
	aux = aux->next;
	while (aux)
	{
		out = ft_strjoin(out, aux->command);
		aux = aux->next;
	}
	ft_lstclear_shell(&aux2);
	return (out);
}