/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlarabi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:35:27 by rlarabi           #+#    #+#             */
/*   Updated: 2023/02/14 18:09:31 by rlarabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr("command not found: ");
	ft_putstr(cmd);
	ft_putstr("\n");
	exit(1);
}

void	normal_init(int ac, char **av, t_cmd_line *cmd, char **ev)
{
	int	i;

	i = 0;
	cmd->num_cmds = ac - 3;
	cmd->num_pipes = ac - 4;
	cmd->av = av;
	cmd->ev = ev;
	cmd->cmds = malloc(sizeof(char *) * (cmd->num_cmds + 1));
	if (!cmd->cmds)
		exit(1);
	while (i < cmd->num_cmds)
	{
		cmd->cmds[i] = ft_strdup(av[2 + i]);
		i++;
	}
	cmd->cmds[i] = NULL;
	cmd->infile = ft_strdup(av[1]);
	cmd->outfile = ft_strdup(av[ac - 1]);
	cmd->path = get_path(ev);
}

t_cmd_line	*init_args(int ac, char **av, char **ev)
{
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	if (!cmd)
		return (NULL);
	normal_init(ac, av, cmd, ev);
	return (cmd);
}

void	main_free(t_cmd_line *cmd)
{
	free_2d_table(cmd->path);
	free_2d_table(cmd->cmds);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd);
}

int	main(int ac, char **av, char **ev)
{
	t_cmd_line	*cmd;

	if (ac < 5)
	{
		write(2, "Error Args\n", 11);
		write(2, "how it works : ", 15);
		write(2, "./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n", 48);
		exit(1);
	}
	cmd = init_args(ac, av, ev);
	pipex(cmd);
	main_free(cmd);
	return (0);
}
