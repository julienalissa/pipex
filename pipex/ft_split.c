/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:24:35 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 19:24:35 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_lines(const char *s, char c)
{
	size_t	i;
	size_t	nb_of_line;

	i = 0;
	nb_of_line = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb_of_line = nb_of_line + 1;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_of_line);
}

static void	ft_incremente(size_t *len_words, size_t *i)
{
	*len_words = *len_words + 1;
	*i = *i + 1;
}

void	*ft_malloc_lines(const char *s, char c, char **res)
{
	size_t	i;
	size_t	len_words;
	size_t	words;

	words = 0;
	len_words = 0;
	i = 0;
	while (s[i])
	{
		len_words = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			ft_incremente(&len_words, &i);
		if (len_words > 0)
		{
			res[words] = malloc(sizeof(char) * (len_words + 1));
			if (!res[words])
				return (NULL);
		}
		words++;
	}
	return (res);
}

void	*ft_fill_lines(const char *s, char c, char **res)
{
	size_t	i;
	size_t	line_number;
	size_t	index;

	index = 0;
	line_number = 0;
	i = 0;
	while (res[line_number])
	{
		index = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			res[line_number][index] = s[i];
			i++;
			index++;
		}
		res[line_number][index] = '\0';
		line_number++;
	}
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	nb_of_line;

	nb_of_line = ft_count_lines(s, c);
	res = malloc(sizeof(char *) * (nb_of_line + 1));
	if (!res)
		return (NULL);
	res[nb_of_line] = NULL;
	ft_malloc_lines(s, c, res);
	ft_fill_lines(s, c, res);
	return (res);
}
