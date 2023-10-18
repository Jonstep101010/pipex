/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:31:32 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 16:13:50 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int end[2])
{
	close(end[0]);
	close(end[1]);
}

void	loop_gnl(t_input *input, t_here_doc *s_here_doc)
{
	s_here_doc->line = get_next_line(input->f1);
	while (s_here_doc->line && ft_strncmp(s_here_doc->line, 
			s_here_doc->limiter, 
			ft_strlen(s_here_doc->limiter) + 1) != 0)
	{
		write(s_here_doc->end[1], s_here_doc->line, 
			ft_strlen(s_here_doc->line));
		free_null_str(&(s_here_doc->line));
		s_here_doc->line = get_next_line(input->f1);
	}
	free(s_here_doc->line);
}

/*
structure of cmd:
./pipex here_doc limiter cmd1 cmd2 outfile
@follow-up use function pointer in future for interface?
*/
void	here_doc(t_input *input)
{
	t_here_doc	s_here_doc;

	ft_bzero(&s_here_doc, sizeof(s_here_doc));
	pipe(s_here_doc.end);
	loop_gnl(input, &s_here_doc);
	s_here_doc.first = fork();
	if (s_here_doc.first == -1)
		return (perror("fork()"));
	else if (s_here_doc.first == 0)
	{
		first_child(s_here_doc.end, input);
		waitpid(s_here_doc.first, &(input->exit), 0);
	}
	dup2(s_here_doc.end[0], STDIN_FILENO);
	close_fds(s_here_doc.end);
	s_here_doc.last = fork();
	if (s_here_doc.last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (s_here_doc.last == 0)
	{
		last_child(s_here_doc.end, input);
		waitpid(s_here_doc.last, &(input->exit), 0);
	}
	close_fds(s_here_doc.end);
	waitpid(-1, &(input->exit), 0);
	free_and_exit(input, EXIT_SUCCESS);
}
