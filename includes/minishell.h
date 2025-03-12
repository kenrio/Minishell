/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:09:18 by keishii           #+#    #+#             */
/*   Updated: 2025/03/12 15:14:27 by keishii          ###   ########.fr       */
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

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
}			t_node_type;

typedef enum e_redir_type
{
	R_OUT,
	R_OUT_APPEND,
	R_IN,
	R_HEREDOC,
}			t_redir_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*file_name;
	struct s_redirect	*next;
}			t_ridirect;

typedef enum e_token_type
{
	WORD,
	REDIRECT_OUT,
	REDIRECT_IN,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	PIPE,
}			t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	token_type;
}			t_token;

typedef struct s_token_list
{
	t_token	*token_list;
	int		num;
}			t_token_list;

typedef struct s_token_state
{
	bool	in_squote;
	bool	in_dquote;
	bool	new_token;
	int		start_index;
	int		current_index;
	int		token_index;
}			t_token_state;

// AST
// AST structure can take "cmd_node" or "pipe_node".
// cmd_node must have "redirects" member.
// we can use this to judge we shold handle "redirect" or not. 
typedef struct u_ast
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
int		ft_strcmp(const char *s1, const char *s2);

// lexer functions

int		lexer(char *input_line, int *exit_status);
int		count_tokens(char *line, t_token_list *list);
int		tokenize(char *line, t_token_list *list, int *exit_status);
int		add_token(char *line, t_token_list *list,
			t_token_state *state, int *exit_status);
void	assign_token_type(t_token_list *list);
void	free_token_list(t_token_list *list);
void	init_token_state(t_token_state *state);
void	handle_quote(char *line, t_token_state *state);
int		is_operator(char c);
int		is_double_operator(char *line, int index);
