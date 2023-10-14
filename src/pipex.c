/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 19:35:09 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #ifdef RELEASE
void	check_leaks(void)
{
	system("leaks pipex");
}

/**
 * @param argc
 * @param argv
 * @param ENV environment to parse @todo
 * @follow-up need to check if access(cmd_path, X_OK)
 * @return int EXITCODE
 */
int	main(int argc, char **argv, char **envp)
{
	// atexit(check_leaks);
	// fprintf(stderr, "argc:%d\n", argc);
	t_input	input;

	if (argc < 5)
		exit(EXIT_FAILURE);
	ft_bzero(&input, sizeof(input));
	input.argv = argv;
	input.args = argc;
	// fprintf(stderr, "'%s'\n", argv[1]);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc(&input, envp);
	// return (1);
	parse_input(argc, argv, &input);
	parse_envp(&input, envp);
	parent(&input);
	free_and_exit(&input, input.exit);
}
// #endif
