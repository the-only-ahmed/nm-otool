/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 21:00:55 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 21:13:52 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	check_text(struct segment_command_64 *seg, struct mach_header_64 *mo)
{
	struct section_64	*sec;
	unsigned int		i;

	i = 0;
	sec = (struct section_64*)\
					(seg + sizeof(struct segment_command_64*) / sizeof(void*));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, TUT) && !ft_strcmp(sec->segname, TXT))
		{
			write(1, "(__TEXT,__text) section\n", 24);
			print_res(sec->addr, sec->size, (char *)mo + sec->offset);
		}
		sec = (struct section_64*)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void	check_64(struct load_command *com, struct mach_header_64 *mo)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)com;
	check_text(seg, mo);
}
