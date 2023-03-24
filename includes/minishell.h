/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:11:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/24 01:56:20 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
typedef struct s_cmd
{
    char *content;
	int	type;
	int len;
    struct s_cmd *next;
	struct s_cmd *prev;
}   t_command;

typedef struct s_cmd_line
{
	char	*infile;
	char	*outfile;
	int		num_cmds;
	int		num_pipes;
	char	*cmd;
}			t_cmd_line;

#endif