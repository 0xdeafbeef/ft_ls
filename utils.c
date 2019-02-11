#include <ft_ls.h>

void print_bits(unsigned short int c, char bytes)
{
	int i = 8;
	i *= bytes;
	write(1, "\n", 1);
	while (i--)
		(c >> i) & 1 ? write(1, "1", 1) : write(1, "0", 1);
}

void print_error(char * error_file, char *msg)
{
	if (!msg || !error_file)
		return;
	ft_putstr_fd(error_file,2);
	ft_putstr_fd(": ",2);
	ft_putstr_fd(msg,2);
}