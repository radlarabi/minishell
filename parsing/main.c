/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:00:22 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/24 01:55:01 by rlarabi          ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
    char *str;
    int i;
    int len;
    t_command *cmd;
    t_command *tmp;
    cmd = init_cmd();
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
            tmp->content = ft_substr(str, i - tmp->len, tmp->len);
            printf("%s   -> %d -> %d\n", tmp->content, i , tmp->len);
            ft_lstadd_back(&cmd, tmp);
            // exit(0);
            // free(tmp);
            // i++;
        }
        free(str);
    }
    return 0;
}
