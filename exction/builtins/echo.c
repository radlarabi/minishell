/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:53:34 by hlakhal-          #+#    #+#             */
/*   Updated: 2023/03/27 00:09:42 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char *str_line(t_command **command__line)
// {
// 	char *command;
// 	command =  NULL;
// 	while ((*command__line)->next)
// 	{
// 		//command = ft_strjoin(command,(*command__line)->content);
// 		printf("%s\n",(*command__line)->content);
// 		(*command__line) = (*command__line)->next;
// 	}
// 	return command;
// }

// int	ft_echo(t_command *echo_1)
// {
// 	int			i;
// 	int			flag;
// 	t_command	*temp;
// 	char *words;

// 	flag = 0;
// 	i = 0;
// 	temp = echo_1;
// 	str_line(&temp);
// 	//printf("%s",str_line(&temp));
// 	// if (temp->next->type && temp->next->type == SPACE)
// 	// {
// 	// 	// exit(0);
// 	// 	temp = temp->next;
// 	// 	words = temp->next->next->content;

// 	// 	printf("%s",words);
// 	// 	if (!words)
// 	// 	{
// 	// 		printf("%s",temp->next->next->content);
// 	// 		if (temp->next->type == WORD)
// 	// 		{
// 	// 		while (temp->next->content[i])
// 	// 		{
// 	// 			printf("%c", temp->next->content[i]);
// 	// 			i++;
// 	// 		}
// 	// 		}
// 	// 	}
// 	// 	if (!ft_strncmp(ft_strjoin(temp->next->content,words),"-n",7))
// 	// 		flag = 1;

// 	// 	if (!flag)
// 	// 		printf("\n");
// 	// }
// 	return (0);
// }
