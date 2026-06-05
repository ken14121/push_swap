/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:33 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:16 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	inside;
	int	i;

	count = 0;
	inside = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && inside == 0)
		{
			inside = 1;
			count++;
		}
		else if (s[i] == c)
			inside = 0;
		i++;
	}
	return (count);
}

static char	*copy_word(char const *s, int start, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	fill_word(char **res, char const *s, int *i, int j)
{
	int	start;

	while (s[*i] == ' ')
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != ' ')
		(*i)++;
	res[j] = copy_word(s, start, *i - start);
	if (!res[j])
		return (0);
	return (1);
}

static char	**clear_split(char **res, int j)
{
	while (j > 0)
	{
		j--;
		free(res[j]);
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		if (!fill_word(res, s, &i, j))
			return (clear_split(res, j));
		j++;
	}
	res[j] = NULL;
	return (res);
}
