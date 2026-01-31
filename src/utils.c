/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:33:12 by matnusko          #+#    #+#             */
/*   Updated: 2025/11/25 19:14:32 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	free_stacks(t_stack *arr)
{
	if (arr)
	{
		if (arr->a)
			free(arr->a);
		if (arr->b)
			free(arr->b);
		free(arr);
	}
}

int	is_sorted(t_stack *arr)
{
	int	i;

	i = 0;
	while (i < arr->size_a - 1)
	{
		if (arr->a[i] > arr->a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
