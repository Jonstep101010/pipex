/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:35:17 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/13 16:35:26 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	create_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (false);
	ft_putstr_fd("Hello, World\n", fd);
	close(fd);
	return (true);
}
