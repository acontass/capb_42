/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*   phpcaf_42.h                                         :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   by: acontass <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/08 00:23:09 by acontass           #+#    #+#             */
/*   Updated: 2014/04/08 19:50:47 by acontass         ###   ########.fr       */
/*                                                                             */
/* *************************************************************************** */
#ifndef PHPCAF_42_H
# define PHPCAF_42_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>

typedef struct		s_files_n_folders
{
	char			*tmp;
	char			*temp;
	char			*road;
	char			*conf;
	char			*bitnami;
	char			*htdocs;
	char			*vhosts;
	char			*index;
	char			*phpinfo;
}					s_files_n_folders;

#endif
