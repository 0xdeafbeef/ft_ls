#include <ft_ls.h>

void print_bits(unsigned short int c, char bytes)
{
	int i = 8;
	i *= bytes;
	write(1, "\n", 1);
	while (i--)
		(c >> i) & 1 ? write(1, "1", 1) : write(1, "0", 1);
}

void print_error(char const *error_file, int error_num)
{
	char *error;

	error = ft_strnew((ft_strlen(ft_strrchr(error_file, '/')) + 1) +
					  ft_strlen("ft_ls: : ") +
					  ft_strlen(strerror(error_num)));
	ft_strcat(error, "ft_ls: ");
	ft_strcat(error, (ft_strrchr(error_file, '/')) + 1);
	ft_strcat(error, ": ");
	ft_strcat(error, strerror(error_num));
	ft_putendl_fd(error, 2);
	free(error);
}

int is_dir(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}
