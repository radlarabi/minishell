/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/26 18:30:59 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_command *init_cmd()
{
    t_command *cmd;
    cmd = malloc(sizeof (t_command));
    if (!cmd)
        return NULL;
    cmd->content = NULL;
    cmd->next = NULL;
    cmd->prev = NULL;
    cmd->type = 0;
    cmd->len = 0;
    cmd->state = 0;
    return cmd;
}

void    ft_lstadd_back(t_command **lst,t_command *new)
{
    t_command *temp;

    if(!(*lst))
    {
        *lst = new;
        return ;
    }
    temp = *lst;
    while(temp->next != NULL)
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
void displayList(t_command **node)
{
    while ((*node) != NULL) {
        printf("%s -> %d -> %d\n", (*node)->content, (*node)->type, (*node)->state);
        (*node) = (*node)->next;
    }
    printf("\n");
}

int    sub_check_qotes(char *str, int *i, int a)
{
    int j;

    j = 0;
    if (str[*i] == a)
    {
        (*i)++;
        while(str[*i])
        {
            if(str[*i] == a)
            {
                j = 1;
                break;
            }
            (*i)++;
        }
        if(j == 0)
        {
            printf("errot quotes\n");
            return 0;
        }
    }
    return 1;
}

int    check_close_qotes(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (!sub_check_qotes(str, &i, 39) || !sub_check_qotes(str, &i, 34))
            return 0;
        i++;
    }
    return 1;
}

int    fill_types(t_command *tmp, char c, int *i, char *str)
{
    if (c == '-')
    {
        tmp->len = 1;
        tmp->type = DASH;
        (*i)++;
    }
    else if (ft_isalpha(c))
    {
        while (ft_isalpha(str[*i]))
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
        tmp->len = 1;
        tmp->type = RED_IN;
        (*i)++;
    }
    else if (c == '>' && str[(*i) + 1] != '>')
    {
        tmp->len = 1;
        tmp->type = RED_OUT;
        (*i)++;
    }
    else if (c == '>' && str[(*i) + 1] == '>')
    {
        tmp->len = 2;
        tmp->type = APPE;
        (*i) += 2;
    }
    else if (c == '<' && str[(*i) + 1] == '<')
    {
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
        tmp->len = 1;
        tmp->type = PIPE;
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
        printf("error token");
        return 0;
    }
    return 1;
}

void    fill_pipe(t_command **cmd, char *str)
{
    t_command    *tmp;
    t_cmd_line  *cmd_p;
    cmd_p = malloc(sizeof(cmd_p));
    int i;
    tmp = *cmd;
    while(tmp != NULL)
    {
        i = 0;
        if (tmp->type == RED_IN)
        {
            while(tmp != NULL && tmp->type != WORD)
                tmp = tmp->next;
            if (!tmp)
                return ;
            if (tmp->type == WORD)
                cmd_p->infile = ft_strdup(tmp->content);
        }
        if (tmp->type == RED_OUT)
        {
            while(tmp != NULL && tmp->type != WORD)
                tmp = tmp->next;
            if (!tmp)
            {
                cmd_p->outfile = NULL;
                return ;
            }
            if (tmp->type == WORD)
                cmd_p->outfile = ft_strdup(tmp->content);
        }
        tmp = tmp->next;
    }
    printf("in %s\tout %s\n", cmd_p->infile, cmd_p->outfile);
}

void    command_or_pipe(t_command **cmd, char *str)
{
    t_command    *tmp;

    tmp = *cmd;
    while(tmp != NULL)
    {
        if(tmp->type == PIPE)
        {
            printf("PIPE\n");
            fill_pipe(cmd, str);
            return ;
        }
        tmp = tmp->next;
    }
    printf("CMD\n");
}

char *struct_to_str(t_command **cmd)
{
    t_command    *tmp;
    char *str;

    tmp = *cmd;
    str = NULL;
    while(tmp != NULL)
    {
        str = ft_strjoin(str, tmp->content);
        tmp = tmp->next;
    }
    return str;
}

void    ft_lstadd_middle(t_command **cmd)
{
    t_command *new;
    t_command *new1;

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

    new1->prev = (*cmd)->prev;
    new1->next = (*cmd);
    (*cmd)->prev->next = new1;
}
void    extend_cmd(t_command **cmd)
{
    t_command *tmp;
    t_command *node;
    int i = 0;
    tmp = *cmd;
    while(tmp != NULL)
    {
        if (tmp->state == GENERAL 
            && (tmp->type == RED_IN || tmp->type == RED_OUT
                || tmp->type == PIPE || tmp->type == HERDOC
                || tmp->type == APPE))
        {
            ft_lstadd_middle(&tmp);
        }
        tmp = tmp->next;
        i++;
    }
}
void    set_states(t_command **cmd)
{
    t_command *tmp;

    tmp = *cmd;
    while(tmp != NULL)
    {
        tmp->state = GENERAL;
        if (tmp->type == DOUBLE_Q)
        {
            tmp = tmp->next;
            while(tmp != NULL && tmp->type != DOUBLE_Q)
            {
                tmp->state = IN_DC;
                tmp = tmp->next;
            }
        }
        else if (tmp->type == SINGLE_Q)
        {
            tmp = tmp->next;
            while(tmp != NULL && tmp->type != SINGLE_Q)
            {
                tmp->state = IN_SC;
                tmp = tmp->next;
            }
        }
        else
            tmp = tmp->next;
    }
}
int main(int ac, char **av, char **env)
{
    char *str;
    int i;
    int len;
    t_command *cmd;
    t_command *node;
    t_command *tmp;

    while(1)
    {
        i = 0;
        str = readline("minishell -> ");
        add_history(str);
        while(str[i])
        {
            tmp = init_cmd();
            if (!fill_types(tmp, str[i], &i,str))
                return 0;
            tmp->content = ft_substr(str, i - tmp->len, tmp->len);
            ft_lstadd_back(&cmd, tmp);
        }
        printf("--->%s\n", struct_to_str(&cmd));
        check_close_qotes(str);
        command_or_pipe(&cmd, str);
        set_states(&cmd);
        extend_cmd(&cmd);
        free(str);
        displayList(&cmd);
    }
    return 0;
}
