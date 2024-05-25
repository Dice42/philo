/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:47:52 by mohammoh          #+#    #+#             */
/*   Updated: 2024/05/25 01:13:15 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_str_is_numeric(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static char	*is_space(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return ((char *)str + i);
}

static int	check_if_negative(int sign, char c)
{
	if (c == '-')
		sign = -sign;
	return (sign);
}

long	ret_digit(char *str, int i, int *flag)
{
	long	ret;
	int		sign;

	sign = 1;
	ret = 0;
	if ((str[i] == '+' || str[i] == '-') 
		&& (str[i + 1] != '+' && str[i + 1] != '-'))
	{
		*flag = 0;
		sign = check_if_negative(sign, str[i]);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && *flag == 0)
	{
		ret = ret * 10 + (str[i] - 48);
		if (sign * ret < INT_MIN || sign * ret > INT_MAX)
			return (0);
		i++;
	}
	return (sign * ret);
}

long	ft_atoi(char *str)
{
	unsigned int	i;
	long			ret;
	int				flag;

	i = 0;
	ret = 0;
	flag = 1;
	str = is_space(str);
	if (!str)
		return (0);
	if (ft_str_is_numeric(str))
		flag = 0;
	ret = ret_digit(str, i, &flag);
	if (flag == 1)
		return (-1);
	return (ret);
}
