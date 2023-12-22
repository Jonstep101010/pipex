/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:38:37 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/18 18:33:43 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_and_null(void *tofree)
{
	free(tofree);
	tofree = NULL;
}

/**
 * @brief pass in address of string to free
 *
 * @param tofree &str to free
 */
void	free_null_str(char **tofree)
{
	if (!tofree || !*tofree)
		return ;
	free(*tofree);
	tofree = NULL;
}
