/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/04/04 16:09:07 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void    error_msg()
{
    printf(ERROR_MSG"\n");
}
t_command	*init_cmd()
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->content = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->type = 0;
	cmd->opr = 0;
	cmd->len = 0;
	cmd->state = 0;
	return (cmd);
}

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
	{
		*lst = new;
	}
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
	{
		*lst = new;
	}
	else
	{
		temp->next = new;
	}
}
void	displayList(t_command **node)
{
	while ((*node) != NULL)
	{
		printf("%s -> %d -> %d\n", (*node)->content, (*node)->type,
				(*node)->state);
		(*node) = (*node)->next;
	}
	printf("\n");
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
		{
			printf("errot quotes\n");
			return (0);
		}
	}
	return (1);
}

int	check_close_qotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!sub_check_qotes(str, &i, 39) || !sub_check_qotes(str, &i, 34))
		{
			return (0);
			// exit(258);
		}
		i++;
	}
	return (1);
}
void	skipe_spaces(t_command **tmp)
{
	while((*tmp) && (*tmp)->type == SPACE)
        (*tmp) = (*tmp)->next;
}
int	fill_types(t_command *tmp, char c, int *i, char *str)
{
	if (c == '-')
	{
		tmp->len = 1;
		tmp->type = DASH;
		tmp->opr = N_OPER;
		(*i)++;
	}
	else if (ft_isalnum(c))
	{
		while (ft_isalnum(str[*i]))
		{
			tmp->len++;
			(*i)++;
		}
		tmp->type = WORD;
	}
	else if (c == ' ')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = SPACE;
		(*i)++;
	}
	else if (c == '\"')
	{
		tmp->len = 1;
		tmp->type = DOUBLE_Q;
		(*i)++;
	}
	else if (c == '\'')
	{
		tmp->len = 1;
		tmp->type = SINGLE_Q;
		(*i)++;
	}
	else if (c == '<' && str[(*i) + 1] != '<')
	{
		tmp->opr = OPER;
		tmp->len = 1;
		tmp->type = RED_IN;
		(*i)++;
	}
	else if (c == '>' && str[(*i) + 1] != '>')
	{
		tmp->len = 1;
		tmp->opr = OPER;
		(*i)++;
		tmp->type = RED_OUT;
	}
	else if (c == '>' && str[(*i) + 1] == '>')
	{
		tmp->opr = OPER;
		tmp->len = 2;
		tmp->type = APPE;
		(*i) += 2;
	}
	else if (c == '<' && str[(*i) + 1] == '<')
	{
		tmp->opr = OPER;
		tmp->len = 2;
		tmp->type = HERDOC;
		(*i) += 2;
	}
	else if (c == '.' && str[(*i) + 1] == '.')
	{
		tmp->len = 2;
		tmp->opr = N_OPER;
		tmp->type = WORD;
		(*i) += 2;
	}
	else if (c == '.' && str[(*i) + 1] != '.')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = WORD;
		(*i) += 1;
	}
	else if (c == '|')
	{
		tmp->opr = OPER;
		tmp->len = 1;
		tmp->type = PIPE;
		(*i)++;
	}
	else if (c == '?')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = QEST;
		(*i)++;
	}
	else if (c == '$')
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = ENV;
		(*i)++;
	}
	else
	{
		tmp->opr = N_OPER;
		tmp->len = 1;
		tmp->type = OTHER;
		(*i)++;
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

void	ft_lstadd_middle(t_command **cmd)
{
	t_command	*new;
	t_command	*new1;

	new = init_cmd();
	new->content = " ";
	new->type = SPACE;
	new->state = GENERAL;
	new->len = 1;
	new1 = init_cmd();
	new1->state = GENERAL;
	new1->content = " ";
	new1->type = SPACE;
	new1->len = 1;
	new->next = (*cmd)->next;
	new->prev = (*cmd);
	(*cmd)->next = new;
	/*hada code dyal espace befor node*/
	if ((*cmd)->prev != NULL)
	{
		new1->prev = (*cmd)->prev;
		new1->next = (*cmd);
		(*cmd)->prev->next = new1;
		(*cmd)->prev = new1;
	}
	else
	{
		new1->prev = NULL;
		new1->next = (*cmd);
		(*cmd)->prev = new1;
	}
	/*end*/
}


void	set_states(t_command **cmd)
{
	t_command	*tmp;
	int count = 0;
	tmp = *cmd;

	while (tmp != NULL)
	{
		tmp->state = GENERAL;
		if (tmp->type == DOUBLE_Q)
		{
			tmp = tmp->next;
			while(tmp && tmp->type != DOUBLE_Q)
			{
				count++;
				tmp = tmp->next;
			}
			if (!tmp)
			{
				return;
			}
			while(count)
			{
				tmp = tmp->prev;
				count--;
			}
			while(tmp && tmp->type != DOUBLE_Q)
			{
				tmp->state = IN_DC;
				tmp = tmp->next;
			}
				tmp->state = GENERAL;
				tmp = tmp->next;
		}
		else if (tmp->type == SINGLE_Q)
		{
			tmp = tmp->next;
			while(tmp && tmp->type != SINGLE_Q)
			{
				count++;
				tmp = tmp->next;
			}
			if (!tmp)
			{
				return;
			}
			while(count)
			{
				tmp = tmp->prev;
				count--;
			}
			while(tmp && tmp->type != SINGLE_Q)
			{
				tmp->state = IN_SC;
				tmp = tmp->next;
			}
				tmp->state = GENERAL;
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}


void	ft_pwd(t_command **cmd)
{
	t_command *tmp;

	tmp = *cmd;
	if (tmp && !ft_strncmp(tmp->content, "pwd", 3))
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("%s\n", cwd);
		} else {
			perror("getcwd() error");
			return ;
		}
	}
}

int	sub_check_syntax_error(t_command **cmd)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->state == GENERAL && (!ft_strncmp(tmp->content, "&&", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, "*", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, ";", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, ")", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, "(", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, "&", ft_strlen(tmp->content))
		|| !ft_strncmp(tmp->content, "\\", ft_strlen(tmp->content))))
		{
			error_msg();
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}

int	check_syntax(t_command	**cmd)
{
	t_command	*tmp;
	t_command	*t1;
	t_command	*t2;
	t_command	*t3;

	tmp = *cmd;
	while(tmp)
	{
		if (tmp && tmp->opr == OPER && tmp->state == GENERAL)
		{
			t1 = tmp->next;
			t2 = tmp->prev;
			while(t1 && t1->opr != OPER  && t1->type != WORD  && t1->type != DOUBLE_Q && t1->type != SINGLE_Q && t1->state == GENERAL && t1->type != OTHER)
				t1 = t1->next;
			while(t2 && t2->opr != OPER  && t2->type != WORD && t2->type != DOUBLE_Q && t2->type != SINGLE_Q && t2->state == GENERAL && t2->type != OTHER)
				t2 = t2->prev;
			if(!t1 || !t2)
			{
				if (!t1 || (!t2 && tmp && tmp->type == PIPE && tmp->state == GENERAL))
				{
					if (!t2 && tmp && tmp->opr == OPER && tmp->state == GENERAL && tmp->type != OTHER && tmp->type != DOUBLE_Q)
					{
						printf("t1 n 1");
						error_msg();
						return 0;
					}
					if (!t1 && tmp && tmp->opr == OPER && tmp->state == GENERAL)
					{
						printf("t1 n 2");
						error_msg();
						return 0;
					}

					if (!t1 && tmp->type != HERDOC && tmp->type != RED_IN && tmp->type != RED_OUT && tmp->type != APPE && tmp->type != ENV)
					{
						printf("t1 n 3");
						error_msg();
						return 0;
					}
				}
			}
			else
			{
				if (t1->opr == OPER)
				{
					if (t1->type == PIPE && t1->state == GENERAL)
					{
						printf("%s  --> t1 ", t1->content);
						error_msg();
						return 0;
					}
				}
				if(t2->opr == OPER)
				{
					if ((t2->type == PIPE && tmp && tmp->type == PIPE && t2->state == GENERAL)
						|| (t2->type != PIPE && tmp && tmp->type != PIPE && t2->state == GENERAL)
						|| (tmp && tmp->type == PIPE))
					{
						printf("%s  --> t2 ", t2->content);
						error_msg();
						return 0;
					}
				}
			}
		}
		tmp = tmp->next;
	}
	if (!sub_check_syntax_error(cmd))
		return 0;
	return 1;
}


void	display_pipe(t_cmd_line *cmd_l)
{
	// int i = 0;
	// while(cmd_l && cmd_l->cmds[i])
	// {
	// 	printf("cmds[%d] %s\n", i, cmd_l->cmds[i]);
	// 	i++;
	// }
}
int 	count_pipes(t_command **cmd)
{
	t_command *tmp;
	int count;

	count = 0;
	tmp = *cmd;
	while(tmp)
	{
		if (tmp->type == PIPE && tmp->state == GENERAL)
			count++;
		tmp = tmp->next;
	}
	return count;
}

t_cmd_line *lst_init_cmds()
{
	t_cmd_line *cmd_l = malloc(sizeof(t_cmd_line));
	cmd_l->infile = NULL;
	cmd_l->outfile = NULL;
	cmd_l->next = NULL;
	cmd_l->cmds = NULL;
	return cmd_l;
}
void	extend_cmd(t_command **cmd)
{
	t_command	*tmp;
	t_command	*node;
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

void	skip_and_fill_in_quotes(char *str, char **s, int a, int *i)
{
	(*s)[*i] = str[*i];
	(*i)++;
	while (str[*i])
	{
		(*s)[*i] = str[*i];
		if (str[*i] == a)
			break ;
		(*i)++;
	}
}

void	skip_in_quotes(char *str, int a, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == a)
			break ;
		(*i)++;
	}
}
char *join_char(char *str, char c)
{
	char *a;
	if (!str)
	{
		a = malloc(sizeof(char) * 2);
		if (!a)
			return NULL;
		a[0] = c;
		a[1] = '\0';
		return a;
	}
	int i = 0;
	a = malloc(ft_strlen(str) + 2);
	while(str[i])
	{
		a[i] = str[i];
		i++;
	}
	a[i] = c;
	i++;
	a[i] = '\0';
	printf("--------------> %s\n", a);
	return a;
}
char *change_quote_in_files(char *str)
{
	int i = 0;
	char *a = NULL;
	if (!str)
		return NULL;
	while(str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while(str[i] && str[i] != '\"')
			{
				a = join_char(a, str[i]);
				i++;
			}
			if (!str[i])
				break;
			if ('\"')
				i++;
			if (!str[i])
				break;
		}
		else if (str[i] == '\'')
		{
			i++;
			while(str[i] && str[i] != '\'')
			{
				a = join_char(a, str[i]);
				i++;
			}
			if (!str[i])
				break;
			if ('\'')
				i++;
			if (!str[i])
				break;
		}
		else
		{
			printf("-%s-\n",a);
			a = join_char(a, str[i]);
			i++;
		}
	}
	return a;
}

char *set_spliter(char *str, char c)
{
	char *s;
	int i;
	if (!str)
		return NULL;
	s = malloc(ft_strlen(str) + 1);
	i = 0;
	while(str[i])
	{
		if (str[i] == 39)
			skip_and_fill_in_quotes(str, &s, 39, &i);
		else if (str[i] == 34)
			skip_and_fill_in_quotes(str, &s, 34, &i);
		else if (str[i] == c)
			s[i] = -1;
		else
			s[i] = str[i];
		i++;
	}
	s[i] = 0;
	return s;
}

char **splite_with_pipes(t_command **cmd)
{
	t_command *tmp;

	tmp = *cmd;
	extend_cmd(&tmp);
	char *str = struct_to_str(&tmp);
	printf("_________^^^%s\n", str);
	return ft_split(set_spliter(str, '|'), -1);
}

char **splite_with_space(char *str)
{
	return ft_split(set_spliter(str, ' '), -1);
}

t_cmd_line * commands_struct(char **cmds)
{
	t_cmd_line *cmd_l = NULL;
	t_cmd_line *tmp;
	int i = 0;
	int j = 0;
	char *t1;
	char **temp;
	while (cmds[i])
	{
		temp = splite_with_space(cmds[i]);
		tmp = lst_init_cmds();
		j = 0;
		t1 = NULL;
		while(temp[j])
		{
			if (!ft_strncmp(temp[j], "<", ft_strlen(temp[j])))
			{
				if (!temp[++j])
					break;
				tmp->infile = change_quote_in_files(ft_strdup(temp[j]));
			}
			else if (!ft_strncmp(temp[j], ">", ft_strlen(temp[j])))
			{
				if (!temp[++j])
					break;
				tmp->outfile = change_quote_in_files(ft_strdup(temp[j]));
			}
			else
			{
				t1 = ft_strjoin(t1, temp[j]);
				t1 = ft_strjoin(t1, " ");
			}
			j++;
		}
		tmp->cmds = splite_with_space(t1);
		ft_lstadd_back_cmds(&cmd_l, tmp);
		i++;
	}
	i = 0;
	while(cmd_l)
	{
		j = 0;
		printf("---> %d infile %s +++ outfile %s +++ \n", i++, cmd_l->infile, cmd_l->outfile);
		while (cmd_l->cmds[j])
		{
			printf("cmd [%d] %s\n", j+1, cmd_l->cmds[j]);
			j++;
		}
		cmd_l = cmd_l->next;
	}
	return cmd_l;
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	int			i;
	pid_t id;
	int status;
	int			len;
	t_command	*cmd;
	t_command	*node;
	t_command	*tmp;
	t_cmd_line *cmd_l;
	while (1)
	{
		i = 0;
		str = readline("minishell -> ");
		add_history(str);
		while (str[i])
		{
			tmp = init_cmd();
			if (!fill_types(tmp, str[i], &i, str))
				return (0);
			tmp->content = ft_substr(str, i - tmp->len, tmp->len);
			ft_lstadd_back(&cmd, tmp);
		}
		if (!check_close_qotes(str))
		{
			cmd = NULL;
			continue ;
		}
		set_states(&cmd);
		if (!check_syntax(&cmd))
		{
			cmd = NULL;
			continue ;
		}
		ft_pwd(&cmd);

		// char **a = splite_with_pipes(str);
		cmd_l = commands_struct(splite_with_pipes(&cmd));
		// i = 0;
		// while(cmd_l->cmds[i])
		// {
		// 	printf("cmd[%d]--->%s\n", i, cmd_l->cmds[i]);
		// 	i++;
		// }
		displayList(&cmd);
		cmd = NULL;
        free(str);
	}
	return (0);
}

