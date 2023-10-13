/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 13:33:50 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #ifdef RELEASE
void	check_leaks(void)
{
	system("leaks pipex");
}


/*
structure of cmd:
./pipex here_doc LIMITER cmd1 cmd2 outfile
@follow-up use function pointer in future for interface?
*/
void	here_doc(t_input *input, char **envp)
{
	int	end[2];
	(void)envp;
	(void)input;
	char	*line;
	input->search = false;
	input->exit = EXIT_SUCCESS;
	input->f1 = STDIN_FILENO;
	input->LIMITER = input->argv[2];
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
	// *tmp1 = ft_strjoin(input->LIMITER, "\n");
	input->LIMITER = ft_strjoin(input->LIMITER, "\n");
	pid_t	first;
	line = get_next_line(input->f1);
	while (line && ft_strncmp(line, input->LIMITER, ft_strlen(input->LIMITER) + 1) != 0)
	{
		write(end[1], line, ft_strlen(line));
		free_null_str(&line);
		line = get_next_line(input->f1);
	}
	free(line);
	// fprintf(stderr, "argc:%d\n", input->args);
	// print_arr(input->cmd1_args);
	// print_arr(input->cmd2_args);
	parse_envp(input, envp);
	// printf("%s\n", input->cmd1);
	// printf("%s\n", input->cmd2);


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
	fprintf(stderr, "triggered!\nexiting with 0\n");
	free_and_exit(input, EXIT_SUCCESS);

	// input->infile = input->argv[2];
	// input->cmd1 = argv[3];
	// input->cmd2 = argv[4];


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
