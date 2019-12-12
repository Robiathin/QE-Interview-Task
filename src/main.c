
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extract.h"
#include "extract_csv.h"
#include "extract_json.h"
#include "population_data.h"

int
main(int argc, char *argv[])
{
	population_data_t *pd;
	size_t file_len;
	int fd, status, err;
	char *file_ext, *buffer, *file;

	err = 0;

	if (argc != 2) {
		fprintf(stderr, "Please supply data file as argument.\nUsage: %s <file>\n", argv[0]);
		return (1);
	}

	file = argv[1];
	file_ext = strrchr(argv[1], '.') + 1;
	if (!file_ext) {
		fprintf(stderr, "%s does not have a supported file extension\n", file);
		return (1);
	}

	if (!strcmp(file_ext, "json") || !strcmp(file_ext, "csv")) {
		fd = open(file, O_RDONLY);
		if (!fd) {
			fprintf(stderr, "Could not open %s for reading\n", file);
			return (1);
		}

		/* Check file length by skiping to the end and back */
		file_len = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);

		buffer = malloc(file_len + 1);
		if (buffer == NULL) {
			close(fd);
			return (2);
		}

		status = read(fd, buffer, file_len);
		close(fd);
		if (status == -1) {
			free(buffer);
			fprintf(stderr, "Problem reading from file!\n");
			return (1);
		}

		pd = (!strcmp(file_ext, "json")) ? population_data_from_json(buffer) : population_data_from_csv(buffer);
		if (pd == NULL) {
			free(buffer);
			fprintf(stderr, "Couldn't load data from JSON!\n");
			return (-1);
		}

		err = extract_data(pd);

		/* csv needs special cleanup */
		if (!strcmp(file_ext, "csv"))
			population_data_from_csv_free();
		free(pd);
	} else {
		fprintf(stderr, "%s is not a supported file extension\n", file_ext);
		err = 1;
	}

	return (err);
}

