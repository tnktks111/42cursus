/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:25 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 17:54:53 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	switch_menu_frag(t_env *env);

void	switch_menu_frag(t_env *env)
{
	env->display_menu = !(env->display_menu);
	redraw_line_after_tab(env);
}
