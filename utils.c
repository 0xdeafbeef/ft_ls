#include <ft_ls.h>

void print_bits(unsigned short int c, char bytes)
{
	int i = 8;
	i *= bytes;
	write(1, "\n", 1);
	while (i--)
		(c >> i) & 1 ? write(1, "1", 1) : write(1, "0", 1);
}

void print_error(char const *error_file, int error_num, t_files_attrib *attrib)
{
	char *error;
	char error_m[1024];

	strerror_r(error_num, error_m, 1023);
	error = ft_strnew((ft_strlen(error_file) + 1) +
					  ft_strlen("ft_ls: : ") +
					  ft_strlen(error_m));
	ft_strcat(error, "ft_ls: ");
	ft_strcat(error, (error_file));
	ft_strcat(error, ": ");
	ft_strcat(error, strerror(error_num));
	ft_strcat(error, "\n");
	if (!attrib)
	{
		ft_putstr_fd(error, 1);
		free(error);
		return;
	}
	attrib->error_message = error;
}

int is_dir(const char *path)
{
	struct stat statbuf;

	errno = 0;
	if (lstat(path, &statbuf) != 0)
		return 0;

	return S_ISDIR(statbuf.st_mode);
}
