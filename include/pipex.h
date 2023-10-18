/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:02:58 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 16:10:09 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
pipes by default cause direction to shell -> command not found

non existing files need to be created

if no outfile specified, write to stdout
*/

/*
allowed external functions:
- open, close, read, write
- malloc, free
- perror, strerror
- access, dup, dup2
- execve, exit, fork
- pipe, unlink, wait, waitpid
*/

# include <fcntl.h>
# include "libft.h"
# include "structs.h"

void	close_fds(int end[2]);
void	here_doc(t_input *input);
char	**parse_args(char *s);
void	print_arr(char **arr);
void	free_and_null(void *tofree);
void	free_null_str(char **tofree);
void	free_and_exit(t_input *input, int exit_code);

void	parse_here_doc(t_input *input);
void	parse_envp(char **cmd, char **ENV);
void	parse_input(t_input *input);
void	first_child(int end[2], t_input *input);

void	middle_child(int end[2], t_input *input, char *cmd, char **cmdargs);
void	last_child(int end[2], t_input *input);
void	default_parent(t_input *input);
void	multiple_parent(t_input *input);

void	print_file(char *filename);

bool	create_outfile(char *filename);
#endif // PIPEX_H
