/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/29 18:02:56 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include <assert.h>

/**
 * @param argc
 * @param argv
 * @param ENV environment to parse @todo
@follow-up need to check if access(cmd_path, X_OK)
 * @return int EXITCODE
 */
int	main(int argc, char **argv, char **envp)
{
	t_input	input;

	if (argc <= 2 && argv[1])
		return (print_file(argv[1]), EXIT_SUCCESS);
	parse_input(argc, argv, &input);
	input.envp = envp;
	parent(&input);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
