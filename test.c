#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

size_t ft_strlen(char *s)
{
    size_t  i = 0;
    if (!s)
        return 0;
    while(s[i])
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
    char *rs;
    size_t i = 0;

    if (!s)
        return NULL;
    rs = malloc(sizeof(char)  * (ft_strlen(s) + 1));
    if (!rs)
        return NULL;
    while (s[i])
    {
        rs[i] = s[i];
        i++;
    }
    rs[i] ='\0';
    return rs;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *rs;
    size_t i = 0;
    size_t j = 0;

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
    while(s2[j])
    {
        rs[i] = s2[j];
        i++;
        j++;
    }
    rs[i] = '\0';
    free(s1);
    return rs;
}

char *ft_back(char *tmp)
{
    char *back;
    size_t i = 0;
    size_t j = 0;

    if (!tmp)
        return NULL;
    while (tmp[i] && tmp[i] != '\n')
        i++;
    if (!tmp[i])
    {
        free(tmp);
        return NULL;
    }
    i++;
    back = malloc(sizeof(char) * (ft_strlen(tmp) - i + 1));
    if (!back)
    {
        free(tmp);
        return NULL;
    }
    while (tmp[i])
    {
        back[j] = tmp[i];
        j++;
        i++;
    }
    back[j] = '\0';
    free(tmp);
    return back;
}

char *ft_get_line(char *tmp)
{
    char *line;
    size_t i = 0;
    size_t j = 0;

    if (!tmp[0])
        return NULL;
    while (tmp[i] && tmp[i] != '\n')
        i++;
    if (tmp[i] == '\n')
        line = malloc(i + 2);
    else
        line = malloc(i + 1);
    if (!line)
        return (NULL);
    while(tmp[j] && j <= i)
    {
        line[j] = tmp[j];
        j++;
    }
    line[j] = '\0';
    return (line);
}

char *ft_read_file(int fd, char *tmp)
{
    char *buff;
    int rbyt = 1;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return NULL;
    while (!ft_strchr(tmp, '\n') && rbyt)
    {
        rbyt = read(fd, buff, BUFFER_SIZE);
        if (rbyt == -1)
        {
            free(buff);
            free(tmp);
            return NULL;
        }
        buff[rbyt] = '\0';
        tmp = ft_strjoin(tmp, buff);
        if(!tmp)
        {
            free(buff);
            return NULL;
        }
    }
    free(buff);
    return tmp;
}

char *ft_get_next_line(int fd)
{
    char *buff;
    char static *tmp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    tmp = ft_read_file(fd, tmp);
    if (!tmp)
        return NULL;
    buff = ft_get_line(tmp);
    tmp = ft_back(tmp);
    return buff;
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