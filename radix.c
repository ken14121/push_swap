/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:43:07 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:29 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	max_bits(int max)
{
	int	bits;

	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

static void	sort_bit(t_stack *a, t_stack *b, int bit)
{
	int	j;
	int	size;

	j = 0;
	size = a->size;
	while (j < size)
	{
		if (((a->head->index >> bit) & 1) == 1)
			ra(a);
		else
			pb(a, b);
		j++;
	}
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	bits;
	int	i;

	bits = max_bits(a->size - 1);
	i = 0;
	while (i < bits)
	{
		sort_bit(a, b, i);
		while (b->size)
			pa(a, b);
		i++;
	}
}
