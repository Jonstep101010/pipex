/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:02:58 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/05 10:08:37 by jschwabe         ###   ########.fr       */
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

void	print_arr(char **arr);
void	free_and_null(void *tofree);
void	free_null_str(char **tofree);
void	free_and_exit(t_input *input, int exit_code);

void	parse_envp(t_input *input);
void	parse_input(int argc, char **argv, t_input *input);
void	child_one(int end[2], t_input *input);
void	child_two(int end[2], t_input *input);
void	parent(t_input *input);

void	print_file(char *filename);

bool	create_outfile(char *filename);

#endif
