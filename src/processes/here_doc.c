/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:31:32 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 11:50:13 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int end[2])
{
	close(end[0]);
	close(end[1]);
}

typedef struct s_pid
{
	pid_t	first;
	pid_t	last;
}	t_pid;

/*
structure of cmd:
./pipex here_doc limiter cmd1 cmd2 outfile
@follow-up use function pointer in future for interface?
*/
void	here_doc(t_input *input)
{
	int		end[2];
	char	*line;
	t_pid	childs;

	pipe(end);
	line = get_next_line(input->f1);
	while (line && ft_strncmp(line, input->limiter, ft_strlen(input->limiter) + 1) != 0)
	{
		write(end[1], line, ft_strlen(line));
		free_null_str(&line);
		line = get_next_line(input->f1);
	}
	free(line);
	childs.first = fork();
	if (childs.first == -1)
		return (perror("fork()"));
	else if (childs.first == 0)
	{
		first_child(end, input);
		waitpid(childs.first, &(input->exit), 0);
	}
	dup2(end[0], STDIN_FILENO);
	close_fds(end);
	childs.last = fork();
	if (childs.last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (childs.last == 0)
	{
		last_child(end, input);
		waitpid(childs.last, &(input->exit), 0);
	}
	close_fds(end);
	waitpid(-1, &(input->exit), 0);
	free_and_exit(input, EXIT_SUCCESS);
}
