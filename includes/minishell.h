/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:11:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/03/29 21:50:47 by hlakhal-         ###   ########.fr       */
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
# define S_DOTS 12
# define D_DOTS 13
# define OPER 14
# define N_OPER 15
# define QEST 16
# define OTHER 17
#define ERROR_MSG "\033[0;31m syntax error \033[0m"

#define GENERAL 1
#define IN_DC 2
#define IN_SC 3
typedef struct s_cmd
{
    char *content;
	int	type;
	int state;
	int opr;
	int len;
    struct s_cmd *next;
    struct s_cmd *prev;
}   t_command;

typedef struct s_cmd_line
{
	char	*infile;
	char	*outfile;
	char	**cmds;
}			t_cmd_line;

/*  fonction builtins  */
void	commands(t_cmd_line **commands_v,t_command **cmd);
int	ft_echo(t_cmd_line **commands_v,t_command **cmd);
/* end */

#endif
