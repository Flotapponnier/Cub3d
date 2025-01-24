/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:31:02 by eebert            #+#    #+#             */
/*   Updated: 2025/01/24 17:35:04 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCOLLECTOR_H
# define GCOLLECTOR_H

# include <unistd.h>

void	*gc_add(void *ptr);

void	*gc_malloc(size_t size);

void	gc_free(void);

void	gc_free_ptr(void *addr);

void	gc_list_clear(t_list **list, void (*del)(void *));

void	gc_close_fds(void);

int		gc_add_fd(int fd);

void	gc_close_fd(int fd);

#endif
