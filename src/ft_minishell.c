/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:31:09 by dmonjas-          #+#    #+#             */
/*   Updated: 2024/04/02 16:11:35 by rofuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_cpy_no_env(t_minishell *shell)
{
	char	*pwd;

	shell->pwd = NULL;
	shell->env = malloc(sizeof(char *) * 4);
	pwd = getcwd(shell->pwd, 100);
	shell->env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	shell->env[1] = ft_strdup("SHLVL=1");
	shell->env[2] = ft_strdup("_=/usr/bin/env");
	shell->env[3] = NULL;
	shell->oldpwd = NULL;
	shell->pwd = ft_env(shell->env, "PWD=");
}

static void	ft_init_var(t_minishell *shell, char **env)
{
	shell->shlvl = 1;
	shell->infile = 0;
	shell->outfile = 0;
	shell->heredoc = 0;
	shell->last_error = 0;
	shell->cmd_line = NULL;
	shell->inf = NULL;
	shell->here = NULL;
	shell->del = NULL;
	if (!env[0])
		ft_cpy_no_env(shell);
	else
	{
		shell->env = ft_cpy_env(env);
		shell->path = ft_env(env, "PATH=");
		shell->pwd = ft_env(env, "PWD=");
		shell->oldpwd = ft_env(env, "OLDPWD=");
		shell->root = ft_env(env, "HOME=");
	}
	g_code_error = 0;
	ft_init_signal();
}

static void	ft_free_cmdline(t_minishell *shell, t_command **cmd)
{
	free(shell->cmd_line);
	if (shell->inf)
	{
		free(shell->inf);
		shell->inf = NULL;
	}
	if (shell->here)
	{
		free(shell->here);
		shell->here = NULL;
	}
	if (shell->del)
		shell->del = NULL;
	*cmd = NULL;
	return ;
}

static void	ft_sig_disable(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_int);
}

/* void ft_leaks(void)
{
	system("leaks -q minishell");
} */

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;
	t_command	*cmd;

	if (argc != 1 || argv[1])
		ft_error_arguments();
	ft_init_var(&shell, env);
	ft_signal_dis();
	cmd = NULL;
	while (1)
	{
		ft_sig_disable();
		if (!g_code_error)
			shell.cmd_line = readline(GREEN"Minishell  🤯 $ "RESET);
		else
			shell.cmd_line = readline(RED"Minishell  🤯 $ "RESET);
		if (!shell.cmd_line)
			ft_error_cmd();
		shell.last_error = g_code_error;
		g_code_error = 0;
		shell.cmd_line[ft_strlen(shell.cmd_line)] = '\0';
		add_history(shell.cmd_line);
		ft_check_line(cmd, &shell);
		ft_free_cmdline(&shell, &cmd);
	}
	return (0);
}
