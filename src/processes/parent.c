/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/29 17:52:18 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(t_input *input)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		perror("child1: error (fork())");
	else if (child1 == 0)
	{
		child_one(end, input);
		waitpid(child1, &status, 0);
	}
	child2 = fork();
	if (child2 < 0)
	{
		perror("child2: error (fork())");
		waitpid(child2, &status, 0);
	}
	else if (child2 == 0)
		child_two(end, input);
	close(end[0]);
	close(end[1]);
}
