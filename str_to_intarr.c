
#include "fdf.h"

int	*initialize_memory(char **tempstr, int **index, int *outlength)
{
	*index = (int *)malloc(sizeof(int) * 3);
	*tempstr = (char *)malloc(sizeof(char) * 11);
	if (*tempstr == NULL)
	{
		*outlength = 0;
		return (NULL);
	}
	return (*index);
}

int	*allocate_array(int numelements, char *tempstr, int *outlength)
{
	int	*array;

	array = (int *)malloc(sizeof(int) * numelements);
	if (array == NULL)
	{
		free(tempstr);
		*outlength = 0;
		return (NULL);
	}
	return (array);
}

int	*allocate_color_array(int numelements, char *tempstr, int *outlength)
{
	int	*color_array;

	color_array = (int *)malloc(sizeof(int) * numelements);
	if (color_array == NULL)
	{
		free(tempstr);
		*outlength = 0;
		return (NULL);
	}
	return (color_array);
}

void	process_tempstr(t_parseparams *params, char *comma)
{
	if (params->index[0] > 0)
	{
		params->tempstr[params->index[0]] = '\0';
		comma = strchr(params->tempstr, ',');
		if (comma)
		{
			*comma = '\0';
			params->array[params->index[1]] = atoi(params->tempstr);
			params->color_array[params->index[1]] = strtol(comma + 1, NULL, 16);
		}
		else
		{
			params->array[params->index[1]] = atoi(params->tempstr);
			params->color_array[params->index[1]] = -1;
		}
		params->index[1]++;
		params->index[0] = 0;
	}
}

void	parse_string(char *str, t_parseparams *params)
{
	int		length;
	char	*comma;

	comma = NULL;
	length = strlen(str);
	while (params->index[2] <= length)
	{
		if (isspace(str[params->index[2]]) || str[params->index[2]] == '\0')
		{
			process_tempstr(params, comma);
		}
		else
		{
			params->tempstr[params->index[0]] = str[params->index[2]];
			params->index[0]++;
		}
		params->index[2]++;
	}
}

t_parseparams	create_parse_params(int *array, int *color_array, char *tempstr,
		int *index)
{
	t_parseparams	params;

	params.array = array;
	params.color_array = color_array;
	params.tempstr = tempstr;
	params.index = index;
	return (params);
}

int	*string_to_int_array(char *str, int *outlength, int **color_array)
{
	int				numelements;
	int				*array;
	char			*tempstr;
	int				*index;
	t_parseparams	params;

	index = initialize_memory(&tempstr, &index, outlength);
	if (index == NULL)
		return (NULL);
	numelements = count_integers_in_string(str);
	array = allocate_array(numelements, tempstr, outlength);
	if (array == NULL)
		return (NULL);
	*color_array = allocate_color_array(numelements, tempstr, outlength);
	if (*color_array == NULL)
	{
		free(array);
		return (NULL);
	}
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	params = create_parse_params(array, *color_array, tempstr, index);
	parse_string(str, &params);
	return (free(tempstr), free(index), *outlength = numelements, array);
}
