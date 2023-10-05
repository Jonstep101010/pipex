/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/05 11:13:32 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_arr(char **arr)
{
	int	i = 0;
	if ((!arr) || (!*arr))
		return;
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

	if (!paths || !*paths)
		return;
	tmp = *cmd;
	*cmd = ft_strjoin("/", *cmd);
	if (tmp)
		free_null_str(&tmp);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], *cmd);
		if (access(tmp, X_OK) != FAIL)
		{
			// printf("freed:%s\n", *cmd);
			free_null_str(cmd);
			// printf("set:%s\n", tmp);
			*cmd = tmp;
			return;
		}
		free_null_str(&tmp);
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
	free_null_str(&tmp);
	check_path(paths, &(input->cmd1));
	// printf("cmd1:%s\n", input->cmd1);
	check_path(paths, &(input->cmd2));
	// printf("cmd2:%s\n", input->cmd2);

	arr_free(paths);
}

char	**remove_first(char **arr)
{
	int	len;
	int	i;

	if (!*arr || !arr[1])
		return (NULL);
	len = arr_len(arr);
	ft_bzero(arr[0], ft_strlen(arr[0]));
	free_null_str(&(arr[0]));
	i = 0;
	while (i < len - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	char	**tmp1;
	char	**tmp2;

	if (argc < 5)
		free_and_exit(input, EXIT_FAILURE);
	while (input->args < argc && argv[input->args])
		input->args++;
	if (argv[1])
	{
		input->infile = argv[1];
		input->f1 = open(input->infile, O_RDONLY);
		if (input->f1 < 0)
		{
			fprintf(stderr, "pipex: No such file or directory: %s\n", argv[1]);
			free_and_exit(input, EXIT_SUCCESS);
		}
	}
	if (argv[2])
	{
		tmp1 = ft_split(argv[2], ' ');
		if (!tmp1 || !tmp1[0])
			free_and_exit(input, EXIT_FAILURE);
		input->cmd1 = ft_strdup(tmp1[0]);
		input->cmd1_args = tmp1;
	}

	if (argv[3])
	{
		tmp2 = ft_split(argv[3], ' ');
		if (!tmp2 || !*tmp2)
			free_and_exit(input, EXIT_FAILURE);
		else
		{
			input->cmd2 = ft_strdup(tmp2[0]);
			input->cmd2_args = tmp2;
		}
	}
	if (argv[4])
	{
		input->outfile = argv[4],
		input->f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
}

	// input->cmd1_args = argv[2];
	// print_arr(input->cmd1_args);
	// input->cmd2_args = argv[3];
	// print_arr(input->cmd2_args);

	// char **wth
	// wth[0] = path
	// wth[1] = -c
	// wth[2] = cmd (non spplitted)
	// wth[3] = NULL;
	// execve(path ohne cmd, wwth, envp)
	// execve(path!, )

