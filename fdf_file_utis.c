/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:26:02 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/31 02:36:35 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(const char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	return (fd);
}

void	process_string(const char *str, int *i, int *in_number, int *count)
{
	while (str[*i] != '\0')
	{
		if (isdigit(str[*i]) || (str[*i] == '-' && isdigit(str[*i + 1])))
		{
			if (!*in_number)
			{
				*in_number = 1;
				(*count)++;
			}
		}
		else if (str[*i] == ',')
		{
			while (str[*i] != ' ' && str[*i] != '\0')
				(*i)++;
			*in_number = 0;
			continue ;
		}
		else
			*in_number = 0;
		(*i)++;
	}
}

int	count_integers_in_string(char *str)
{
	int	count;
	int	in_number;
	int	i;

	count = 0;
	in_number = 0;
	i = 0;
	process_string(str, &i, &in_number, &count);
	return (count);
}
