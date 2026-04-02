/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:33:41 by jaigonza          #+#    #+#             */
/*   Updated: 2024/05/31 12:23:28 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_OPEN_FILES
#  define MAX_OPEN_FILES 1024 
# endif

# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_strjoin(char const *s1, char const *s2);
int		gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *str);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*initialize_buffer(char *buffer);
void	ft_read(int fd, char *buf, char **buffer);
char	*ft_read_text(int fd, char *buffer);
char	*ft_get_line(char *buffer);
char	*ft_next_line(char **buffer);
#endif
