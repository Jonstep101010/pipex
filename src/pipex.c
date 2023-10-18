/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 16:09:58 by jschwabe         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	input->av = argv;
	input->ac = argc;
	input->envp = envp;
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
	free_and_exit(&input, input.exit);
}
// #endif
