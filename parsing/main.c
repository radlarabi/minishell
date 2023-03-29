/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/29 21:45:40 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void    error_msg()
{
    printf("syntax error near unexpected token `newline'\n");
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
	cmd->opr = N_OPER;
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
			return (0);
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
		tmp->type = D_DOTS;
		(*i) += 2;
	}
	else if (c == '.' && str[(*i) + 1] != '.')
	{
		tmp->len = 1;
		tmp->type = S_DOTS;
		(*i) += 2;
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
		tmp->len = 1;
		tmp->type = QEST;
		(*i)++;
	}
	else if (c == '$')
	{
		tmp->len = 1;
		tmp->type = ENV;
		(*i)++;
	}
	else
	{
		tmp->len = 1;
		tmp->type = OTHER;
		(*i)++;
	}
	return (1);
}

t_cmd_line	*fill_pipe(t_command **cmd, char *str)
{
	t_command	*tmp;
	char *str1 = NULL;
	t_cmd_line	*cmd_p;
	cmd_p = malloc(sizeof(t_cmd_line));
	if (!cmd_p)
		return NULL;
	cmd_p->infile = NULL;
	cmd_p->outfile = NULL;
	cmd_p->cmds = NULL;
	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp && tmp->type == WORD)
		{
			cmd_p->infile = NULL;
			cmd_p->outfile = NULL;
			while(tmp && (tmp->type == WORD || tmp->type == SPACE || tmp->type == SINGLE_Q || tmp->type == DOUBLE_Q || tmp->type == DASH))
			{
				str1 = ft_strjoin(str1, tmp->content);
				tmp = tmp->next;
			}
			cmd_p->cmds = ft_split(str1, ' ');
		}
		else if (tmp && tmp->type == RED_IN)
		{
			while (tmp != NULL && tmp->type != WORD)
				tmp = tmp->next;
			if (!tmp)
			{
				cmd_p->infile = NULL;
				break ;
			}
			if (tmp && tmp->type == WORD)
			{
				cmd_p->infile = ft_strdup(tmp->content);
				tmp = tmp->next;
			}
			else
				cmd_p->infile = NULL;
			skipe_spaces(&tmp);
			while(tmp && (tmp->type == WORD || tmp->type == SPACE || tmp->type == SINGLE_Q || tmp->type == DOUBLE_Q || tmp->type == DASH))
			{
				str1 = ft_strjoin(str1, tmp->content);
				tmp = tmp->next;
			}
			cmd_p->cmds = ft_split(str1, ' ');
			//printf("!!!!!!!%s\n", str1);
			// exit(0);
		}
		else if (tmp && tmp->type == RED_OUT)
		{
			while (tmp != NULL && tmp->type != WORD)
				tmp = tmp->next;
			if (!tmp)
			{
				cmd_p->outfile = NULL;
				break ;
			}
			if (tmp && tmp->type == WORD)
			{
				cmd_p->outfile = ft_strdup(tmp->content);
				tmp = tmp->next;
			}
			else
				cmd_p->outfile = NULL;
		}
		else
			tmp = tmp->next;
	}
	// if ((*cmd))
	// 	printf("in %s\tout %s\tcmd %s %s %s\n", cmd_p->infile, cmd_p->outfile, cmd_p->cmds[0], cmd_p->cmds[1],cmd_p->cmds[2]);
	return cmd_p;
}

void	command_or_pipe(t_command **cmd, char *str)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			printf("PIPE\n");
			fill_pipe(cmd, str);
			return ;
		}
		tmp = tmp->next;
	}
	printf("CMD\n");
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
	new->len = 1;
	new1 = init_cmd();
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
				error_msg();
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
			// while(tmp && tmp->type != DOUBLE_Q)
			// {
			// 	tmp->state = IN_DC;
			// 	tmp = tmp->prev;
			// }
			// tmp = tmp->next;
			// while (tmp != NULL && tmp->type != DOUBLE_Q)
			// {
			// }
		}
		else if (tmp->type == SINGLE_Q)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->type != SINGLE_Q)
			{
				tmp->state = IN_SC;
				tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
}

void check_syntax_error(t_command **cmd)
{
    t_command *tmp;

    tmp = *cmd;
    printf("%s------> %d\n", tmp->content, tmp->type);
    while(tmp && tmp->type == SPACE)
        tmp = tmp->next;
    while (tmp && tmp->type != WORD)
        tmp = tmp->next;
	if (!tmp)
	{
		error_msg();
		return ;
	}
    if (tmp->type == PIPE || tmp->type == RED_OUT)
    {
        error_msg();
        return ;
    }
    // while(tmp != NULL)
    // {
    //     tmp = tmp->next;
    // }
}

void	ft_pwd(t_command **cmd)
{
	t_command *tmp;

	tmp = *cmd;
	if (tmp && !ft_strncmp(tmp->content, "pwd", ft_strlen(tmp->content)))
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("Current working directory: %s\n", cwd);
		} else {
			perror("getcwd() error");
			return ;
		}
	}
}


void	check_syntax(t_command	**cmd)
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
			while(t1 && t1->opr != OPER && t1->type != WORD && t1->state == GENERAL)
				t1 = t1->next;
			while(t2 && t2->opr != OPER && t2->type != WORD && t1->state == GENERAL)
				t2 = t2->prev;
			if (t1 && tmp && (t1->type == HERDOC || t1->type == APPE || t1->type == RED_IN || t1->type == RED_OUT) && t1->opr == OPER && tmp->type == PIPE)
			{
				tmp = tmp->next;
				continue;
			}
			if ((t1 && t1->type == WORD && tmp && tmp->opr == OPER && tmp->state == GENERAL)
			|| (!t2 && t1 && tmp->opr == OPER && tmp->state == GENERAL))
			{
				printf("csacacasca\n");
				if ((!t2 || t1->opr == OPER) && t1->state == GENERAL)
				{
					ft_putendl_fd(ERROR_MSG,2);
					return ;
				}
				tmp = tmp->next;
				continue;
			}
			if (!t1 || !t2 || (t1->opr == OPER && t1->state == GENERAL) || (t2->opr == OPER && t2->state == GENERAL))
			{
				ft_putendl_fd(ERROR_MSG,2);
				return ;
			}
		}
		tmp = tmp->next;
	}
	t3 = *cmd;
	while(t3)
	{
		if (t3->type == OTHER && t3->state == GENERAL)
		{
			ft_putendl_fd(ERROR_MSG,2);
			return ;
		}	
		t3 = t3->next;
	}
}

void	check_syntax_rd(t_command	**cmd)
{
	t_command	*tmp;
	t_command	*t1;
	t_command	*t2;
	
	tmp = *cmd;
	while(tmp)
	{
		if (tmp && (tmp->type == RED_IN || tmp->type == HERDOC) && tmp->state != IN_DC && tmp->state != IN_SC)
		{
			t1 = tmp->next;
			// t2 = tmp->prev;
			while(t1 && t1->type != WORD && (t1->type != RED_IN && t1->type != HERDOC))
				t1 = t1->next;
			// while(t2 && t2->type != WORD && t2->type != RED_IN)
			// 	t2 = t2->prev;
			if (!t1 || t1->type != WORD)
			{
				ft_putendl_fd(ERROR_MSG,2);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
void	check_syntax_rd1(t_command	**cmd)
{
	t_command	*tmp;
	t_command	*t1;
	t_command	*t2;
	
	tmp = *cmd;
	while(tmp)
	{
		if (tmp && (tmp->type == RED_OUT || tmp->type == APPE) && tmp->state != IN_DC && tmp->state != IN_SC)
		{
			t1 = tmp->next;
			t2 = tmp->prev;
			while(t1 && t1->type != WORD && (t1->type != RED_OUT && t1->type != APPE))
				t1 = t1->next;
			while(t2 && t2->type != WORD && (t2->type != RED_OUT && t2->type != APPE))
				t2 = t2->prev;
			if (!t1 || !t2 || t1->type != WORD || t2->type != WORD)
			{
				ft_putendl_fd(ERROR_MSG,2);
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	display_pipe(t_cmd_line *cmd_l)
{
	int i = 0;
	printf("infile : %s\t outfile : %s\n", cmd_l->infile, cmd_l->outfile);
	while(cmd_l && cmd_l->cmds[i])
	{
		printf("cmds[%d] %s\n", i, cmd_l->cmds[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	int			i;
	int			len;
	t_command	*cmd;
	t_command	*node;
	t_command	*tmp;
	t_cmd_line *cmd_l;
	// t_pipes_cmds	*cmds_p;
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
		check_close_qotes(str);
		set_states(&cmd);
		check_syntax(&cmd);
		// check_syntax_rd(&cmd);
		// check_syntax_rd1(&cmd);
		// extend_cmd(&cmd);
		ft_pwd(&cmd);
		cmd_l = fill_pipe(&cmd, str);
		
		display_pipe(cmd_l);
		displayList(&cmd);
        free(str); 
	}
	return (0);
}
