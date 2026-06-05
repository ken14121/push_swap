/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadayas <ksadayas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:42:40 by ksadayas          #+#    #+#             */
/*   Updated: 2026/06/05 19:44:19 by ksadayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (0);
	init_stack(&a);
	init_stack(&b);
	parse_args(argc, argv, &a);
	if (!is_sorted(&a))
	{
		assign_indices(&a);
		sort_stack(&a, &b);
	}
	free_stack(&a);
	free_stack(&b);
	return (0);
}
