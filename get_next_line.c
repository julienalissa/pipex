/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:29:34 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/27 07:29:34 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "poulet.h"

char	*get_buffer(char *buffer, int fd)
{
	ssize_t	bytes_read;
	char	*res;
	char	*temp;

	bytes_read = 1;
	res = ft_strdup(buffer);
	if (!res)
		return (res);
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strdup(res);
		free(res);
		res = ft_strjoin_safe(temp, buffer);
		free(temp);
		if (!res)
			return (res);
	}
	return (res);
}

char	*get_line(char *res, char *buffer)
{
	size_t	get_end;
	char	*temp;

	get_end = 0;
	while (res[get_end] && res[get_end] != '\n')
		get_end++;
	if (res[get_end] == '\n')
	{
		get_end++;
		ft_memcpy(buffer, res + get_end, ft_strlen(res + get_end) + 1);
	}
	else
	{
		ft_memcpy(buffer, res + get_end, ft_strlen(res + get_end) + 1);
		temp = ft_strdup(res);
		res = ft_substr_safe(temp, 0, get_end);
		free(temp);
		return (res);
	}
	temp = ft_strdup(res);
	res = ft_substr_safe(temp, 0, get_end);
	free(temp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*res;
	char		*temp;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	res = get_buffer(buffer, fd);
	if (!res || !res[0])
	{
		free(res);
		res = NULL;
		return (res);
	}
	temp = ft_strdup(res);
	free(res);
	res = get_line(temp, buffer);
	free(temp);
	if (!res || !res[0])
	{
		free(res);
		res = NULL;
		return (res);
	}
	return (res);
}
