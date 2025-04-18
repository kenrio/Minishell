/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:09:18 by keishii           #+#    #+#             */
/*   Updated: 2025/04/18 18:51:00 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ----------------------- include -----------------------
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>

#include "libft.h"

#define PROMPT "minishell$ "

// -------------------- define struct --------------------
// lexer_token
typedef struct s_token_state
{
	bool	in_squote;
	bool	in_dquote;
	bool	new_token;
	int		start_index;
	int		current_index;
	int		token_index;
}	t_token_state;

typedef enum e_token_type
{
	WORD,
	REDIRECT_OUT,
	REDIRECT_IN,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	token_type;
}	t_token;

typedef struct s_token_array
{
	t_token	*tokens;
	int		len;
}	t_token_array;

// expantion
typedef struct s_quote_state
{
	bool	in_double_quote;
	bool	in_single_quote;
}	t_quote_state;

// AST
// AST structure can take "cmd_node" or "pipe_node".
// cmd_node must have "redirects" member.
// we can use this to judge we shold handle "redirect" or not. 

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
}	t_node_type;

typedef enum e_redir_type
{
	R_OUT,
	R_OUT_APPEND,
	R_IN,
	R_HEREDOC,
}	t_redir_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*file_name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		struct s_cmd
		{
			char		*name;
			char		*path;
			char		**argv;
			char		**envp;
			int			*stp;
			t_redirect	*redirects;
		} cmd;
		struct s_pipe
		{
			struct s_ast	*left;
			struct s_ast	*right;
		} pipe;
	}	u_data;
}	t_ast;

typedef struct s_parse_helper
{
	t_ast	*node;
	int		index;
	int		arg_count;
}	t_parse_helper;

// pids
typedef struct s_pid_node
{
	pid_t				pid;
	struct s_pid_node	*next;
}	t_pid_node;

typedef struct s_pids
{
	t_pid_node	*head;
	t_pid_node	*tail;
}	t_pids;

// envl
typedef struct s_env_node
{
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_envl
{
	t_env_node	*head;
	t_env_node	*tail;
	int			count;
}	t_envl;

// -------------------- functions --------------------
// run_ast
int		run_ast(t_ast *ast_node, t_envl *envl, int *status);
int		execute_ast(t_ast *ast_node, int fd_in, t_pids *pids);

// run_ast_sub
int		exec_ast_pipe(t_ast *ast_node, int fd_in, t_pids *pids);
void	exec_right_cmd(t_ast *ast_node, int fd_in, t_pids *pids);
void	exec_left_cmd(t_ast *node, int fd_in, int fd_pipe[], t_pids *pids);

// pids
void	init_pids(t_pids *pids);
int		pids_push_back(t_pids *pids, pid_t pid);
void	wait_pids(t_pids *pids, int *status);
void	destroy_pids(t_pids	*pids);

// redirect
int		handle_redirects(t_ast *node, int *fd_in_, int *fd_out_);
int		handle_heredoc(int *fd_in_, char *delimiter, char **envp, int *stp);

// envp
t_envl	*make_envl(char **envp);
void	destroy_envl(t_envl *lst);
int		envl_add_node(t_envl *lst, char *value);
int		envl_rm_node(t_envl *lst, char *key);
char	**make_envp_by_envl(t_envl *lst);
int		envl_push_back(t_envl *lst, char *value);

// boundary_split
char	**boundary_split(char const *str, int (*is_boundary)(int));
void	destroy_split(char **array);

// join_all_split
char	*join_all_split(char **array);

// get_path
char	*get_cmd_path(char **envp, char	*name);
char	*get_env_value_bykey(char **envp, char *key);

// builtin
int		execute_echo(t_ast *ast);
int		execute_cd(t_ast *ast, t_envl *envl);
int		execute_pwd(void);
int		execute_export(t_ast *ast, t_envl *envl);
int		execute_unset(t_ast *ast, t_envl *envl);
int		execute_env(t_ast *ast);
int		execute_exit(t_ast *ast, t_envl *envl);

// expantion functions
char	*expand_doller(char *str, char **envp, int *status_p);
char	*expand_doller_heredoc(char *str, char **envp, int *status_p);
char	*dq_expand_doller(char *str, char **envp, int *status_p);
int		update_elements(char **envp, char **elements, int *stp,
			t_quote_state *q_st);
int		update_elements_hdoc(char **envp, char **e, int *stp,
			t_quote_state *q_st);

// lexer functions
int		lexer(t_token_array *array, char *input_line, int *exit_status);
int		count_tokens(char *line, t_token_array *array);
int		tokenize(char *line, t_token_array *array, int *exit_status);
int		add_token_to_array(char *line, t_token_array *array,
			t_token_state *state, int *exit_status);
void	assign_token_type(t_token_array *array);
void	free_token_array(t_token_array *array);
void	init_token_state(t_token_state *state);
void	toggle_quote_state(char *line, t_token_state *state);
int		is_operator(char c);
int		is_double_operator(char *line, int index);

// parser functions
int		parser(t_ast **ast_node, t_token_array *token_array,
			t_envl *envl, int *exit_status);
int		make_ast(t_token_array *array, t_parse_helper *helper,
			t_envl *envl, int *exit_status);
int		parse_pipe(t_token_array *array, t_parse_helper *helper,
			t_envl *envl, int *exit_status);
int		make_pipe_node(t_token_array *array, t_parse_helper *helper,
			t_envl *envl, int *exit_status);
int		parse_cmd(t_token_array *array, t_parse_helper *helper,
			t_envl *envl, int *exit_status);
int		make_cmd_node(t_token_array *array, t_parse_helper *helper,
			t_envl *envl, int *exit_status);
int		add_args(t_token_array *array, t_parse_helper *helper,
			int *exit_status);
int		add_redirect(t_token_array *array, t_parse_helper *helper,
			int *exit_status);
void	free_cmd_args(t_ast *node, int count);
int		is_redirect(t_token *token);
void	free_ast(t_ast *ast);
void	free_redirects(t_redirect *redirect);
void	syntax_error(const char *s);
t_ast	*copy_ast(t_ast *src, int *exit_status);
int		reset_cmd_node_fields(t_ast *node, t_envl *envl, int *exit_status);

// signal functions
void	set_idle_handler(void);
void	idle_handler(int signum);
void	set_heredoc_handler(void);
void	set_heredoc_child_handler(void);
void	exec_handler(int signum);
void	set_exec_handler(void);
void	set_exec_child_handler(void);

// debug functions
void	debug_print_tokens(t_token_array *array);
void	check_expand(char **envp, int *stp);
void	debug_print_ast(t_ast *node, int depth);

// utils
void	print_message(void);
int		ft_isspace(char c);
int		is_doller(int c);
int		is_env_char(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*strrmchr(char *str, char *set);
int		copy_str_array(char ***dst, char **src);
void	free_str_array(char **arr);
void	exit_f(char *comment);
