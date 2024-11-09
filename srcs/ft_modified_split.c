/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modified_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:05:20 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 11:41:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_split from libft altered to handle '' on top of spaces
// I NEED TO FINISHING CODING THAT SHIT BUT M TOO TIRED RN

#include "../includes/pipex.h"
#include "libft.h"

static void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		free(str[i]);
		i++;
	}
	free(str);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && (str[i] != c || str[i] == 39))
		{
			count++;
			while (str[i] && str[i] != c && str[i] != 39)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	count_char(const char *str, char c, int index)
{
	int	count;

	count = 0;
	while (str[index] && str[index] != c && str[index] != 39)
	{
		count++;
		index++;
	}
	return (count);
}

static char	*ft_strndup(const char *str, int index, int n)
{
	int		i;
	char	*tab;

	tab = malloc(sizeof (char) * (n + 1));
	i = 0;
	if (!tab)
		return (0);
	while (str[i] && i < n)
	{
		tab[i] = str[index + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_modified_split(const char *str, char c)
{
	int		i;
	int		j;
	char	**splitter;

	if (!str)
		return (NULL);
	splitter = ft_calloc(sizeof(char *), (count_words(str, c) + 1));
	if (!splitter)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != 39)
		{
			splitter[j++] = ft_strndup(str, i, count_char(str, c, i));
			if (!splitter[j - 1])
				return (free_all(splitter), NULL);
			while (str[i] && str[i] != c && str[i] != 39)
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (splitter);
}