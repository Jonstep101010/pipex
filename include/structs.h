/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:44 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 11:08:27 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_input
{
	bool		search;
	int			exit;
	int			args;
	char		**argv;
	char		*infile;
	int			f1;
	char		*outfile;
	int			f2;
	char		*cmd1;
	char		**cmd1_args;
	char		*middle;
	char		*cmd2;
	char		**cmd2_args;
	char		**envp;
	char		*LIMITER;
}	t_input;

#endif
