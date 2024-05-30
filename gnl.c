/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:23:59 by yozainan          #+#    #+#             */
/*   Updated: 2024/05/30 13:57:16 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

size_t ft_strlen(char *s)
{
    size_t  i = 0;

    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *ft_strchr(char *s, char c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == c)
            return s;
        s++;
    }
    if (c == '\0')
        return s;
    return NULL;
}

char *ft_strdup(char *s)
{
    size_t i = 0;
    char *rs = NULL;

    if (!s)
        return NULL;
    rs = malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!rs)
        return NULL;
    while (s[i])
    {
        rs[i] = s[i];
        i++;
    }
    rs[i] = '\0';
    return rs;
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t i = 0;
    size_t j = 0;
    char *rs = NULL;

   if (!s2)
    return NULL;
    if (!s1)
        return (ft_strdup(s2));
    rs = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!rs)
        return NULL;
    while (s1[i])
    {
        rs[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        rs[i] = s2[j];
        i++;
        j++;
    }
    free(s1);
    rs[i] = '\0';
    return rs;
}

char *ft_back(char *save)
{
    char *rs;
    int i = 0;
    int j = 0;

    while (save[i] && save[i] != '\n')
        i++;
    if (!save[i])
    {
        free(save);
        return NULL;
    }
    i++;
    rs = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
    if (!rs)
    {
        free(save);
        return NULL;
    }
    while (save[i])
    {
        rs[j] = save[i];
        j++;
        i++;
    }
    rs[j] = '\0';
    free(save);
    return rs;
    
}

char *get_new_line(char *tmp)
{
    char *rs;
    int i = 0;
    int j = 0;

    if (!tmp[0])
        return NULL;
    while (tmp[i] && tmp[i] != '\n')
        i++;
    if (tmp[i] == '\n')
        rs = malloc(i + 2);
    else
        rs = malloc(i + 1);
    if (!rs)
        return NULL;
    while (tmp[j] && j <= i)
    {
        rs[j] = tmp[j];
        j++;
    }
    rs[j] = '\0';
    return rs;
}


char *read_file(int fd, char *tmp)
{
    char *buff = NULL;
    int rbyte = 1;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return NULL;
    while (!ft_strchr(tmp, '\n') && rbyte)
    {
        rbyte = read(fd, buff, BUFFER_SIZE);
        if (rbyte == -1)
        {
            free(buff);
            free(tmp);
            return NULL;
        }
        buff[rbyte] = '\0';
        tmp = ft_strjoin(tmp, buff);
        if (!tmp)
            return NULL;
    }
    free(buff);
    return tmp;
}

char *ft_get_next_line(int fd)
{
    char *buff;
    static char *tmp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    tmp = read_file(fd, tmp);
    if (!tmp)
        return NULL;
    buff = get_new_line(tmp);
    tmp = ft_back(tmp);
    return (buff);
}
int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    int i = 1;
    while (line = ft_get_next_line(fd))
    {
        printf("[%d]\t%s", i, line);
        i++;
        free(line);
    }
    close(fd);
}