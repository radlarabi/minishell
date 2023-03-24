/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/24 17:41:35 by rlarabi          ###   ########.fr       */
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
// void    set_type_token(t_command *tmp, char *str,int *i)
// {
//     if (str[*i] == '-')
//     {
//         tmp->len = 1;
//         tmp->type = 2;
//         *i++;
//     }
// }
void displayList(t_command *node)
{
    while (node != NULL) {
        printf("%s -> %d\n", node->content, node->state);
        node = node->next;
    }
    printf("\n");
}

void    check_close_qotes(t_command **cmd)
{
    t_command *tmp;
    int start_dc = 0;
    int start_sc = 0;
    int i;


    i = 0;
    tmp = *cmd;
    while(tmp != NULL)
    {
        i = 0;
        while(tmp->content[i])
        {
            if (tmp->content[i] == '\"')
                start_dc++;
            if (tmp->content[i] == '\'')
                start_sc++;
            i++;
        }
        tmp = tmp->next;
    }
    if (start_dc % 2 || start_sc % 2)
    {
        printf("Error qotes %d %d\n", start_dc, start_sc);
        exit(0);
    } 
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
            tmp->state = 2;
            if (tmp->content[i] == '\"')
            {
                tmp->state = 3;
                tmp = tmp->next;
                count++;
                close_dc = 1;
                if (count == 2)
                {
                    close_dc = 0;
                    count = 0;
                }
                if (close_dc == 1)
                    tmp->state = 1;
            }
            else if (tmp->content[i] == '\'')
            {
                // tmp->state = 4;
                // tmp = tmp->next;
                // count++;
                // close_dc = 1;
                // if (count == 2)
                // {
                //     close_dc = 0;
                //     count = 0;
                // }
                // if (close_dc == 1)
                //     tmp->state = 1;
            }
            i++;
        }
        tmp = tmp->next;
    }
}

int main(int ac, char **av, char **env)
{
    char *str;
    int i;
    int len;
    t_command *cmd;
    t_command *tmp;
    // cmd = init_cmd();
    while(1)
    {
        i = 0;
        str = readline("minishell -> ");
        add_history(str);
        while(str[i])
        {
            tmp = init_cmd();
            if (str[i] == '-')
            {
                tmp->len = 1;
                tmp->type = 2;
                i++;
            }
            else if (ft_isalpha(str[i]))
            {
                while (ft_isalpha(str[i]))
                {
                    tmp->len++;
                    i++;
                }
                tmp->type = 1;
            }
            else if (str[i] == ' ')
            {
                tmp->len = 1;
                tmp->type = 3;
                i++;
            }
            else if (str[i] == '\"')
            {
                tmp->len = 1;
                tmp->type = 4;
                i++;
            }
            else if (str[i] == '\'')
            {
                tmp->len = 1;
                tmp->type = 5;
                i++;
            }
            else if (str[i] == '<' && str[i + 1] != '<')
            {
                tmp->len = 1;
                tmp->type = 6;
                i++;
            }
            else if (str[i] == '>' && str[i + 1] != '>')
            {
                tmp->len = 1;
                tmp->type = 7;
                i++;
            }
            else if (str[i] == '>' && str[i + 1] == '>')
            {
                tmp->len = 2;
                tmp->type = 8;
                i += 2;
            }
            else if (str[i] == '<' && str[i + 1] == '<')
            {
                tmp->len = 2;
                tmp->type = 9;
                i += 2;
            }
            else if (str[i] == '|')
            {
                tmp->len = 1;
                tmp->type = 10;
                i++;
            }
            else if (str[i] == '$')
            {
                tmp->len = 1;
                tmp->type = 11;
                i++;
            }
            else
            {
                printf("error token");
                return 0;
            }
            tmp->content = ft_substr(str, i - tmp->len, tmp->len);
            ft_lstadd_back(&cmd, tmp);
            // printf("%s   -> %d -> %d -> %d\n", tmp->content, i - tmp->len , tmp->len);
        }
        check_close_qotes(&cmd);
        set_state(&cmd);
        displayList(cmd);
        free(str);
    }
    return 0;
}
