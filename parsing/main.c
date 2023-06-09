/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/06/01 16:31:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_t_command_struct(t_command **cmd, char *str)
{
	t_command	*tmp;
	int			i;

	tmp = NULL;
	if (ft_strlen(str) != 0)
		add_history(str);
	i = 0;
	while (str && str[i])
	{
		tmp = init_cmd(tmp);
		fill_types(tmp, str[i], &i, str);
		tmp->content = ft_substr(str, i - tmp->len, tmp->len);
		ft_lstadd_back(cmd, tmp);
	}
}

char	**env_is_null(void)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 4);
	if (!tab)
		return (NULL);
	tab[0] = ft_strjoin(NULL, "PWD=/Users/rlarabi/Desktop/minishell");
	tab[1] = ft_strjoin(NULL, "SHLVL=1");
	tab[2] = ft_strjoin(NULL, "_=/usr/bin/env");
	tab[3] = 0;
	return (tab);
}

void	fill_env_global_var(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	g_gv = malloc(sizeof(t_gv));
	if (!g_gv)
		return ;
	while (env[i])
		i++;
	if (i)
	{
		g_gv->env = get_env(env);
		g_gv->exit_status = 0;
	}
	else if (!i)
	{
		g_gv->env = get_env_1(env);
		g_gv->exit_status = 0;
	}
}

int	main_check_syntax(char *str, t_command **cmd)
{
	if (!check_close_qotes(str))
	{
		free_t_command(cmd);
		if (str)
			free(str);
		return (1);
	}
	set_states(cmd);
	if (!check_syntax(cmd))
	{
		free_t_command(cmd);
		if (str)
			free(str);
		return (1);
	}
	if (max_herdoc(cmd))
	{
		g_gv->exit_status = 2;
		printf("maximum here-document count exceeded\n");
		free_t_command(cmd);
		exit(2);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_command	*cmd;
	t_cmd_line	*cmd_l;
	char		**temp;

	init_main_sig(ac, av, env);
	while (1)
	{
		cmd = NULL;
		cmd_l = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		str = readline("MINISHELL -> ");
		signal(SIGINT, SIG_IGN);
		exit_cntrl_d(str);
		fill_t_command_struct(&cmd, str);
		if (main_check_syntax(str, &cmd))
			continue ;
		temp = splite_with_pipes(&cmd);
		cmd_l = commands_struct(temp);
		pipex(cmd_l);
		main_free(&cmd, &cmd_l, temp, str);
	}
	return (0);
}
