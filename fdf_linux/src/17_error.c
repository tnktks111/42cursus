/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:30:59 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 19:51:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	put_errmsg(char *err_msg);

int	put_errmsg(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (EXIT_FAILURE);
}
