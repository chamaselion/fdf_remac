/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ft_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:14:54 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/31 02:05:04 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	if (ptr != NULL)
	{
		if (old_size < new_size)
			memmove(new_ptr, ptr, old_size);
		else
			memmove(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}
