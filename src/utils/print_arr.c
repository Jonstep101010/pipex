/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:21:06 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/06 18:21:16 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if ((!arr) || (!*arr))
		return ;
	while (arr[i])
	{
		ft_printf("%d\"%s\"", i, arr[i]);
		i++;
	}
	ft_printf("\n");
}
