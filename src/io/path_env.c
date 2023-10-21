/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:22:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/21 17:33:20 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wrap_access(char *cmd)
{
	if (access(cmd, F_OK) == EXIT_SUCCESS)
	{
		if (access(cmd, X_OK) != EXIT_SUCCESS)
			return (ERR_X_KO);
		else
			return (EXIT_SUCCESS);
	}
	return (ERR_F_KO);
}

		//f_ok did you find (127) command not found
		//x_ok executable permission(126) no permission to execute
static void	check_path(char **paths, char **cmd, int *status)
{
	char	*tmp;

	if (!paths || !*paths)
		return ;
	tmp = *cmd;
	if (*cmd && **cmd != '/' && **cmd != '.')
		*cmd = ft_strjoin("/", *cmd);
	if (tmp)
		free_null_str(&tmp);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, *cmd);
		*status = wrap_access(tmp);
		if (*status == EXIT_SUCCESS)
		{
			free_null_str(cmd);
			*cmd = tmp;
			return ;
		}
		free_null_str(&tmp);
		paths++;
	}
}

/**
 * @brief pass address of cmd and environment
 * @param cmd will be concatenated to contain binary path
 * @param ENV
 */
int	parse_envp(char **cmd, char **ENV, t_input *input)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = NULL;
	i = 0;
	if (wrap_access(*cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	input->error_cmd = ft_strdup(*cmd);
	while (ENV && ENV[i] && ft_strncmp(ENV[i], "PATH=", 5) != 0)
		i++;
	if (!ENV || !*ENV)
		paths = ft_split("/bin:/usr/bin", ':');
	tmp = ft_strtrim(ENV[i], "PATH=");
	if (tmp)
		paths = ft_split(tmp, ':');
	free_null_str(&tmp);
	check_path(paths, cmd, &(input->access));
	arr_free(paths);
	if (input->access != EXIT_SUCCESS)
		free_and_exit(input, input->access);
	free_null_str(&(input->error_cmd));
	return (EXIT_SUCCESS);
}
