/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:09:18 by keishii           #+#    #+#             */
/*   Updated: 2025/02/21 20:26:24 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ----------------------- include -----------------------
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft.h"

# define PROMPT "minishell$ "

// -------------------- define struct --------------------

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

// AST
// AST structure can take "cmd_node" or "pipe_node".
// cmd_node must have "redirects" member.
// we can use this to judge we shold handle "redirect" or not. 
typedef	struct u_ast
{
	t_node_type type;

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
			struct	u_ast	*left;
			struct	u_ast	*right;
		} pipe;
		
	} data;
} t_ast;

// -------------------- functions --------------------

void	print_message(void);




