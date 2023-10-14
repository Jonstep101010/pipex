/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:31:32 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 19:39:04 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
structure of cmd:
./pipex here_doc limiter cmd1 cmd2 outfile
@follow-up use function pointer in future for interface?
*/
void	here_doc(t_input *input, char **envp)
{
	int	end[2];
	char	*line;
	input->search = false;
	input->exit = EXIT_SUCCESS;
	input->f1 = STDIN_FILENO;
	input->limiter = input->argv[2];
	input->outfile = input->argv[input->args - 1];
	char	**tmp1;
	tmp1 = parse_args(input->argv[3]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = arr_dup(tmp1);
	arr_free(tmp1);
	tmp1 = parse_args(input->argv[4]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd2 = ft_strdup(tmp1[0]);
	input->cmd2_args = arr_dup(tmp1);
	arr_free(tmp1);
	input->f2 = open(input->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);

	// The hot mess of parsing inside a parent
	pipe(end);
	input->limiter = ft_strjoin(input->limiter, "\n");
	pid_t	first;
	line = get_next_line(input->f1);
	while (line && ft_strncmp(line, input->limiter, ft_strlen(input->limiter) + 1) != 0)
	{
		write(end[1], line, ft_strlen(line));
		free_null_str(&line);
		line = get_next_line(input->f1);
	}
	free(line);
	parse_envp(input, envp);
	first = fork();
	if (first == -1)
		return (perror("fork()"));
	else if (first == 0)
	{
		first_child(end, input);
		waitpid(first, 0, 0);
	}
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
	pid_t	last;
	last = fork();
	if (last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (last == 0)
	{
		last_child(end, input);
		waitpid(last, &input->exit, 0);
	}
	close(end[0]);
	close(end[1]);
	waitpid(-1, &input->exit, 0);
	free_and_exit(input, EXIT_SUCCESS);
}
