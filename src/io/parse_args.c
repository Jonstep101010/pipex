/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:41:55 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 09:57:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef RELEASE
#include "pipex.h"
#endif
#include "libft.h"
#include "parse_args.h"
static int	str_cchr(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static char	**helper_cmd(char **ret, char *s, int count, int i)
{
	int			ii;

	while (s[i] && (unsigned long)count < sizeof(ret) - 1)
	{
		if (s[i] == '\'')
		{
			ii = i + 1;
			while (s[ii + 1] != '\'')
				ii++;
			ret[count] = ft_substr(s, i + 1, ii - i);
			i = ii + 1;
			count++;
		}
		i++;
	}
	return (ret);
}

char	**parse_args(char *s)
{
	int		i;
	int		count;
	char	**ret;
	char	*cmd;

	cmd = NULL;
	if (ft_strchr(s, '\'') == 0 && (ft_strchr(s, '{') == 0
			|| ft_strchr(s, '}') == 0))
		return (ft_split(s, ' '));
	i = 0;
	while (!ft_isspace(s[i]) && s[i] && s[i + 1])
		i++;
	count = str_cchr(s, '\'') - str_cchr(s, '\\');
	if (count >= 2)
		count /= 2;
	ret = (char **) ft_calloc(count + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_substr(s, 0, (size_t)i);
	helper_cmd(ret, s, 1, i + 1);
	return (ret);
}
