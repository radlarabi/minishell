/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:11:37 by rlarabi           #+#    #+#             */
/*   Updated: 2023/05/16 00:27:54 by hlakhal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>

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
# define AND 17
# define ERROR_MSG "\033[0;31m syntax error \033[0m"
# define MINISHELL "minishell -> "

# define GENERAL 1
# define IN_DC 2
# define IN_SC 3

typedef struct s_env
{
	char				*value;
	char				*var;
	int					flag;
	struct s_env		*next;
}						t_env;

typedef struct s_gv
{
	t_env				*env;
	int					exit_status;
}						t_gv;

t_gv					*g_gv;

typedef struct s_cmd
{
	char				*content;
	int					type;
	int					state;
	int					opr;
	int					len;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_command;

typedef struct s_cmd_line
{
	int					infile;
	int					outfile;
	int					flag;
	int					index;
	char				*fd_error;
	char				**cmds;
	struct s_cmd_line	*next;
}						t_cmd_line;

typedef struct s_num_p_cmds
{
	int					num_pipes;
	int					num_cmds;
}						t_num_p_cmds;
/*  fonction builtins  */
int						ft_pwd(t_cmd_line **commands_v);
int						ft_echo(t_cmd_line **commands_v);
int						ft_cd(t_cmd_line **cd_cmd);
void					ft_env(t_cmd_line **commands_v);
int						ft_export(t_cmd_line **commands_v);
int						ft_exit(t_cmd_line **commands_v, int flag_exit);
int						ft_unset(t_cmd_line **commands_v);
/* end */
void					add_node(t_env **env, char *env_var, char *env_val,
							int a);
char					*remove_char(char *string, int pos);
void					change_value(t_env **env, char *env_var,
							char *new_env_val);
void					join_value(t_env **env, char *env_var,
							char *new_env_val);
void					error_identifie(char *value_of_var);
void					export_utils1(char *value_of_var, int *flag);
void					export_utils2(char *value_of_var, int i, int *flag,
							int *flag1);
void					export_utils3(char *value_of_var, int i, int *flag,
							int *flag1);
void					ft_strncpy(char *dest, const char *src, size_t n);
t_env					*dup_env(t_env *env_list);
void					change_value(t_env **env, char *env_var,
							char *new_env_val);
t_env					*init_env(void);
void					ft_add_back_env(t_env **lst, t_env *new);
t_env					*fill_env_node(char *env, t_env *t_env);
char					*fill_env_var(char *ev, int *j);
int						ft_cherch_node(char *exp_var);
int						check_syntax_cmd(char *cmd);
char					**splitre_whit_pos(char *str, size_t pos);
void					ft_execution(t_cmd_line *cmd_l);
void					error_msg(void);
t_command				*init_cmd(t_command *cmd);
void					ft_lstadd_back(t_command **lst, t_command *new);
void					ft_lstadd_back_cmds(t_cmd_line **lst, t_cmd_line *new);
int						check_syntax(t_command **cmd);
void					set_states(t_command **cmd);
t_cmd_line				*commands_struct(char **cmds);
int						files_here_doc(char **temp, t_cmd_line **tmp, int *j);
int						files_red_in(char **temp, t_cmd_line **tmp, int *j);
int						files_red_out(char **temp, t_cmd_line **tmp, int *j);
int						files_append(char **temp, t_cmd_line **tmp, int *j);
char					*change_quote_in_files(char *str);
char					*get_stop_heredoc(char *str);
int						fill_content_heredoc(char *stop, int fd, int in_q);
int						sub_check_qotes(char *str, int *i, int a);
int						check_close_qotes(char *str);
void					fill_types(t_command *tmp, char c, int *i, char *str);
char					*struct_to_str(t_command **cmd);
void					ft_lstadd_middle(t_command **cmd);
t_cmd_line				*lst_init_cmds(void);
void					extend_cmd(t_command **cmd);
char					*ft_join_char(char *str, char c);
void					skip_and_fill_in_quotes(char *str, char **s, int a,
							int *i);
void					skip_in_quotes(char *str, int a, int *i);
char					*set_spliter(char *str, char c);
char					**splite_with_pipes(t_command **cmd);
char					**splite_with_space(char *str);
t_env					*get_env(char **ev);
t_env					*get_env_1(char **ev);
char					*ft_getenv(char *str);
int						is_quots(char *str, int index);
char					*extand_var(char *cmds);
void					pipex(t_cmd_line *cmd_l);
char					**get__env(void);
char					*get__path(char *cmd);
int						is_in_qotes(char *str);
void					free_2d_table(char **temp);
int						check_command_builtins(char *command);
void					command_builtins(t_cmd_line **cmd_l);
char					*remove_quotes(char *str);
void					ft_add_back_env(t_env **lst, t_env *new);
t_env					*init_env(void);
t_command				*init_lst_in_middle(void);
void					main_free(t_command **cmd, t_cmd_line **cmd_l,
							char **temp, char *str);
void					free_2d_table(char **temp);
void					free_t_command(t_command **cmd);
void					free_t_cmd_line(t_cmd_line **cmd);
int						is_quots(char *str, int index);
char					**env_is_null(void);
void					open_pipes(int num_pipes, int **pipefd);
void					cmd_not_found(char *cmd);
int						check_command_builtins(char *command);
void					command_builtins(t_cmd_line **cmd_l);
void					dup_files_and_pipes(t_cmd_line *cmd_l, int **pipefd,
							int i, int num_pipes);
/*			files					*/
int						is_ambiguous(char *str);
int						sub_files_red_in(char **infile, t_cmd_line **tmp,
							int *j, char **temp);
int						files_red_in(char **temp, t_cmd_line **tmp, int *j);
int						sub_files_red_out(char **outfile, t_cmd_line **tmp,
							int *j, char **temp);
int						files_red_out(char **temp, t_cmd_line **tmp, int *j);
int						files_append(char **temp, t_cmd_line **tmp, int *j);
char					*ret_in_double_quotes(char *str);
char					*get_variable(char *str);
void					extand_exit_status(char **ret, int *j);
void					sub_extand_var_in_dq(char **ret, char *cmds, int *j);
void					extand_var_in_double_qoutes(char **ret, char *cmds,
							int *j);
void					ignore_extand_in_single_quotes(char **ret, char *cmds,
							int *j);
void					ignore_extand_in_herdoc(char **ret, char *cmds, int *j);
int						extand_normal_var(char **ret, char *cmds, int *j);
int						sub_extand_var(char **ret, char *cmds, int *j);
char					**change_content_cmds(char **cmds, int leen);
void					remove_double_quotes(char *str, char **ret, int *i,
							int *j);
char					*remove_quotes(char *str);
int						strlen_2d(char **str);
char					**ft_join_2d(char **tab1, char **tab2, int p);
void					extand_in_comamnd_struct(t_cmd_line **tmp, int *j);
int						sub_command_struct(t_cmd_line **tmp);
char					**fill_temp_of_command_struct(char **cmds);
t_cmd_line				*init_temp_cmd_line(char **cmds, int i);
int						open_read_out_in(char **temp, t_cmd_line **tmp, int *j);
int						open_appnd_herdoc(char **temp, t_cmd_line **tmp,
							int *j);
int						open_files_in_command_struct(char **temp,
							t_cmd_line **tmp);
void					child(int num_pipes, int i, int **pipefd,
							t_cmd_line *cmd_l);
void					wait_for_child(int *pids, int i);
void					sub2_pipex(t_num_p_cmds num, int **pipefd, int *pids,
							t_cmd_line *cmd_l);

/*			****************					*/

/*						syntax						*/
void					error_msg(void);
int						chech_syntax_exclamation_mark(t_command *tmp);
int						sub_check_syntax_error(t_command **cmd);
int						check_syntax_1(t_command *tmp, t_command *t1,
							t_command *t2);
int						check_syntax_2(t_command *tmp, t_command *t1,
							t_command *t2);

/*				***********					*/
#endif
