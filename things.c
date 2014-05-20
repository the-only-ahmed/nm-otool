/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/25 19:09:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/04/27 21:06:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char		secto(t_lsection *sec, unsigned int n_sect)
{
	t_section	*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

char		typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

void		aff_things(t_things *thing)
{
	t_things	*tmp;

	tmp = thing;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%ap %c %s\n", tmp->value, tmp->type, tmp->str);
		else
			ft_printf("\t\t %c %s\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

t_things	*del_things(t_things *thing)
{
	t_things	*tmp;
	t_things	*tmp2;

	tmp = thing;
	while (tmp)
	{
		if ((tmp->type == 'z' || tmp->type == 'Z') ||\
				(tmp->next && tmp->value && tmp->value == tmp->next->value))
		{
			if (tmp->type != 'z' && tmp->type != 'Z' && tmp->next->type == '?')
				tmp = tmp->next;
			tmp2 = tmp->next;
			if (tmp2)
				tmp2->prev = tmp->prev;
			tmp->prev->next = tmp2;
			free(tmp->str);
			free(tmp);
		}
		tmp = tmp->next;
	}
	return (thing);
}
