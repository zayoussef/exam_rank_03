#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *s)
{
    size_t i = 0;
    int len = 0;
    if (!s)
        s = "(null)";
    while (s[i])
    {
        len += ft_putchar(s[i]);
        i++;
    }
    return len;
}

int ft_putdigits(long long int nb, int base)
{
    char hex[] = "0123456789abcdef";
    int len = 0;

    if (nb < 0)
    {
        nb *= -1;
        len += ft_putchar('-');
    }
    if (nb >= base)
        len += ft_putdigits(nb / base, base);
    len += ft_putchar(hex[nb % base]);
    return len;
}

int ft_printf(const char *s, ... )
{
    size_t i = 0;
    size_t len = 0;
    va_list nb;

    va_start(nb, s);
    while (s[i])
    {
        if (s[i] == '%' && s[i + 1])
        {
            i++;
            if (s[i] == 's')
                len += ft_putstr((char *)va_arg(nb, char*));
            else if (s[i] == 'x')
                len += ft_putdigits((long long int)va_arg(nb, unsigned int), 16);
            else if (s[i] == 'd')
                len += ft_putdigits((long long int)va_arg(nb, int), 10);
            else if (s[i] == '%')
                len += ft_putchar('%');
        }
        else
           len += ft_putchar(s[i]);
        i++;
    }
    va_end(nb);
    return len;
}

int main()
{
    char s[] = "hellosadfasdfa";
    ft_printf("[is ] : %s\n", s);
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 26598);
    return 0;
}
