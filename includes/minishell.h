/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:11:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/25 16:08:07 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

# define WORD 1
# define DASH 2
# define SPACE 3
# define DOUBLE_Q 4
# define SINGLE_Q 5
# define RED_IN 6
# define RED_OUT 7
# define HERDOC 8
# define APPE 9
# define PIPE 10
# define ENV 11

typedef struct s_cmd
{
    char *content;
	int	type;
	int state;
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