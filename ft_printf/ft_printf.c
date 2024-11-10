#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int ft_putchar(char c);
static int  ft_putstr(char *str);
static int  ft_putnum_dec(int num);
static int  ft_putnum_hex(unsigned int num);
static int  check_conversion(const char *str, va_list args, int ind);

int ft_printf(const char *str, ...)
{
    int ind;
    va_list args;
    int len;

    ind = 0;
    len = 0;
    va_start(args, str);
    while (str[ind])
    {
        if (str[ind] == '%')
            if (str[ind + 1] == 's' || str[ind + 1] == 'd' || str[ind + 1] == 'x')
            {
                len += check_conversion(str, args, ind + 1);
                ind += 2;
                continue ;
            }
        len += ft_putchar(str[ind]);
        ind++;
    }
    va_end(args);
    return (len);
}

static int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

static int  ft_putstr(char *str)
{
    int ind;

    ind = -1;
    while (str[++ind])
        ft_putchar(str[ind]);
    return (ind);
}

static int  ft_putnum_dec(int num)
{
    int     len;

    len = 0;
    if (num == INT_MIN)
        return (ft_putstr("-2147483648"));
    if (num < 0)
    {
        len += ft_putchar('-');
        num *= -1;
    }
    if (num > 9)
        len += ft_putnum_dec(num / 10);
    len += ft_putchar((num % 10) + '0');
    return (len);
}

static int  ft_putnum_hex(unsigned int num)
{
    char    *base;
    int     len;

    base = "0123456789abcdef";
    len = 0;
    if (num > 15)
        len += ft_putnum_hex(num / 16);
    len += ft_putchar(base[num % 16]);
    return (len);
}

static int  check_conversion(const char *str, va_list args, int ind)
{
    if (str[ind] == 's')
        return (ft_putstr(va_arg(args, char *)));
    if (str[ind] == 'd')
        return (ft_putnum_dec(va_arg(args, int)));
    if (str[ind] == 'x')
        return (ft_putnum_hex(va_arg(args, unsigned int)));
    return (0);
}