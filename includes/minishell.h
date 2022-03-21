/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:27:32 by sclam             #+#    #+#             */
/*   Updated: 2022/03/20 15:56:43 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>

int	g_stage;

typedef struct s_node {
	char			*name;
	char			*info;
	struct s_node	*next;
}	t_node;

typedef struct s_fd
{
	int	fdin;
	int	fdout;
	int	tmpin;
	int	tmpout;
}	t_fd;

typedef struct s_redirect {
	char				*infile;
	char				*outfile;
	char				*stop;
	int					append_mod;
	int					heredoc;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd {
	char			**args;
	char			**option;
	char			*cmd;
	t_redirect		*redir;
	t_node			**env;
	size_t			*exit_status;
	pid_t			pid;
	char			*heredoc_file;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_stct {
	t_cmd	*cmd;
	t_node	*env;
	char	*last_arg;
	size_t	exit_status;
}	t_stct;

/*ENV_LISTS_FINCTIONS*/
t_node		*ft_lst_new(void);
int			ft_lst_size(t_node *lst);
t_node		*ft_lst_last(t_node *lst);
int			ft_lst_add_back(t_node **lst, t_node *new);
int			ft_lst_add_front(t_node **lst, t_node *new);
t_node		*find_list_elem(t_node *env_list, char *name);
void		env_lists(t_stct *data, char **env, int i);
t_node		*ft_copy_list(t_node *orig);
void		ft_merge_sort_list(t_node **env);
void		ft_lst_del(t_node **lst, t_node *del);
void		increment_lvl(t_node *env);
char		**ft_env_to_arr(t_node *env_list);

/*CMD_LISTS_FUNCTIONS*/
t_cmd		*new_cmd(t_stct *data, char *str);
t_cmd		*cmd_last(t_cmd *cmd);
void		cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
void		init_cmd(t_stct *data, char *str);

/*PARS_FUNCTIONS*/
int			parser(t_stct *data, char *str);
char		**parse_string(t_stct *data, char *str);
char		**split_with_quotes(char *str, char border);
char		**str_array_dup(char **str, int start, int finish);
int			count_str(char **str);
int			what_is_first(char *str);
char		**join_str(char **str_arr, char *str);
char		*last_word(char *str);
int			check_pipe(char *str, int *quotes, int word, int i);
int			check_quotes(char *str, int count1, int count2, int first_open);
int			amount_quotes(const int *quotes);
char		*find_path(char *cmd, t_stct *data, int i);
char		*ft_charjoin(char *s1, char symbol);
int			what_is_first(char *str);
char		*str_without_quotes(t_stct *data, char *str, int quote);
char		**arr_without_quotes(t_stct *data, char *str);
int			check_dollar_in_array(char **str_array);
char		*dollar(t_stct *data, char *str);
int			check_dollar(char *str);
void		last_arg(t_stct *data);

/*REDIRECT_FUNCTIONS*/
int			redirect(t_stct *data, t_cmd **cmd);
char		*new_redirect_str(char *str, int i, int j);
int			check_redirect(t_cmd **cmd);
char		**new_args(char **str_arr, char *str);
t_redirect	*new_redirect(void);
t_redirect	*last_redirect(t_redirect *redirect);
int			add_back_redirect(t_redirect **redirect, t_redirect *new);
int			outfiles_count(t_redirect *redir);
int			infiles_count(t_redirect *redir);
void		redirect_cmd_and_option(t_stct *data, t_cmd *cmd, int *i);

/*BUILTINS_FUNCTIONS*/
void		ft_cd(t_cmd *cmd);
void		ft_echo(t_cmd *cmd);
void		ft_env(t_cmd *cmd);
void		ft_pwd(t_cmd *cmd);
void		ft_exit(t_cmd *cmd);
void		ft_export(t_cmd *cmd);
void		ft_unset(t_cmd *cmd);
int			ft_check_idtf(char *str, t_cmd *cmd);
void		ft_add_idtf(char *str, int flag, t_cmd *cmd);
void		ft_print_export(t_cmd *cmd);
void		ft_cd_home(t_cmd *cmd, char *info);
void		ft_refresh_oldpwd(char *info, t_cmd *cmd);
void		ft_refresh_pwd(t_cmd *cmd);
int			ft_identif_check(char *str);

/*EXEC_FUNCTIONS*/
void		ft_child(t_cmd *cmd);
void		ft_exec_coms(t_stct *stct);
int			ft_check_one_cmd(t_fd *fd_stct, t_stct *stct);
int			ft_exec_builtin(t_cmd *cmd);
void		ft_save_first(t_fd *fd_stct);
int			ft_save_sec(t_cmd *curr, int *fdpipe, t_fd *fd_stct);
void		ft_restore_fds(t_fd *fd_stct);
int			ft_open_infiles(t_cmd *cmd);
int			ft_open_outfiles(t_cmd *cmd);
void		exec_redir(t_cmd *cmd);
void		ft_heredoc(t_cmd *cmd);
void		ignore_signal_for_shell(void);

/*FREE*/
void		*free_matrix(char **str);
void		ft_free_stcs(t_stct *stct);
void		*ft_free_lists(t_node *node);
void		*free_cmd(t_cmd *cmd);
void		free_redirect(t_redirect *redirect);

#endif /*MINISHELL_H*/