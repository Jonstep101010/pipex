/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:44 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/09 10:23:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// struct s_files
// {
// 	char	*infile;
// 	char	*outfile;
// 	int		fd1;
// 	int		fd2;
// 	void	*error;
// };

// struct	s_pipe
// {
// 	int	exit_code;
// 	int	fd_in;
// 	int	fd_out;
// };


typedef struct s_input
{
	int			exit;
	int			args;
	char		**argv;
	char		*infile;
	int			f1;
	char		*outfile;
	int			f2;
	char		*cmd1;
	char		**cmd1_args;
	char		*cmd2;
	char		**cmd2_args;
	char		**envp;
}	t_input;

#endif
