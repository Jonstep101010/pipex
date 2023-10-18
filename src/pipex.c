/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 11:50:19 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #ifdef RELEASE
void	check_leaks(void)
{
	system("leaks pipex");
}

void	parse_here_doc(t_input *input)
{
	char	**tmp1;

	input->f1 = STDIN_FILENO;
	input->outfile = input->av[input->ac - 1];
	tmp1 = parse_args(input->av[3]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		return (free_and_exit(input, EXIT_FAILURE));
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = arr_dup(tmp1);
	arr_free(tmp1);
	tmp1 = parse_args(input->av[4]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		return (free_and_exit(input, EXIT_FAILURE));
	input->cmd2 = ft_strdup(tmp1[0]);
	input->cmd2_args = arr_dup(tmp1);
	arr_free(tmp1);
	input->f2 = open(input->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input->limiter = ft_strjoin(input->av[2], "\n");
	parse_envp(&(input->cmd1), input->envp);
	parse_envp(&(input->cmd2), input->envp);
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
	else
	{
		parse_input(input);
		parent(input);
	}
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
	t_input	input;
	// atexit(check_leaks);

	ft_bzero(&input, sizeof(input));
	check_init_struct(&input, argc, argv, envp);
	free_and_exit(&input, input.exit);
}
// #endif
