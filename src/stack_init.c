/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:23:14 by matnusko          #+#    #+#             */
/*   Updated: 2025/11/26 11:42:29 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	initialize_stack(int argc, char **argv, t_stack *stack, char **args)
{
	int		i;

	if (!stack)
		return (0);
	stack->a = (int *)malloc(sizeof(int) * (argc + 1));
	stack->b = (int *)malloc(sizeof(int) * (argc + 1));
	if (!stack->a)
	{
		free(stack);
		return (0);
	}
	i = 0;
	while (i < argc)
	{
		stack->a[i] = ft_atoi_wcheck(argv[i + 1], stack, args);
		i++;
	}
	stack->a[i] = '\0';
	stack->size_a = argc;
	stack->b[0] = 0;
	stack->size_b = 0;
	return (1);
}

static int	find_min_pos(int *arr, int size)
{
	int	min_pos;
	int	i;

	min_pos = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] < arr[min_pos])
			min_pos = i;
		i++;
	}
	return (min_pos);
}

static void	build_index_map(int *temp, int *indices, int size)
{
	int	i;
	int	min_pos;

	i = 0;
	while (i < size)
	{
		min_pos = find_min_pos(temp, size);
		indices[min_pos] = i;
		temp[min_pos] = INT_MAX;
		i++;
	}
}

void	convert_to_indices(t_stack *arr)
{
	int	i;
	int	*indices;

	indices = (int *)malloc(sizeof(int) * arr->size_a);
	if (!indices)
		return ;
	i = -1;
	build_index_map(arr->a, indices, arr->size_a);
	i = -1;
	while (++i < arr->size_a)
		arr->a[i] = indices[i];
	free(indices);
}
