#include "get_next_line.h"

char    *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
}