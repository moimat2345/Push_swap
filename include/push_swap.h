/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:00:00 by matnusko          #+#    #+#             */
/*   Updated: 2025/11/25 19:14:38 by matnusko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../include/my_lib/include/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int		*a;
	int		*b;
	int		size_a;
	int		size_b;
}	t_stack;

// stack_init.c
int		initialize_stack(int argc, char **argv, t_stack *stack, char **args);
void	convert_to_indices(t_stack *arr);

// input_validation.c
int		parse_and_validate(t_stack *arr, int argc);
int		validate_no_duplicates(t_stack *arr, int argc);
int		validate_range(t_stack *arr, int argc);
int		validate_arguments(int argc, char **argv);
int		validate_format(char **arg);

// sort_small.c
void	sort_small_stack(t_stack *arr);
void	sort_three_elements(t_stack *arr);
void	sort_four_elements(t_stack *arr);
void	sort_five_elements(t_stack *arr);

// sort_radix.c
void	radix_sort(t_stack *arr);
int		get_max_bits(int n);
void	radix_sort_b(t_stack *arr, int size, int bit_size, int bit);

// operations_stack_a.c
int		sa(t_stack *stack);
int		ra(t_stack *stack);
int		rra(t_stack *stack);
int		pa(t_stack *stack);

// operations_stack_b.c
int		rb(t_stack *stack);
int		pb(t_stack *stack);

// utils.c
void	free_stacks(t_stack *arr);
int		is_sorted(t_stack *arr);
void	free_split(char **split);

// input_special.c
void	special_init(char *str, t_stack *stack);
int		ft_atoi_wcheck(char *str, t_stack *stack, char **args);

#endif
