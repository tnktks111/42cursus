/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:24:15 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 21:14:09 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft_for_fdf.h"

static int	ft_count(char const *s, char c);
static char	*word_splitter(char const *s, char c);
static char	**free_and_fail(char **words, int allocated_count);
char		**ft_split(char const *s, char c);

static int	ft_count(char const *s, char c)
{
	int	cnt;

	if (!s || !s[0])
		return (0);
	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static char	*word_splitter(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	word[i] = '\0';
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static char	**free_and_fail(char **words, int allocated_count)
{
	int	i;

	i = 0;
	while (i < allocated_count)
		free(words[i++]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**words;

	len = ft_count(s, c);
	words = (char **)malloc(sizeof(char *) * (len + 1));
	if (!words)
		return (NULL);
	words[len] = NULL;
	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[j] && s[j] == c)
			j++;
		words[i] = word_splitter(s + j, c);
		if (!words[i++])
			return (free_and_fail(words, i));
		while (s[j] && s[j] != c)
			j++;
	}
	return (words);
}
