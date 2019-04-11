/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_long_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:36:24 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 16:36:38 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <pwd.h>
#include <grp.h>

void					get_permissions(mode_t perm, t_files_attrib *attrib)
{
	acl_t				acl;
	acl_entry_t			dummy;
	ssize_t				xattr;
	char				chr;

	acl = acl_get_link_np(attrib->full_path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(attrib->full_path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = ' ';
	acl_free(acl);
	attrib->st_mode_to_char = ft_strnew(11);
	permisions_look_up(perm, attrib->st_mode_to_char);
	permissions_to_char(perm, attrib->st_mode_to_char, chr);
}

void					permissions_to_char(mode_t perm, char *modeval,
						char chr)
{
	modeval[1] = (char)((perm & S_IRUSR) ? 'r' : '-');
	modeval[2] = (char)((perm & S_IWUSR) ? 'w' : '-');
	modeval[3] = (char)((perm & S_IXUSR) ? 'x' : '-');
	modeval[4] = (char)((perm & S_IRGRP) ? 'r' : '-');
	modeval[5] = (char)((perm & S_IWGRP) ? 'w' : '-');
	modeval[6] = (char)((perm & S_IXGRP) ? 'x' : '-');
	modeval[7] = (char)((perm & S_IROTH) ? 'r' : '-');
	modeval[8] = (char)((perm & S_IWOTH) ? 'w' : '-');
	modeval[9] = (char)((perm & S_IXOTH) ? 'x' : '-');
	modeval[10] = chr;
	modeval[11] = '\0';
}

size_t					get_long_props_inner_getter(struct passwd *pasw,
						struct stat *structstat, struct group *g,
								t_files_attrib *atr)
{
	size_t len;

	pasw = getpwuid((*structstat).st_uid);
	atr->owner_name = ft_strdup(pasw->pw_name);
	g = getgrgid(pasw->pw_gid);
	atr->group_name = ft_strdup(g->gr_name);
	get_permissions((*structstat).st_mode, atr);
	atr->link_count = (*structstat).st_nlink;
	atr->file_size = (size_t)(*structstat).st_size;
	len = (size_t)(*structstat).st_size + 1;
	return (len);
}

void					permisions_look_up(mode_t perm, char *modeval)
{
	if (S_ISREG(perm))
		modeval[0] = '-';
	if (S_ISBLK(perm))
		modeval[0] = 'b';
	if (S_ISCHR(perm))
		modeval[0] = 'c';
	if (S_ISFIFO(perm))
		modeval[0] = 'p';
	if (S_ISSOCK(perm))
		modeval[0] = 's';
	if (S_ISDIR(perm))
		modeval[0] = 'd';
}

char					*parse_time(const char *time)
{
	char				*ret;

	ret = ft_strnew(TIME_FORMAT_LEN);
	ft_strncpy(ret, time + 4, TIME_FORMAT_LEN);
	return (ret);
}
