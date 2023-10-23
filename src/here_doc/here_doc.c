/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:31:32 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/23 16:58:49 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	loop_gnl(t_input *input, t_here_doc *s_here_doc)
{
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		s_here_doc->line = get_next_line(input->f1);
		if (!s_here_doc->line || ft_strncmp(s_here_doc->line, \
				s_here_doc->limiter, ft_strlen(s_here_doc->limiter)) == 0)
			break ;
		ft_putstr_fd(s_here_doc->line, s_here_doc->end[1]);
		free_null_str(&(s_here_doc->line));
	}
}

void	here_doc(t_input *input)
{
	t_here_doc	s_here_doc;

	s_here_doc.line = NULL;
	s_here_doc.limiter = input->limiter;
	pipe(s_here_doc.end);
	loop_gnl(input, &s_here_doc);
	hd_first_fork(input, &s_here_doc);
	dup2(s_here_doc.end[0], STDIN_FILENO);
	close_fds(s_here_doc.end);
	hd_last_fork(input, &s_here_doc);
	close_fds(s_here_doc.end);
	waitpid(-1, &(input->exit), 0);
	free_and_exit(input, EXIT_SUCCESS);
}
