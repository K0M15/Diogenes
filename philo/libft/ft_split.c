/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:04:57 by afelger           #+#    #+#             */
/*   Updated: 2024/10/18 17:33:58 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned long	count_starts(const char *s, char c)
{
	unsigned long	count;
	unsigned long	result;

	count = 0;
	result = 0;
	if (s[count] != c && s[count])
	{
		result++;
		count++;
	}
	while (s[count])
	{
		if (s[count] == c && s[count + 1] != c && s[count + 1])
			result++;
		count++;
	}
	return (result);
}

static char	*get_current(const char *s, char c)
{
	char			*result;
	unsigned int	count;

	while (*s && *s == c)
		s++;
	count = 0;
	while (s[count] && s[count] != c)
		count++;
	result = ft_calloc(count + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s, count + 1);
	return (result);
}

static const char	*get_next(const char *s, char c)
{
	unsigned int	count;

	while (*s && *s == c)
		s++;
	count = 0;
	while (s[count] && s[count] != c)
		count++;
	while (s[count] && s[count] == c)
		count++;
	return (&s[count]);
}

static void	cleanup(char **result, int amount)
{
	while (amount)
	{
		free(result[amount]);
		amount--;
	}
	free(result[amount]);
	free(result);
}

char	**ft_split(const char *s, char c)
{
	unsigned long	elements;
	unsigned long	count;
	char			**result;

	elements = count_starts(s, c) + 1;
	result = ft_calloc(elements, sizeof(char *));
	if (result == NULL)
		return (NULL);
	count = 0;
	while (count < elements - 1)
	{
		result[count] = get_current(s, c);
		if (result[count] == NULL)
		{
			cleanup(result, count);
			return (NULL);
		}
		s = get_next(s, c);
		if (ft_strlen(s) == 0)
			break ;
		count++;
	}
	return (result);
}

// #include <libc.h>

// int main()
// {
// 	char **tst = ft_split("hello!",' ');
// 	while(*tst)
// 	{
// 		printf("%s", *tst);
// 		tst++;
// 	}
// }