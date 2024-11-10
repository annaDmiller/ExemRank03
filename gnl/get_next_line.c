#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char *tail;
    char    *buffer[BUFFER_SIZE];
    char    *line;
    int     ind_nl;
    int     bytes;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    line = NULL;
    if (!tail)
    {
        while (bytes = read(fd, &(buffer[0]), BUFFER_SIZE - 1))
        {
            if (bytes == -1)
                return (NULL);
            buffer[bytes] = '\0';
            ind_nl = check_new_line_in_buff(&(buffer[0]));
            if (ind_nl != bytes)
            {
                line = ft_realloc(&(buffer[0]), line);
                if (ind_nl < bytes)
                {
                    tail = add_tail(&(buffer[0]), ind_nl);
                    return (line);
                }
            }
        }
    }
    
}

static int  check_new_line_in_buff(char *str)
{
    int ind;

    ind = 0;
    while (str[ind])
    {
        if (str[ind] == '\n')
            return (ind);
        ind++;
    }
    return (ind);
}