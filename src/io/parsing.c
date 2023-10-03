/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/03 20:57:09 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_arr(char **arr)
{
	int	i = 0;
	while (arr[i])
	{
		ft_printf("%d'%s'", i, arr[i]);
		i++;
	}
	ft_printf("\n");
}

void	check_path(char **paths, char **cmd)
{
	int	i = 0;
	char	*tmp;

	tmp = *cmd;
	*cmd = ft_strjoin("/", *cmd);
	if (tmp)
		free(tmp);

	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], *cmd);
		if (access(tmp, X_OK) != FAIL)
		{
			// printf("freed:%s\n", *cmd);

			free(*cmd);
			// printf("set:%s\n", tmp);
			*cmd = tmp;
			return;
		}
		free(tmp);
		i++;
	}
}

void	parse_envp(t_input *input)
{
	char	**ENV;
	char	**paths;
	char	*tmp;
	int		i;

	ENV = input->envp;
	paths = NULL;

	i = 0;
	//get to path
	while (ENV[i] && ft_strncmp(ENV[i], "PATH=", 5) != 0)
		i++;
	tmp = ft_strtrim(ENV[i], "PATH=");
	if (tmp)
		paths = ft_split(tmp, ':');
	// if (!paths)
	// {
	// 	free_and_null((void*)tmp);
	// 	arr_free(paths);
	// 	free_and_exit(input, EXIT_FAILURE);
	// }
	free_and_null((void*)tmp);
	// print_arr(paths);
	check_path(paths, &(input->cmd1));
	printf("cmd1:%s\n", input->cmd1);
	check_path(paths, &(input->cmd2));
	printf("cmd2:%s\n", input->cmd2);

	arr_free(paths);
}

// void	arr_dup_range(char **arr, t_input *input, char **inparr, size_t start)
// {
// 	size_t	i;
// 	char	**ret;

// 	i = 0;
// 	if (arr_len(arr) <= start)
// 		return;
// 	while (arr[i] && i <= start)
// 		i++;
// 	ret = (char **) ft_calloc(arr_len(arr) - start, sizeof(char *));
// 	if (!ret)
// 		free_and_exit(input, EXIT_FAILURE);
// 	while (i < arr_len(arr) - start)
// 	{
// 		ret[i] = ft_strdup(arr[i]);
// 		i++;
// 	}
// 	arr_free(arr);
// 	inparr = ret;
// }

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	input->args = 0;
	if (argc < 3)
		free_and_exit(input, EXIT_FAILURE);
	while (input->args < argc && argv[input->args])
		input->args++;
	char	**tmp1;
	char	**tmp2;

	tmp1 = ft_split(argv[2], ' ');
	tmp2 = ft_split(argv[3], ' ');
	if (!tmp1[0] || !tmp2[0])
		free_and_exit(input, EXIT_FAILURE);
	*input = (t_input)
	{
		.infile = argv[1],
		.f1 = open(argv[1], O_RDONLY),
		.cmd1 = ft_strdup(tmp1[0]),
		.cmd2 = ft_strdup(tmp2[0]),
		.outfile = argv[4],
		.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644),
	};
	print_arr(tmp1);
	arr
	print_arr(tmp2);
	arr_free(tmp2);
	arr_free(tmp1);
	print_arr(input->cmd1_args);
	// printf("%s\n", input->cmd2);
	print_arr(input->cmd2_args);
	// printf("%s\n", input->outfile);


}

