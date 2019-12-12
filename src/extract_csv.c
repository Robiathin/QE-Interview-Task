
#include <stdlib.h>
#include <string.h>

#include "extract_csv.h"
#include "population_data.h"


/* This isn't great but we need somewhere for token strings to point and no library is helping with this */
static char **buff_cpy_lines = NULL;

void
population_data_from_csv_free(void)
{
	for(size_t i = 0; buff_cpy_lines[i] != NULL; i++)
		free(buff_cpy_lines[i]);
	free(buff_cpy_lines);
}

population_data_t *
population_data_from_csv(char *buffer)
{
	population_data_t *pop_data;
	size_t linenum, i, data_tmp, pos, llen, j;
	char *val, *line;

	linenum = 0;
	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '\n')
			linenum++;

	pop_data = calloc(linenum, sizeof(population_data_t));
	if (pop_data == NULL)
		return (NULL);

	/* Skip the header line */
	for (pos = 0; buffer[pos] != '\n' && buffer[pos] != '\0'; pos++);
	pos++;

	buff_cpy_lines = calloc(linenum, sizeof(char *));

	linenum--;

	if (buff_cpy_lines == NULL) {
		free(pop_data);
		return (NULL);
	}

	for (i = 0; i < linenum; i++) {
		for (llen = 0; buffer[pos + llen] != '\n' && buffer[pos + llen] != '\0'; llen++);
		line = malloc(llen + 1);
		if (line == NULL) {
			population_data_from_csv_free();
			free(pop_data);
			return (NULL);
		}
		buff_cpy_lines[i] = line; /* Save for cleanup */
			
		/* strtok(3) is destructive. Copy each line to a new buffer*/
		for (j = 0; buffer[pos + j] != '\n'; j++)
			line[j] = buffer[pos + j];
		line[j] = '\0';

		val = strtok(line, ",");
		pop_data[i].first_name = val;

		val = strtok(NULL, ",");
		pop_data[i].last_name = val;

		val = strtok(NULL, ",");
		data_tmp = strtol(val, NULL, 10);
		pop_data[i].siblings = data_tmp;

		val = strtok(NULL, ",");
		pop_data[i].favourite_food = val;

		val = strtok(NULL, ",");
		pop_data[i].birth_timezone = val;

		val = strtok(NULL, ",");
		data_tmp = strtol(val, NULL, 10);
		pop_data[i].birth_timestamp = data_tmp;
		pos += llen + 1;
	}
	pop_data[i].first_name = NULL;
	pop_data[i].last_name = NULL;

	return (pop_data);
}

