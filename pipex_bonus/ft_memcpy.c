/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memcpy.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/30 17:58:33 by jualissa       #+#    #+#                */
/*   Updated: 2025/11/30 17:58:34 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*real_dest;
	unsigned char	*real_src;

	real_dest = (unsigned char *)dest;
	real_src = (unsigned char *)src;
	i = 0;
	if ((!real_dest && !real_src))
		return (NULL);
	while (n > 0)
	{
		real_dest[i] = real_src [i];
		i++;
		n--;
	}
	return (real_dest);
}
