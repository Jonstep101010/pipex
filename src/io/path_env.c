/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:22:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/06 18:23:05 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path(char **paths, char **cmd)
{
	int		i;
	char	*tmp;

	if (!paths || !*paths)
		return ;
	tmp = *cmd;
	*cmd = ft_strjoin("/", *cmd);
	if (tmp)
		free_null_str(&tmp);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], *cmd);
		if (access(tmp, X_OK) != FAIL)
		{
			free_null_str(cmd);
			*cmd = tmp;
			return ;
		}
		free_null_str(&tmp);
		i++;
	}
}

void	parse_envp(t_input *input, char **ENV)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = NULL;
	i = 0;
	while (ENV && ENV[i] && ft_strncmp(ENV[i], "PATH=", 5) != 0)
		i++;
	if (!ENV || !*ENV)
		paths = ft_split("/bin:/usr/bin", ':');
	else
	{
		tmp = ft_strtrim(ENV[i], "PATH=");
		if (tmp)
			paths = ft_split(tmp, ':');
		input->envp = ENV;
		free_null_str(&tmp);
	}
	check_path(paths, &(input->cmd1));
	check_path(paths, &(input->cmd2));
	arr_free(paths);
}
	// printf("cmd1:%s\n", input->cmd1);
	// printf("cmd2:%s\n", input->cmd2);
