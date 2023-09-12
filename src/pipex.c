/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/12 18:56:12 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_file_contents(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	exit(EXIT_SUCCESS);
}

//@todo make sure exit is appropriate for case handling
void	parse_input(int argc, char **argv, t_input *input)
{
	(void)input;
	// puts("Dies");
	if (argc < 2)
		exit(EXIT_FAILURE);
	input->infile = argv[1];
	if (argc == 2)
		print_file_contents(input->infile);
	ft_printf("\ninput %s", argv[1]);
	ft_printf("\nargc %d", argc);
}


/*
pipes by default cause direction to shell -> command not found

non existing files need to be created

if no outfile specified, write to stdout
*/
/**
 * @param argc
 * @param argv
 * @param ENV environment to parse @todo
 * @return int EXITCODE
 */
int		main(int argc, char **argv, char **ENV)
{
	t_program	pipex;


	parse_input(argc, argv, &(pipex.input));
	(void)argc;
	(void)argv;
	(void)ENV;
	// ft_printf("\nlaunched!");
	// int	fd;
	// int	i;

	// i = 0;
	// while (++i && argv[i] && i <= argc)
	// {
	// 	printf("\n%s", argv[i]);
	// }
	// printf("\n");

	// (void)ENV;
	// i = 0;
	// while (++i && ENV[i])
	// {
	// 	printf("\n%s", ENV[i]);
	// }
	// printf("\n");

	// fd = open("./def_outfile.txt", O_CREAT | O_RDWR, 0644);
	// ft_putendl_fd("Hello, World!", fd);
	// close(fd);
	return (EXIT_SUCCESS);
}
