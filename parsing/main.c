/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/25 16:58:25 by rlarabi          ###   ########.fr       */
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
        printf("%s -> %d\n", (*node)->content, (*node)->type);
        (*node) = (*node)->next;
    }
    printf("\n");
}

void    check_close_qotes(char *str, char *string_perfect)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while(str[i])
    {
        if (str[i] == string_perfect[j])
                j++;
        i++;
        if (j == 2)
            j = 0;
        
    }
    if (j)
        printf("Error syntaxe\n");
}
void    set_state(t_command **cmd)
{
    int i = 0;
    int close_dc = 0;
    int close_sc = 0;
    t_command *tmp;
    int count = 0;
    tmp = *cmd;
    while(tmp != NULL)
    {
        i = 0;
        while(tmp->content[i])
        {
            tmp->state = 1;
            if (tmp->content[i] == '\"')
            {
                while(tmp->content[i] != '\"');
            }
            i++;
        }
        tmp = tmp->next;
    }
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

int main(int ac, char **av, char **env)
{
    char *str;
    int i;
    int len;
    t_command *cmd;
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
        check_close_qotes(str, "\"\"");
        check_close_qotes(str, "\'\'");
        // set_state(&cmd);
        displayList(&cmd);
        free(str);
    }
    return 0;
}
