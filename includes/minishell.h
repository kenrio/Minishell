/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:09:18 by keishii           #+#    #+#             */
/*   Updated: 2025/03/19 13:50:42 by tishihar         ###   ########.fr       */
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
}			t_token_state;

typedef enum	e_token_type
{
	WORD,
	REDIRECT_OUT,
	REDIRECT_IN,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	PIPE,
}				t_token_type;

typedef struct	s_token
{
	char			*token;
	t_token_type	token_type;
}				t_token;

typedef struct s_token_array
{
	t_token	*tokens;
	int		len;
}			t_token_array;

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
} t_node_type;

typedef	enum e_redir_type
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
	struct	s_redirect	*next;
} t_ridirect;

typedef	struct u_ast
{
	t_node_type	type;

	union
	{
		struct
		{
			char		*name;
			char		*path;
			char		**argv;
			t_ridirect	*redirects;
		} cmd;
		struct
		{
			struct u_ast	*left;
			struct u_ast	*right;
		} pipe;
	}	data;
}				t_ast;

// -------------------- functions --------------------

// utils functions
void	print_message(void);
int		ft_isspace(char c);
int		is_doller(int	c);
int		is_env_char(int	c);
int		ft_strcmp(const char *s1, const char *s2);
char	*strrmchr(char *str, char *set);

// boundary_split
char	**boundary_split(char const *str, int (*is_boundary)(int));
void	destroy_split(char **array);

// join_all_split
char	*join_all_split(char **array);

// get_path
char	*get_cmd_path(char **envp, char	*name);
char	*get_env_value_bykey(char **envp, char *key);

// lexer functions
int		lexer(char *input_line, int *exit_status);
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

// expantion functions
char	*expand_doller(char *str, char **envp, int *status_p);
char	*expand_doller_heredoc(char *str, char **envp, int *status_p);
char	*dq_expand_doller(char *str, char **envp, int *status_p);
int		update_elements(char **envp, char **elements, int *stp, t_quote_state *q_st);
int		update_elements_hdoc(char **envp, char **e, int *stp, t_quote_state *q_st);

// debug functions
void	debug_show_token_array(t_token_array *array);

// parser functions
int		parser(void);

