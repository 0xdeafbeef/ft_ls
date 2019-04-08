/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 01:10:21 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/09 01:10:23 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			print_error(char const *error_file, int error_num,
				t_files_attrib *attrib)
{
	char	*error;
	char	error_m[1024];

	strerror_r(error_num, error_m, 1023);
	error = ft_strnew((ft_strlen(error_file) + 1) + ft_strlen("ft_ls: : ") +
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
		return ;
	}
	attrib->error_message = error;
}

int				is_dir(const char *path)
{
	struct stat	statbuf;

	errno = 0;
	if (lstat(path, &statbuf) != 0)
		return (0);
	return ((((((((((((((((((((((S_ISDIR(statbuf.st_mode)))))))))))))))))))))));
}

char			*get_full_path(char *fld_name, char *name)
{
	char	*path;
	int		len;

	len = ft_strlen(fld_name);
	path = ft_strnew(len + 1 + ft_strlen(name));
	ft_strcat(path, fld_name);
	if (fld_name[len - 1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, name);
	return (path);
}
