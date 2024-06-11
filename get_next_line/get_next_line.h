/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:02:27 by yozainan          #+#    #+#             */
/*   Updated: 2024/06/02 17:09:58 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // just using to testing!
#include <fcntl.h> // just using to testing!

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

size_t  ft_strlen(char *s);
char    *ft_strchr(char *s, char c);
char    *ft_strdup(char *s);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_back(char *tmp);
char    *ft_get_line(char *tmp);
char    *ft_read_file(int fd, char *tmp);
char    *get_next_line(int fd);

#endif
