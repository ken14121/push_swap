/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:43:10 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:52 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	min_pos(t_stack *a)
{
	t_node	*cur;
	int		pos;
	int		min;
	int		i;

	cur = a->head;
	pos = 0;
	min = cur->index;
	i = 0;
	while (cur)
	{
		if (cur->index < min)
		{
			min = cur->index;
			pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (pos);
}

static void	sort_three(t_stack *a)
{
	int	x;
	int	y;
	int	z;

	x = a->head->index;
	y = a->head->next->index;
	z = a->tail->index;
	if (x > y && y < z && x < z)
		sa(a);
	else if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && x > z)
		ra(a);
	else if (x < y && y > z && x < z)
	{
		sa(a);
		ra(a);
	}
	else if (x < y && y > z && x > z)
		rra(a);
}

static void	push_min(t_stack *a, t_stack *b)
{
	int	pos;

	pos = min_pos(a);
	if (pos <= a->size / 2)
		while (pos-- > 0)
			ra(a);
	else
		while (pos++ < a->size)
			rra(a);
	pb(a, b);
}

void	sort_stack(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
	{
		while (a->size > 3)
			push_min(a, b);
		sort_three(a);
		while (b->size)
			pa(a, b);
	}
	else
		radix_sort(a, b);
}
