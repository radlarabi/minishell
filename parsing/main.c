/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/13 22:47:35 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
		*lst = new;
	else
	{
		temp->next = new;
		new->prev = temp;
	}
}

void	ft_lstadd_back_cmds(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

int	sub_check_qotes(char *str, int *i, int a)
{
	int	j;

	j = 0;
	if (str[*i] == a)
	{
		(*i)++;
		while (str[*i])
		{
			if (str[*i] == a)
			{
				j = 1;
				break ;
			}
			(*i)++;
		}
		if (j == 0)
			return (0);
	}
	return (1);
}

int	check_close_qotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!sub_check_qotes(str, &i, 39) || !sub_check_qotes(str, &i, 34))
		{
			error_msg();
			return (0);
		}
		i++;
	}
	return (1);
}

char	*struct_to_str(t_command **cmd)
{
	t_command	*tmp;
	char		*str;

	tmp = *cmd;
	str = NULL;
	while (tmp != NULL)
	{
		str = ft_strjoin(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

t_command	*init_lst_in_middle(void)
{
	t_command	*new;

	new = NULL;
	new = init_cmd(new);
	new->content = ft_strdup(" ");
	new->type = SPACE;
	new->state = GENERAL;
	new->len = 1;
	return (new);
}

void	ft_lstadd_middle(t_command **cmd)
{
	t_command	*new;
	t_command	*new1;

	new = init_lst_in_middle();
	new1 = init_lst_in_middle();
	new->next = (*cmd)->next;
	new->prev = (*cmd);
	(*cmd)->next = new;
	if ((*cmd)->prev != NULL)
	{
		new1->prev = (*cmd)->prev;
		new1->next = (*cmd);
		(*cmd)->prev->next = new1;
		(*cmd)->prev = new1;
	}
	else
	{
		free(new1->content);
		free(new1);
	}
}

void	extend_cmd(t_command **cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp->state == GENERAL && (tmp->type == RED_IN
				|| tmp->type == RED_OUT || tmp->type == PIPE
				|| tmp->type == HERDOC || tmp->type == APPE))
		{
			ft_lstadd_middle(&tmp);
		}
		tmp = tmp->next;
		i++;
	}
}

char	*ft_getenv(char *str)
{
	t_env	*temp;

	temp = g_gv->env;
	while (temp)
	{
		if (!ft_strcmp(str, temp->var))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	is_quots(char *str, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i] && i != index)
	{
		if (!open && str[i] == '\"')
			open = 2;
		else if (open == 2 && str[i] == '\"')
			open = 0;
		if (!open && str[i] == '\'')
			open = 3;
		else if (open == 3 && str[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

char	*search_path(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], "PATH", 4))
			return (ev[i]);
		i++;
	}
	return (NULL);
}

void	free_2d_table(char **temp)
{
	int	i;

	i = 0;
	while (temp && temp[i])
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	if (temp)
		free(temp);
}

void	free_t_command(t_command **cmd)
{
	t_command	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->content)
			free((*cmd)->content);
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	free_t_cmd_line(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->fd_error)
			free((*cmd)->fd_error);
		if ((*cmd)->cmds)
			free_2d_table((*cmd)->cmds);
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	fill_t_command_struct(t_command **cmd, char *str)
{
	t_command	*tmp;
	int			i;

	tmp = NULL;
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

void	main_free(t_command **cmd, t_cmd_line **cmd_l, char **temp, char *str)
{
	free(temp);
	free_t_command(cmd);
	free_t_cmd_line(cmd_l);
	if (str)
		free(str);
}

char	**env_is_null(void)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 4);
	tab[0] = ft_strjoin(NULL, "PWD=/Users/hlakhal-/Desktop/minishell");
	tab[1] = ft_strjoin(NULL, "SHLVL=1");
	tab[2] = ft_strjoin(NULL, "_=/usr/bin/env");
	tab[3] = 0;
	return (tab);
}

t_env	*get_env_1(char **env)
{
	t_env	*tmp;
	int		i;
	t_env	*env_var;

	i = 0;
	env_var = NULL;
	env = env_is_null();
	while (env[i])
	{
		tmp = init_env();
		tmp = fill_env_node(env[i], tmp);
		ft_add_back_env(&env_var, tmp);
		i++;
	}
	return (env_var);
}

void	fill_env_global_var(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	g_gv = malloc(sizeof(t_gv));
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
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	t_command	*cmd;
	t_cmd_line	*cmd_l;
	char		**temp;

	fill_env_global_var(ac, av, env);
	change_value(&g_gv->env, "OLDPWD",NULL);
	while (1)
	{
		cmd = NULL;
		cmd_l = NULL;
		str = readline("MINISHELL -> ");
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
