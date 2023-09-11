/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:02:58 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/11 16:21:06 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
allowed external functions:
- open, close, read, write
- malloc, free
- perror, strerror
- access, dup, dup2
- execve, exit, fork
- pipe, unlink, wait, waitpid
*/

# include "libft.h"

int		main(int argc, char **argv);

#endif
