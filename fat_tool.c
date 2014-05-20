/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 22:44:41 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 22:45:45 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		go_fati(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			x;
	uint32_t			offset;

	fat = (void*)ptr;
	x = fat->nfat_arch;
	x = swap_uint32(x);
	arch = (void*)ptr + sizeof(fat);
	while (x)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		x--;
	}
	ft_otool(ptr + swap_uint32(offset), NULL);
}

void		go_archivi(void *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_offt(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_art(lst, ptr, name);
}

void		ft_otool(void *mem, char *name)
{
	struct mach_header_64		*mo;
	struct load_command			*com;
	unsigned int				number;

	mo = mem;
	com = mem + sizeof(struct mach_header_64);
	number = *(int *)mem;
	if (number == MH_MAGIC_64)
		browse_cmd(com, mo);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fati(mem);
	else if (!ft_strncmp(mem, ARMAG, SARMAG))
		go_archivi(mem, name);
	else
		ft_putendl("Wrong binary format");
}
