/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/19 09:39:04 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	waitpid(-1, &input.exit, 0);
	free_exit_parent(&input);
}
