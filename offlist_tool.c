/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 18:02:06 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 22:41:49 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_offlist		*add_offt(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (lst);
}

void			print_art(uint32_t off, char *ptr, char *file)
{
	int				size_fuck;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size_fuck = catch_size(arch->ar_name);
	ft_printf("\n%s(%s):\n", file, name);
	ft_otool((void*)arch + sizeof(*arch) + size_fuck, file);
}

void			browse_art(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_art(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
