/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:34:46 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/08 11:27:33 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			count_words(char *str, char separator);
static char	*get_next_word(char *str, char separator);

char	**ft_split(char *str, char separator)
{
	char	**result;
	int		words;
	int		i;

	words = count_words(str, separator);
	i = 0;
	result = (char **)malloc(sizeof(char *) * (words + 2));
	if (!result)
		return (NULL);
	while (words-- >= 0)
	{
		if (i == 0)
		{
			result[i] = (char *)malloc(sizeof(char));
			if (!result[i])
				return (NULL);
			result[i++][0] = '\0';
		}
		else
			result[i++] = get_next_word(str, separator);
	}
	result[i] = NULL;
	return (result);
}

int	count_words(char *str, char separator)
{
	int	count;
	int	word;

	count = 0;
	while (*str)
	{
		word = 0;
		while (*str == separator)
			str++;
		while (*str && *str != separator)
		{
			if (!word)
			{
				count++;
				word = 1;
			}
			str++;
		}
	}
	return (count);
}

static char	*get_next_word(char *str, char separator)
{
	static int	cursor = 0;
	char		*next;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (str[cursor] == separator)
		cursor++;
	while (str[cursor + len] && str[cursor + len] != separator)
		len++;
	next = (char *)malloc(sizeof(char) * len + 1);
	if (!next)
		return (NULL);
	while (str[cursor] && str[cursor] != separator)
		next[i++] = str[cursor++];
	next[i] = '\0';
	return (next);
}
