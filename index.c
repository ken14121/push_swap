/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:36 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:17 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	fill_array(t_stack *s, int *arr)
{
	t_node	*cur;
	int		i;

	cur = s->head;
	i = 0;
	while (cur)
	{
		arr[i] = cur->value;
		cur = cur->next;
		i++;
	}
}

static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	find_index(int *arr, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

static void	set_indices(t_stack *s, int *arr)
{
	t_node	*cur;

	cur = s->head;
	while (cur)
	{
		cur->index = find_index(arr, s->size, cur->value);
		cur = cur->next;
	}
}

void	assign_indices(t_stack *s)
{
	int	*arr;

	arr = malloc(sizeof(int) * s->size);
	if (!arr)
		error_exit(s, NULL);
	fill_array(s, arr);
	sort_array(arr, s->size);
	set_indices(s, arr);
	free(arr);
}
