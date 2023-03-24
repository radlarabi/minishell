/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:59:07 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/12 16:38:23 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cmd_line
{
	char	*infile;
	char	*outfile;
	int		num_cmds;
	int		num_pipes;
	char	**av;
	char	**ev;
	char	**cmds;
	char	**path;
}			t_cmd_line;

char		*get_command(char **path, char *cmd);
char		**get_path(char **ev);
int			check_command(char **path, char *cmd);
void		free_2d_table(char **t);
void		print_error(char *a);
void		cmd_not_found(char *cmd);
void		normal_init(int ac, char **av, t_cmd_line *cmd, char **ev);
t_cmd_line	*init_args(int ac, char **av, char **ev);
void		close_pipes(t_cmd_line *cmd, int **pipefd);
void		open_pipes(t_cmd_line *cmd, int **pipefd);
void		open_infile(t_cmd_line *cmd);
void		open_outfile(t_cmd_line *cmd);
void		in_pipe(t_cmd_line *cmd, int i, int **pipefd);
void		out_pipe(t_cmd_line *cmd, int i, int **pipefd);
void		pipex(t_cmd_line *cmd);
void		main_free(t_cmd_line *cmd);

#endif
