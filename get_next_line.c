/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 09:44:18 by abiari            #+#    #+#             */
/*   Updated: 2020/01/26 14:21:20 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_stock(int fd, char *str)
{
	char	*temp;
	int		b_read;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	b_read = 0;
	if (!str)
		str = ft_strdup("");
	while (ft_strchr(str, '\n') == NULL)
	{
		if ((b_read = read(fd, buff, BUFFER_SIZE)) < 0)
		{
			free(buff);
			return (0);
		}
		buff[b_read] = '\0';
		temp = str;
		str = ft_strjoin(str, buff);
		free(temp);
		if (b_read == 0 || str[0] == '\0')
			break ;
	}
	free(buff);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	char		*temp;
	char		c;

	if (fd < 0 || !line || read(fd, &c, 0))
		return (-1);
	if ((str = ft_stock(fd, str)) == NULL)
		return (0);
	if (!(ft_strchr(str, '\n')))
	{
		if (!(*line = ft_strdup(str)))
			return (-1);
		free(str);
		str = NULL;
		return (0);
	}
	else
	{
		temp = str;
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));
		str = ft_strdup(str + (ft_strchr(str, '\n') - str) + 1);
		free(temp);
		return (1);
	}
}
