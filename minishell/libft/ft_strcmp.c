#include "libft.h"

int    ft_strcmp(char *s1, char *s2)
{
    unsigned char    *buf1;
    unsigned char    *buf2;

    buf1 = (unsigned char *)s1;
    buf2 = (unsigned char *)s2;
    if (*buf1 != *buf2)
        return (*buf1 - *buf2);
    while (*buf1 && *buf2)
    {
        if (*buf1 != *buf2)
            return (*buf1 - *buf2);
        buf1++;
        buf2++;
    }
    if (*buf1 == '\0' && *buf2 != '\0')
        return (0 - *buf2);
    else if (*buf2 == '\0' && *buf1 != '\0')
        return (*buf1);
    return (0);
}