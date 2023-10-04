/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:44 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/04 16:24:22 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_input
{
	int			args;
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
