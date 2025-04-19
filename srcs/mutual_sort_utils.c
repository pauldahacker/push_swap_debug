/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutual_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:10:19 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/05 19:18:11 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_on_top_a(t_stack *a, t_stack *b)
{
	int	b_has_pivot;
	int	i;

	b_has_pivot = 0;
	i = 0;
	while (i < b->len)
	{
		if (b->content[i] == a->pivot)
			b_has_pivot = 1;
		++i;
	}
	if (a->n_rotates > 0)
	{
		while (b_has_pivot && b->content[0] != a->pivot && a->n_rotates > 0)
			a->n_rotates += rrab(a, b);
		while (a->n_rotates > 0 && !fast_solution_check(a, a->len))
			a->n_rotates += rra(a);
	}
	while (b_has_pivot && b->content[0] != a->pivot)
		rrb(b);
}

void	put_on_top_b(t_stack *a, t_stack *b)
{
	int	a_has_pivot;
	int	i;

	a_has_pivot = 0;
	i = 0;
	while (i < b->len)
	{
		if (a->content[i] == b->pivot)
			a_has_pivot = 1;
		++i;
	}
	if (b->n_rotates > 0)
	{
		while (a_has_pivot && a->content[0] != b->pivot && b->n_rotates > 0)
			b->n_rotates += rrab(b, a);
		while (b->n_rotates > 0 && !fast_solution_check(b, b->len))
			b->n_rotates += rrb(b);
	}
	while (a_has_pivot && a->content[0] != b->pivot)
		rra(a);
}
