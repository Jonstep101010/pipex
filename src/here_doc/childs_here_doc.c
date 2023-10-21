/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:44:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/21 17:43:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	hd_first_child(int end[2], t_input *input)
{
	close(end[0]);
	if (dup2(input->f1, STDIN_FILENO) == -1)
	{
		perror("dup2:1 first_child");
		free_and_exit(input, EXIT_FAILURE);
	}
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		perror("dup2:2 first_child");
		free_and_exit(input, EXIT_FAILURE);
	}
	close(input->f1);
	close(end[1]);
	close(input->f2);
	if (execve((char const *)input->cmd1, input->cmd1_args \
		, input->envp) == -1)
	{
		free_null_str(&(input->cmd1));
		input->error_cmd = input->cmd1_args[0];
		return (free_and_exit(input, EXIT_SUCCESS));
	}
}

void	hd_first_fork(t_input *input, t_here_doc *s_here_doc)
{
	s_here_doc->first = fork();
	if (s_here_doc->first == -1)
		return (perror("Fork: "));
	else if (s_here_doc->first == 0)
	{
		if (parse_envp(&(input->cmd1), input->envp, input) != EXIT_SUCCESS)
			input->exit = EXIT_SUCCESS;
		hd_first_child(s_here_doc->end, input);
	}
}

static void	hd_last_child(int end[2], t_input *input)
{
	close(end[1]);
	close(end[0]);
	if (dup2(input->f2, STDOUT_FILENO) == -1)
	{
		free_and_exit(input, EXIT_FAILURE);
	}
	close(input->f2);
	if (execve((char const *)input->cmd2, input->cmd2_args \
		, input->envp) == -1)
	{
		free_null_str(&(input->cmd2));
		input->error_cmd = input->cmd2_args[0];
		return (free_and_exit(input, EXIT_SUCCESS));
	}
}

void	hd_last_fork(t_input *input, t_here_doc *s_here_doc)
{
	s_here_doc->last = fork();
	if (s_here_doc->last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (s_here_doc->last == 0)
	{
		parse_envp(&(input->cmd2), input->envp, input);
		hd_last_child(s_here_doc->end, input);
	}
}
