#include "get_next_line.h"

char    *strdup_line(char *line)
{
    int     len;
    int     ind;
    char    *ret;

    ind = -1;
    while (line[++ind])
        len++;
    ind = -1;
    ret = (char *) malloc(sizeof(char) * (len + 1));
    if (!ret)
        return (NULL);
    while (++ind < len)
        ret[ind] = line[ind];
    ret[ind] = '\0';
    return (ret);
}

char    *get_next_line(int fd)
{
    char        buffer[BUFFER_SIZE + 1];
    char        line[70000];
    static int  buff_read;
    static int  buff_pos;
    int         ind;

    ind = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buff_pos >= buff_read)
        {
            buff_read = read(fd, buffer, BUFFER_SIZE);
            if (buff_read <= 0)
                break ;
            buffer[buff_read] = '\0';
            buff_pos = 0;
        }
        line[ind] = buffer[buff_pos++];
        if (line[ind] == '\n')
        {
            ind++;
            break ;
        }
        ind++;
    }
    line[ind] = '\0';
    if (!ind)
        return (NULL);
    return (strdup_line(&(line[0])));

}