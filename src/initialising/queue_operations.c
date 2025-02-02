/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:00:31 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 10:00:46 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	enqueue(t_queue **queue, int x, int y)
{
	t_queue	*new;
	t_queue	*temp;

	new = gc_malloc(sizeof(t_queue));
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!(*queue))
		*queue = new;
	else
	{
		temp = *queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	dequeue(t_queue **queue)
{
	t_queue	*temp;

	if (!(*queue))
		return ;
	temp = *queue;
	*queue = (*queue)->next;
	gc_free_ptr(temp);
}
