/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/06 19:16:03 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	str_cchr(char *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// static char	**helper_cmd(char **ret, char *s, int count)
// {
// 	int			i;
// 	int			ii;

// 	i = 0;
// 	while (!ft_isspace(s[i]) && s[i] && s[i + 1])
// 		i++;
// 	ret[0] = ft_substr(s, 0, (size_t)i);
// 	while (s[i] && (unsigned long)count < sizeof(ret) - 1)
// 	{
// 		if (s[i] == '\'')
// 		{
// 			ii = i + 1;
// 			while (s[ii + 1] != '\'')
// 				ii++;
// 			ret[count] = ft_substr(s, i + 1, ii - i);
// 			i = ii + 1;
// 			count++;
// 		}
// 		i++;
// 	}
// 	print_arr(ret);
// 	return (ret);
// }

// /**
//  * @brief on input like paco with "awk 'something that includes spaces',
//  * parse as entire command to shell"
//  * @param input
//  * @param argv
//  */
// char	**separate_cmd_args(char *s)
// {
// 	char		**ret;
// 	int			count;

// 	if (ft_strchr(s, '\'') == 0)
// 		return (ft_split(s, ' '));
// 	count = str_cchr(s, '\'');
// 	count -= str_cchr(s, '\\');
// 	if (count % 2 != 0)
// 		return (NULL);
// 	count /= 2;
// 	ret = NULL;
// 	ret = (char **) ft_calloc(count + 2, sizeof(char *));
// 	if (!ret || !*ret)
// 		return (NULL);
// 	count = 1;
// 	helper_cmd(ret, s, count);
// 	return (ret);
// }
	// print_arr(ret);

	char	**separate_cmd_args(char *s)
{
	//goal is to remove excess, splitting only substring
	// printf("kinda sus\n");
	// char	*cmd_args1 = ft_strdup(input->cmd2_args[0]);
	// remove_first(input->cmd2_args);
	// bool	quote;
	char *cmd;
	cmd = NULL;
	// bool	flag;
	// quote = false;
	if (ft_strchr(s, '\'') == 0 && (ft_strchr(s, '{') == 0 || ft_strchr(s, '}') == 0))
		return (ft_split(s, ' '));
	// ft_substr
	int	i = 0;
	int	start = 0;
	while (!ft_isspace(s[i]) && s[i] && s[i + 1])
		i++;
	start = i + 1;
	cmd = ft_substr(s, 0, (size_t)i);
	// // printf("cmd:%s", cmd);
	// flag = false;
	int	count = 0;
	i = start;
	while (s[i])
	{
		if (s[i] == '\'')
			count++;
		i++;
	}
	i = start;
	while (s[i])
	{
		if (s[i] == '\\')
			count--;
		i++;
	}
	i = start;
	// printf("count: %d", count);
	if (count >= 2)
		count /= 2;
	// printf("count: %d", count);

	char	**ret;
	int		x = 1;
	ret = (char **) ft_calloc(count + 2, sizeof(char *));
	ret[0] = cmd;
	int	ii = 0;
	while (s[i] && x < count + 1)
	{
		if (s[i] == '\'')
		{
			ii = i + 1;
			while (s[ii + 1] != '\'')
			{
				ii++;
			}
			// printf("%d", )
			// ii++;
			//ft_strlen(s) - i - 2
			ret[x] = ft_substr(s, i + 1, ii - i);
			i = ii + 1;
			x++;
		}
		i++;
	}
	// print_arr(ret);
	return (ret);
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
	input->infile = argv[1];
	input->f1 = open(input->infile, O_RDONLY);
	if (input->f1 < 0)
		free_and_exit(input, EXIT_SUCCESS);
	tmp1 = separate_cmd_args(argv[2]);
	if (!tmp1 || !tmp1[0])
		free_and_exit(input, EXIT_FAILURE);
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = tmp1;
	tmp2 = separate_cmd_args(argv[3]);
	if (!tmp2 || !*tmp2)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd2 = ft_strdup(tmp2[0]);
	input->cmd2_args = tmp2;
	input->outfile = argv[4];
	input->f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
}
