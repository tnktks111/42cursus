/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:31:00 by ttanaka           #+#    #+#             */
/*   Updated: 2025/06/03 21:05:18 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	file_parser(char *infile, char *outfile, t_info *info);

int	file_parser(char *infile, char *outfile, t_info *info)
{
	char	*err_head;

	if (info->here_doc == true)
		return (EXIT_SUCCESS);
	info->in_fd = open(infile, O_RDONLY);
	if (info->in_fd == -1)
	{
		info->is_valid_infile = false;
		err_head = gen_errmsg_head("bash", infile);
		perror(err_head);
		free(err_head);
	}
	info->out_fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (info->out_fd == -1)
	{
		info->is_valid_outfile = false;
		err_head = gen_errmsg_head("bash", outfile);
		perror(err_head);
		free(err_head);
	}
	return (EXIT_SUCCESS);
}
