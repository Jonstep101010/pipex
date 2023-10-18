/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:44 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/17 18:10:15 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>

typedef struct s_input
{
	bool		search;
	int			exit;
	int			ac;
	char		**av;
	char		*infile;
	int			f1;
	int			f2;
	char		*outfile;
	char		*cmd1;
	char		**cmd1_args;
	char		*middle;
	char		*cmd2;
	char		**cmd2_args;
	char		**envp;
	char		*limiter;
}	t_input;

// typedef struct s_here_doc
// {
// 	char	*limiter;
// }	t_here_doc;

// /* @follow-up search is deprecated */
// typedef struct s_multiple
// {
// 	char	*cmd;
// 	pid_t	first;
// 	pid_t	middle;
// 	pid_t	last;
// }	t_multiple;

// typedef struct s_pipe
// {
// 	void		(*pipe_kind);
// 	int			exit_status;
// 	int			fd_in;
// 	int			fd_out;
// 	t_here_doc	*here_doc;
// 	char		*first_cmd;
// 	char		*last_cmd;
// 	int			end[2];
// 	t_input		*input;
// }	t_pipe;

#endif
