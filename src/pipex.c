/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/23 17:32:10 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #ifdef RELEASE
void	check_leaks(void)
{
	system("leaks pipex");
}

void	check_init_struct(t_input *input, int argc, char **argv, char **envp)
{
	if (argc < 5)
		exit(EINVAL);
	input->av = argv;
	input->ac = argc;
	input->envp = envp;
	input->access = -1;
	input->err_fd = -1;
	input->exit = EXIT_SUCCESS;
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (ft_strlen(input->av[2]) < 1)
			return (exit(EXIT_FAILURE));
		parse_here_doc(input);
		here_doc(input);
	}
	else if (argc > 5)
	{
		parse_input(input);
		multiple_parent(input);
	}
	else
	{
		parse_input(input);
		default_parent(input);
	}
}

static void	exit_parent(t_input *input, int exit_code)
{
	if (input->cmd1 && *input->cmd1)
		free_null_str(&(input->cmd1));
	if (input->cmd2 && *input->cmd2)
		free_null_str(&(input->cmd2));
	if (input->middle && *input->middle)
		free_null_str(&(input->middle));
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	exit(exit_code);
}

	// atexit(check_leaks);
/**
 * @param argc
 * @param argv
 * @return int EXITCODE
 */
int	main(int argc, char **argv, char **envp)
{
	t_input	input;

	ft_bzero(&input, sizeof(input));
	check_init_struct(&input, argc, argv, envp);
	if (WEXITSTATUS(input.exit) == 255 && WIFEXITED(input.exit))
		exit_parent(&input, 127);
	if (WIFEXITED(input.exit))
		exit_parent(&input, WEXITSTATUS(input.exit));
}
