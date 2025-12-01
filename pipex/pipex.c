/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:02:23 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/30 18:03:38 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **environ)
{
	t_list	value;

	ft_check_less_five_arg(argc);
	ft_define_value(&value, argc, argv, environ);
	ft_creat_first_child(&value);
	ft_creat_last_child(&value);
}
