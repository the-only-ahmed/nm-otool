/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/25 18:48:44 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 20:37:32 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	end_nm(struct symtab_command *sym, char *ptr, t_lsection *sec)
{
	int					i;
	char				*strtable;
	struct nlist_64		*list;
	t_things			*thing;

	i = 0;
	list = (void *)ptr + sym->symoff;
	thing = NULL;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0
				&& strtable + list[i].n_un.n_strx && ft_strlen(strtable +\
					list[i].n_un.n_strx) && list[i].n_type != 100)
			thing = add_things(thing, list[i], strtable, sec);
		i++;
	}
	thing = del_things(thing);
	aff_things(thing);
}

void	find_oct(char *ptr)
{
	int						cmd;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*command;
	struct symtab_command	*sym;
	t_lsection				*sec;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	cmd = header->ncmds;
	command = (void *)ptr + sizeof(*header);
	sec = get_section(command, header);
	while (i < cmd)
	{
		if (command->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)command;
			end_nm(sym, ptr, sec);
			break ;
		}
		command = (void *)command + command->cmdsize;
		i++;
	}
}

void	ft_nm(char *ptr, char *name)
{
	unsigned int		number;

	number = *(int *)ptr;
	if (number == MH_MAGIC_64)
		find_oct(ptr);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		go_archive(ptr, name);
	else
		ft_putendl("Wrong binary format");
}
