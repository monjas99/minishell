/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:18:39 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/02/26 17:54:01 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_built(char *cmd)
{
	if (ft_strnstr(cmd, "echo", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "echo"));
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "cd"));
	else if (ft_strnstr(cmd, "pwd", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "pwd"));
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "export"));
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "unset"));
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd))
		&& ft_strlen(cmd) > 0)
		return (ft_spr(ft_split(cmd, ' '), "env"));
	return ("exec");
}

char	*ft_take_com(char *command)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_take_size(command);
	i = -1;
	j = 0;
	while (command[++i])
	{
		if (command[i] == '>')
			break ;
		if (command[i] == '<')
		{
			i++;
			while (command[i] == ' ' && command[i + 1] == ' ')
				i++;
		}
		else
		{
			tmp[j] = command[i];
			j++;
		}
	}
	tmp[j] = '\0';
	return (free (command), tmp);
}

static int	ft_open(char *outfile, char *command, t_minishell *shell)
{
	int	fd;
	int	x;

	fd = 0;
	x = ft_count(command, '>');
	if (shell->outfile)
		close(shell->outfile);
	if (x == 1)
	{
		fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening outfile"), 0);
	}
	if (x == 2)
	{
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd > 0 && access(outfile, W_OK | R_OK) < 0)
			return (ft_err_msg("Error opening append"), 0);
	}
	if (fd < 0)
		return (ft_err_msg("No such file or directory"), 0);
	return (fd);
}

int	ft_count(char *cmd, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		if (cmd[i] == c)
			count++;
	}
	return (count);
}

t_command	*ft_inout(t_command **cmd, t_minishell *shell)
{
	t_command	*aux;

	aux = *cmd;
	while (aux)
	{
		if (ft_strchr(aux->command, '<') && aux->dollar == 0)
		{
			if (aux->next->next->command[0] == '<')
				aux = ft_del_node(aux);
			shell->inf = ft_strdup(aux->next->command);
			shell->infile = ft_inf(aux->next->command, aux->command, shell);
			*cmd = ft_del_node(aux);
			aux = *cmd;
		}
		if (aux->next && (ft_strchr(aux->next->command, '>') && aux->next->dollar == 0))
		{
			//shell->out = ft_cp_out(aux->next);
			shell->outfile = ft_open(aux->next->next->command, aux->next->command, shell);
			aux->next = NULL;
			break ;
		}
		aux = aux->next; 
	}
	*cmd = ft_join(cmd);
	return(*cmd);
}
