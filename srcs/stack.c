/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:07:42 by pde-masc          #+#    #+#             */
/*   Updated: 2023/12/17 14:16:32 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(int len, int a_or_b)
{
	t_stack	*init;

	init = malloc(sizeof(t_stack));
	if (!init)
		return (NULL);
	init->content = (int *)malloc((len) * sizeof(int));
	if (!init->content)
	{
		free(init);
		return (NULL);
	}
	if (a_or_b == A)
		init->len = len;
	else
		init->len = 0;
	init->a_or_b = a_or_b;
	init->is_segmented = FALSE;
	init->n_rotates = 0;
	init->pivot = 0;
	return (init);
}

t_stack	*create_stack_A(int len, char *argv[])
{
	int		i;
	t_stack	*new_stack;

	i = 0;
	new_stack = init_stack(len, A);
	if (len == 1)
		help_create(argv[0], new_stack);
	else
	{
		while (i < len)
		{
			if (!is_number(argv[i]))
				handle_error(new_stack);
			new_stack->content[i] = ft_atoi(argv[i]);
			++i;
		}
	}
	if (has_repeats(new_stack))
		handle_error(new_stack);
	return (new_stack);
}

int	lowest(int *stack_content, int len)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = stack_content[0];
	while (++i < len)
	{
		if (stack_content[i] < tmp)
			tmp = stack_content[i];
	}
	return (tmp);
}

int	highest(int *stack_content, int len)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = stack_content[0];
	while (++i < len)
	{
		if (stack_content[i] > tmp)
			tmp = stack_content[i];
	}
	return (tmp);
}

int	is_balanced(t_stack *a, t_stack *b)
{
	int	lowest_a;
	int	highest_b;

	if (a->len == 0 || b->len == 0)
		return (1);
	lowest_a = lowest(a->content, a->len);
	highest_b = highest(b->content, b->len);
	return (lowest_a > highest_b);
}

int	is_correct(t_stack *stack, int len)
{
	int	i;
	int	lowest_pos;

	if (stack->len < 2)
		return (1);
	lowest_pos = 0;
	while (stack->content[lowest_pos] != lowest(stack->content, stack->len))
		++lowest_pos;
	i = 0;
	while (i < lowest_pos)
	{
		if (stack->content[i] != lowest(stack->content + i, lowest_pos - i))
			return (0);
		++i;
	}
	while (i < len)
	{
		if ((stack->content[i]) != lowest(stack->content + i, len - i))
			return (0);
		++i;
	}
	if (lowest_pos > 0 && stack->content[len - 1] > stack->content[0])
		return (0);
	return (is_balanced(stack, stack->other_stack));
}

int	is_reverse_correct(t_stack *stack, int len)
{
	int	i;
	int	highest_pos;

	if (stack->len < 2)
		return (1);
	highest_pos = 0;
	while (stack->content[highest_pos] != highest(stack->content, stack->len))
		++highest_pos;
	i = 0;
	while (i < highest_pos)
	{
		if (stack->content[i] != highest(stack->content + i, highest_pos - i))
			return (0);
		++i;
	}
	while (i < len)
	{
		if (stack->content[i] != highest(stack->content + i, len - i))
			return (0);
		++i;
	}
	if (highest_pos > 0 && stack->content[len - 1] < stack->content[0])
		return (0);
	return (is_balanced(stack->other_stack, stack));
}

int	fast_solution_check(t_stack *stack, int len)
{
	int	top_elem;
	int	top_elem_pos;

	if (stack->len <= 3)
		return (1);
	if (stack->a_or_b == A && is_correct(stack, len))
		top_elem = lowest(stack->content, len);
	else if (stack->a_or_b == B && is_reverse_correct(stack, len))
		top_elem = highest(stack->content, len);
	else
		return (0);
	top_elem_pos = 0;
	while (stack->content[top_elem_pos] != top_elem)
		++top_elem_pos;
	while (stack->content[0] != top_elem)
	{
		if (top_elem_pos > len / 2)
			try_rrab(stack, stack->other_stack);
		else
			try_rab(stack, stack->other_stack);
	}
	return (1);
}

int	find_next_smallest(t_stack *a, t_stack *b, int value)
{
	int	tmp;
	int	i;

	if (a->len)
		tmp = a->content[0];
	i = 0;
	while (++i < a->len)
	{
		if (a->content[i] < tmp && a->content[i] != value)
			tmp = a->content[i];
	}
	i = -1;
	while (++i < b->len)
	{
		if (b->content[i] < tmp && b->content[i] != value)
			tmp = b->content[i];
	}
	return (tmp);
}

int	find_next_biggest(t_stack *a, t_stack *b, int value)
{
	int	tmp;
	int	i;

	if (a->len)
		tmp = a->content[0];
	i = 0;
	while (++i < a->len)
	{
		if (a->content[i] > tmp && a->content[i] != value)
			tmp = a->content[i];
	}
	i = -1;
	while (++i < b->len)
	{
		if (b->content[i] > tmp && b->content[i] != value)
			tmp = b->content[i];
	}
	return (tmp);
}

int get_next_move(t_stack *stack, int pivot)
{
    int last;
	int	successor;

    if (stack->len < 2 || (stack->is_segmented && stack->content[0] != pivot))
		return (NO_MOVE_FLAG);
    last = stack->content[stack->len - 1];
	if (stack->content[0] == pivot)
		return (ROTATE_FLAG);
	if (stack->a_or_b == B)
		successor = find_next_biggest(stack->other_stack, stack, pivot);
	else
		successor = find_next_smallest(stack, stack->other_stack, pivot);
    if (last != pivot)
    {
        if ((stack->a_or_b == B && stack->content[0] < last)
			|| (stack->a_or_b == A && stack->content[0] > last))
			return (ROTATE_FLAG);
		return (RROTATE_FLAG);
    }
	if (stack->content[0] == successor)
		return (ROTATE_FLAG);
	return (NO_MOVE_FLAG);
}
