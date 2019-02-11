#include <ft_ls.h>

void print_bits(unsigned short int c, char bytes)
{
	int i = 8;
	i *= bytes;
	write(1, "\n", 1);
	while (i--)
		(c >> i) & 1 ? write(1, "1", 1) : write(1, "0", 1);
}

void print_error(char *error_file, char *msg, int error_num)
{
	char *buffer;
	char *ptr;

	if (!msg || !error_file)
		return;
	buffer = ft_strnew(ft_strlen("ft_ls: ") + ft_strlen(strerror(error_num)) +
					   ft_strlen(error_file) + ft_strlen(": ") +
					   ft_strlen(msg));
	ptr = buffer;
	ft_memmove(buffer, "ft_ls: ", 7);
	buffer += 7;
	ft_memmove(buffer, msg, ft_strlen(msg));
	buffer += ft_strlen(msg);
	ft_memmove(buffer, ": ", 2);
	buffer += 2;
	ft_memmove(buffer, "'", 1);
	buffer += 1;
	ft_memmove(buffer, error_file, ft_strlen(error_file));
	buffer += ft_strlen(error_file);
	ft_memmove(buffer, "' ", 2);
	buffer += 2;
	ft_memmove(buffer, strerror(error_num), ft_strlen(strerror(error_num)));
	ft_putendl_fd(ptr, 2);
	free(ptr);
}