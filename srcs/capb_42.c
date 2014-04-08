/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*   capb_42.c                                           :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   by: acontass <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/08 00:17:21 by acontass           #+#    #+#             */
/*   Updated: 2014/04/08 03:46:46 by acontass          ###   ########.fr       */
/*                                                                             */
/* *************************************************************************** */
#include "capb_42.h"

static int		ft_strcmp_equal(const char *s1, const char *s2)
{
	int			count;

	count = -1;
	while (s1[++count] && s1[count] == s2[count] && s1[count] != '=')
		;
	return (s1[count] - s2[count]);
}

static char		*ft_home(char **env)
{
	int		count[3];
	char	*ret;

	count[0] = -1;
	while (env[++count[0]])
	{
		if (!(ft_strcmp_equal("HOME=", env[count[0]])))
		{
			count[1] = -1;
			count[2] = 0;
			while (env[count[0]][++count[1]] && env[count[0]][count[1]] != '=')
				;
			while (env[count[0]][++count[1]])
				count[2]++;
			if (!(ret = malloc(sizeof(*ret) * (count[2] + 1))))
				return (0);
			count[1] = -1;
			count[2] = -1;
			while (env[count[0]][++count[1]] && env[count[0]][count[1]] != '=')
				;
			while (env[count[0]][++count[1]])
				ret[++count[2]] = env[count[0]][count[1]];
			ret[++count[2]] = '\0';
			return (ret);
		}
	}
	return (0);
}

static char	*ft_strcat(char *s1, char *s2, char c)
{
	int		count[2];
	char	*ret;

	count[0] = -1;
	while (s1[++count[0]])
		;
	count[1] = -1;
	while (s2[++count[1]])
		;
	count[0] = count[0]++;
	if (!(ret = malloc(sizeof(*ret) * (count[0] + count[1] + 1))))
		return (0);
	count[0] = -1;
	count[1] = -1;
	while (s1[++count[0]])
		ret[++count[1]] = s1[count[0]];
	ret[++count[1]] = c;
	count[0] = -1;
	while (s2[++count[0]])
		ret[++count[1]] = s2[count[0]];
	ret[++count[1]] = '\0';
	return (ret);
}

static void	ft_write_app_file(char *htdocs, int fd)
{
	int		count;

	count = -1;
	write(fd, "\n<Directory \"", 13);
	while (htdocs[++count])
		;
	write(fd, htdocs, count);
	write(fd, "\">\n", 3);
	write(fd, "\tOptions Indexes MultiViews\n", 28);
	write(fd, "\tAllowOverride All\n", 19);
	write(fd, "\t<IfVersion < 2.3 >\n", 20);
	write(fd, "\tOrder allow,deny\n", 18);
	write(fd, "\tAllow from all\n", 16);
	write(fd, "\t</IfVersion>\n", 14);
	write(fd, "\t<IfVersion >= 2.3>\n", 20);
	write(fd, "\tRequire all granted\n", 21);
	write(fd, "\t</IfVersion>\n", 14);
	write(fd, "</Directory>\n", 13);
}

static void	ft_write_vhosts_file(char *htdocs, char *tmp, char *arg, int fd)
{
	int		count;

	write(fd, "\n<VirtualHost *:8080>\n", 22);
	write(fd, "\tServerName ", 12);
	count = -1;
	while (arg[++count])
		;
	write(fd, arg, count);
	write(fd, ".local.42.fr\n", 13);
	write(fd, "\tDocumentRoot \"", 15);
	count = -1;
	while (htdocs[++count])
		;
	write(fd, htdocs, count);
	write(fd, "\"\n", 2);
	write(fd, "\tInclude \"", 10);
	count = -1;
	while (tmp[++count])
		;
	write(fd, tmp, count);
	write(fd, "\"\n", 2);
	write(fd, "</VirtualHost>\n", 15);
}

static void	ft_write_prefix_file(char *htdocs, char *tmp, char *arg, int fd)
{
	int		count;

	count = -1;
	write(fd, "Alias /", 7);
	while (arg[++count])
		;
	write(fd, arg, count);
	write(fd, "/ ", 2);
	count = -1;
	while (htdocs[++count])
		;
	write(fd, htdocs, count);
	write(fd, "/\n", 2);
	count = -1;
	write(fd, "Alias /", 7);
	while (arg[++count])
		;
	write(fd, arg, count);
	write(fd, " ", 1);
	count = -1;
	while (htdocs[++count])
		;
	write(fd, htdocs, count);
	write(fd, "\n\nInclude \"", 11);
	count = -1;
	while (tmp[++count])
		;
	write(fd, tmp, count);
	write(fd, "\"\n", 2);
}

static void	ft_write_bitnami_file(char *vhosts, int fd)
{
	int		count;

	count = -1;
	if ((lseek(fd, 0, SEEK_END)) == -1)
		return ;
	write(fd, "Include \"", 9);
	while (vhosts[++count])
		;
	write(fd, vhosts, count);
	write(fd, "\"\n", 2);
}

static void	ft_write_index_file(int fd)
{
	write(fd, "\n<html><body><h1>Hello world!</h1>\n", 35);
	write(fd, "<a href=\"phpinfo.php\">PHP info</a></body></html>\n", 49);
}

static void	ft_write_phpinfo_file(int fd)
{
	write(fd, "\n<?php\n\nphpinfo();\n\n?>\n", 23);
}

static char	ft_create_folders_n_files(char *arg, char *home)
{
	char	*tmp;
	char	*temp;
	char	*road;
	char	*conf;
	char	*bitnami;
	char	*htdocs;
	char	*vhosts;
	char	*index;
	char	*phpinfo;
	int		fd;

	if (!(tmp = ft_strcat(home, "mamp/apps", '/')))
		return (0);
	if (!(road = ft_strcat(tmp, arg, '/')))
		return (0);
	if ((mkdir(road, 0777)) == -1)
	{
		printf("Directory : %s existe deja.\n", road);
		free(tmp);
		free(road);
		return (0);
	}
	printf("Folder \"%s\" created\n", road);
	free(tmp);
	if (!(conf = ft_strcat(road, "conf", '/')))
		return (0);
	if ((mkdir(conf, 0777)) == -1)
	{
		printf("Error : %s.\n", conf);
		free(conf);
		free(road);
		return (0);
	}
	printf("Folder \"%s\" created\n", conf);
	if (!(htdocs = ft_strcat(road, "htdocs", '/')))
		return (0);
	if ((mkdir(htdocs, 0777)) == -1)
	{
		printf("Error create folder : %s.\n", htdocs);
		free(road);
		free(conf);
		free(htdocs);
		return (0);
	}
	printf("Folder \"%s\" created\n", htdocs);
	free(road);
	if (!(tmp = ft_strcat(conf, "httpd-app.conf", '/')))
		return (0);
	if ((fd = open(tmp, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", tmp);
		free(tmp);
		free(conf);
		free(htdocs);
		return (0);
	}
	printf("File \"%s\" created\n", tmp);
	ft_write_app_file(htdocs, fd);
	close(fd);
	if (!(vhosts = ft_strcat(conf, "httpd-vhosts.conf", '/')))
		return (0);
	if ((fd = open(vhosts, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", vhosts);
		free(tmp);
		free(conf);
		free(vhosts);
		free(htdocs);
		return (0);
	}
	printf("File \"%s\" created\n", vhosts);
	ft_write_vhosts_file(htdocs, tmp, arg, fd);
	close(fd);
	if (!(temp = ft_strcat(conf, "httpd-prefix.conf", '/')))
		return (0);
	if ((fd = open(temp, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", temp);
		free(tmp);
		free(conf);
		free(temp);
		free(vhosts);
		free(htdocs);
		return (0);
	}
	printf("File \"%s\" created\n", temp);
	ft_write_prefix_file(htdocs, tmp, arg, fd);
	close(fd);
	if (!(bitnami = ft_strcat(home, "mamp/apache2/conf/bitnami/bitnami-apps-vhosts.conf", '/')))
		return (0);
	if ((fd = open(bitnami, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", bitnami);
		free(tmp);
		free(conf);
		free(temp);
		free(bitnami);
		free(htdocs);
		free(vhosts);
		return (0);
	}
	printf("File \"%s\" created\n", bitnami);
	ft_write_bitnami_file(vhosts, fd);
	close(fd);
	if (!(index = ft_strcat(htdocs, "index.php", '/')))
		return (0);
	if ((fd = open(index, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", index);
		free(tmp);
		free(conf);
		free(temp);
		free(bitnami);
		free(index);
		free(htdocs);
		free(vhosts);
		return (0);
	}
	printf("File \"%s\" created\n", index);
	ft_write_index_file(fd);
	close(fd);
	if (!(phpinfo = ft_strcat(htdocs, "phpinfo.php", '/')))
		return (0);
	if ((fd = open(phpinfo, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error create file : %s.\n", phpinfo);
		free(tmp);
		free(conf);
		free(phpinfo);
		free(temp);
		free(bitnami);
		free(index);
		free(htdocs);
		free(vhosts);
		return (0);
	}
	printf("File \"%s\" created\n", phpinfo);
	ft_write_phpinfo_file(fd);
	close(fd);
	free(tmp);
	free(index);
	free(conf);
	free(temp);
	free(phpinfo);
	free(bitnami);
	free(vhosts);
	free(htdocs);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	int		count;
	char	*home;

	if (ac > 1)
	{
		count = 0;
		if (!(home = ft_home(env)))
			return (0);
		while (av[++count])
		{
			if (!(ft_create_folders_n_files(av[count], home)))
			{
				free(home);
				return (0);
			}
		}
		free(home);
	}
	return (0);
}
