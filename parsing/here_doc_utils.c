/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:05:57 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/22 14:33:36 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_stop_heredoc(char *str)
{
	int		i;
	char	**a;
	char	*temp;

	i = 0;
	a = splite_with_space(str);
	free(str);
	temp = remove_quotes(a[0]);
	free_2d_table(a);
	return (temp);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_gv->exit_status = 1;
	}
}

void	init_main_sig(int ac, char **av, char **env)
{
	fill_env_global_var(ac, av, env);
	change_value(&g_gv->env, "OLDPWD", NULL);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
