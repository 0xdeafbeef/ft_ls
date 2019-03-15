#include <ft_ls.h>

void print_bits(unsigned short int c, char bytes)
{
	int i = 8;
	i *= bytes;
	write(1, "\n", 1);
	while (i--)
		(c >> i) & 1 ? write(1, "1", 1) : write(1, "0", 1);
}

void print_error(char const *error_file, int error_num,t_files_attrib *attr)
{
	char *error;

	error = ft_strnew(1024 * 1024);
	ft_strcat(error, "ft_ls: ");
	ft_strcat(error, (ft_strrchr(error_file, '/')) +1);
	ft_strcat(error, ": ");
	ft_strcat(error,strerror(error_num));
	attr->error_mesage = error;
}
