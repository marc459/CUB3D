/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 21:23:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		param_sorting(archparams_t *arch, validmap_t *map, char *line, int i)
{
	if (line[i] == '\0')
		i = 0;
	else if (ft_strchr("NSWESFC", line[i]))
	{
		if (!texture_checker(line + i, arch))
			return (ft_puterror("Error en el nombre de los parametros"));
	}
	else if (line[i] == 'R')
	{
		if (!identifyresolution(line, arch))
			return (ft_puterror("La resolución es invalida"));
	}
	else if (line[i] == '1')
	{
		if (arch->parameters_count != 8)
			return (ft_puterror("Faltan parametros para recorrer el mapa"));
		if (!valid_map(line, map, arch) || (map->m_top == 1 && line[0] == '\0'))
			return (ft_puterror("El mapa es invalido"));
	}
	else if (!ft_strchr("NSWESFC1", line[i]))
		return (ft_puterror("Caracter incorrecto en el archivo"));
	return (1);
}

int		loop_gnl(archparams_t *arch, validmap_t *map, char *line)
{
	int i;

	i = 0;
	while (ft_strchr(" \t", line[i]) && line[i] != '\0')
		i++;
	if (map->m_top == 1 && map->m_bot == 0 && line[0] == '\0')
		return (ft_puterror("El mapa es invalido"));
	if (!param_sorting(arch, map, line, i))
		return (0);
	i = 0;
	free(line);
	return (1);
}

int		arch_checker(char *mapfile, archparams_t *arch, validmap_t *map)
{
	int		fd;
	char	*line;
	int		retorno;

	if (!(fd = open(mapfile, O_RDONLY)))
		return (ft_puterror("Error al abrir el archivo"));
	while ((retorno = get_next_line(fd, &line)) == 1)
	{
		if (!loop_gnl(arch, map, line))
			return (0);
	}
	if (!loop_gnl(arch, map, line))
		return (0);
	if (arch->parameters_count != 8)
		return (ft_puterror("Faltan parametros en el archivo"));
	if (!map->player_dir)
		return (ft_puterror("Mapa invalido,falta la posicion del jugador"));
	close(fd);
	return (1);
}