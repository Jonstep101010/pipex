/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/04 17:39:27 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	check_leaks(void)
// {
// 	system("leaks pipex");
// }



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
