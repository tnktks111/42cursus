/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:24:50 by ttanaka           #+#    #+#             */
/*   Updated: 2025/04/27 17:39:38 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*init_seen(char const *s1, int *seen, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (i < 256)
		seen[i++] = 0;
	i = 0;
	while (set[i])
		seen[(unsigned char)set[i++]] = 1;
	return (seen);
}

static size_t	ft_count_rmv_chr(char const *s1, int *seen)
{
	size_t	cnt;
	size_t	i;

	i = 0;
	cnt = 0;
	while (s1[i])
		if (seen[(unsigned char)s1[i++]])
			cnt++;
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		seen[256];
	size_t	i;
	size_t	j;
	size_t	len;
	char	*newstr;

	if (!(init_seen(s1, seen, set)))
		return (NULL);
	i = ft_strlen(s1);
	j = ft_count_rmv_chr(s1, seen);
	len = i - j;
	newstr = malloc(len + 1);
	if (!newstr)
		return (NULL);
	newstr[len] = '\0';
	i = 0;
	j = 0;
	while (i < len)
	{
		while (seen[(unsigned char)s1[i + j]])
			j++;
		newstr[i] = s1[i + j];
		i++;
	}
	return (newstr);
}

// // complie with ft_strlen
// int main()
// {
// 	char s1[] = "aaaabaa42tokyoaaaaa42ataobbbakayaoaaaaaaaaaaaaaaaaaaaa";
// 	char set[] = "aaabbbbbb";
// 	printf("%s\n", ft_strtrim(s1, set));
// }
