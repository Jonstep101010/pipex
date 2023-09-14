/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:32:44 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/13 14:20:11 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_input
{
	int			args;
	char		*infile;
	char		*outfile;
	char		*cmd1;
	char		*cmd2;
}	t_input;

typedef struct s_program
{
	t_input		input;
}	t_program;

#endif
