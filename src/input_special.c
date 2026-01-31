/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:44:27 by mateon            #+#    #+#             */
/*   Updated: 2025/11/26 11:58:46 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	special_init(char *str, t_stack *stack)
{
	char	**args;
	int		i;

	args = ft_split(str, ' ');
	i = 0;
	while (args[i])
		i++;
	initialize_stack(i, args - 1, stack, args);
	free_split(args);
}

static int	returning(long long result, t_stack *stack, char **args)
{
	if (result < -2147483648 || result > 2147483647)
	{
		write(2, "Error\n", 6);
		if (stack)
			free_stacks(stack);
		if (args)
			free_split(args);
		exit(1);
	}
	return ((int)result);
}

int	ft_atoi_wcheck(char *str, t_stack *stack, char **args)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (returning(result * sign, stack, args));
}
