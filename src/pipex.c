/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/04 17:22:48 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	check_leaks(void)
// {
// 	system("leaks pipex");
// }

void	free_and_null(void *tofree)
{
	free(tofree);
	tofree = NULL;
}

void	free_and_exit(t_input *input, int exit_code)
{
	if (input->cmd1)
		free_and_null(input->cmd1);
	if (input->cmd2)
		free_and_null(input->cmd2);
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	input->envp = NULL;
	exit(exit_code);
}

/**
 * @param argc
 * @param argv
 * @param ENV environment to parse @todo
 * @follow-up need to check if access(cmd_path, X_OK)
 * @return int EXITCODE
 */
	// print_arr(envp);
	// atexit(check_leaks);
int	main(int argc, char **argv, char **envp)
{
	t_input	input;

	ft_bzero(&input, sizeof(input));
	if (argc <= 2 && argv[1])
	{
		ft_printf("%s", argv[1]);
		free_and_exit(&input, EXIT_SUCCESS);
	}
	parse_input(argc, argv, &input);
	input.envp = envp;
	parse_envp(&input);
	parent(&input);
	free_and_exit(&input, EXIT_SUCCESS);
}
	// printf("%s\n", input.cmd1);
	// printf("%s\n", input.cmd2);
