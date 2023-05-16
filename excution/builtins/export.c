/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:53:41 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/05/16 23:07:09 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_export(int flag1)
{
	t_env	*tmp;

	tmp = g_gv->env;
	while (tmp)
	{
		if (!tmp->value || (!ft_strcmp(tmp->value, "") && flag1 >= 1))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(tmp->var, 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
		}
		tmp = tmp->next;
	}
	g_gv->exit_status = 0;
}

void	export_one_var(char *value_of_var, int *flag1, int *flag)
{
	if (check_syntax_cmd(value_of_var))
	{
		ft_putstr_fd("export: ", 1);
		ft_putstr_fd(value_of_var, 1);
		ft_putendl_fd(" : not a valid identifier", 1);
		g_gv->exit_status = 1;
	}
	else if (!ft_cherch_node(value_of_var))
	{
		change_value(&g_gv->env, value_of_var, NULL);
		add_node(&g_gv->env, value_of_var, NULL, 1);
		*(flag1) += 1;
	}
	*flag = 1;
}

void	export_utils4(char *value_of_var, int i, int *flag, int *flag1)
{
	if (!(*flag) && value_of_var[0] == '=' && check_syntax_cmd(value_of_var))
		export_utils1(value_of_var, flag);
	else if (!(*flag) && value_of_var[i] == '=' && value_of_var[i - 1] != '+')
		export_utils2(value_of_var, i, flag, flag1);
	else if (!(*flag) && value_of_var[i] == '+' && value_of_var[i + 1] == '=')
		export_utils3(value_of_var, i, flag, flag1);
	else if (!(*flag) && (!ft_strchr(value_of_var, '=')
			&& !ft_strchr(value_of_var, '+')))
		export_one_var(value_of_var, flag1, flag);
}

int	*ft_len_tab(char **tab, int *len)
{
	static int	flag1;

	while (tab && tab[*len])
		(*len)++;
	return (&flag1);
}

int	ft_export(t_cmd_line **commands_v)
{
	char	*value_of_var;
	int		len;
	size_t	i;
	int		j;
	int		flag;

	len = 0;
	j = 1;
	ft_len_tab((*commands_v)->cmds, &len);
	while (j <= len)
	{
		i = 0;
		flag = 0;
		value_of_var = (*commands_v)->cmds[j];
		while (value_of_var && i < ft_strlen(value_of_var))
		{
			export_utils4(value_of_var, i, &flag,
				ft_len_tab((*commands_v)->cmds, &len));
			// system("leaks minishell");
			i++;
		}
		if (!(*commands_v)->cmds[j] && len == 1)
			display_export(*(ft_len_tab((*commands_v)->cmds, &len)));
		j++;
	}
	return (0);
}
