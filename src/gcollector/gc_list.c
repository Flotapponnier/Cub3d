/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:43:27 by eebert            #+#    #+#             */
/*   Updated: 2025/02/02 19:21:58 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	gc_list_clear(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !del)
		return ;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		del(tmp->content);
		gc_free_ptr(tmp);
	}
}

char	**gc_add_split(const char *str, char delimiter)
{
	char	**split_array;
	int		i;

	split_array = ft_split(str, delimiter);
	if (!split_array)
		return (NULL);
	gc_add(split_array);
	i = 0;
	while (split_array[i])
	{
		gc_add(split_array[i]);
		i++;
	}
	return (split_array);
}

void	gc_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		gc_free_ptr(split[i]);
		i++;
	}
	gc_free_ptr(split);
}
