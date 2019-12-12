
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "extract.h"
#include "population_data.h"
#include "time_util.h"

birthday_data_t *
extract_birthday_month_count(population_data_t *data)
{
	/* Static so it isn't allocated on stack memory and a pointer can be returned */
	static birthday_data_t birthday_data[] = {
		{ "January", 0 },
		{ "February", 0 },
		{ "March", 0 },
		{ "April", 0 },
		{ "May", 0 },
		{ "June", 0 },
		{ "July", 0 },
		{ "August", 0 },
		{ "September", 0 },
		{ "October", 0 },
		{ "November", 0 },
		{ "December", 0 }
	};
	struct tm *bday;
	size_t i;

	for (i = 0; data[i].first_name != NULL; i++) {
		bday = timestamp_tz_to_tm((time_t)data[i].birth_timestamp, data[i].birth_timezone);
		if (bday == NULL) {
			fprintf(stderr, "Error finding birthday!\n");
			return (NULL);
		}
		birthday_data[bday->tm_mon].count++;
		free(bday);
	}

	return ((birthday_data_t *)birthday_data);
}

food_data_t *
extract_food_data(population_data_t *data)
{
	food_data_t *food_data;
	size_t i, j, current_size;
	int food_found;

	food_found = 0;
	current_size = 256;
	food_data = calloc(current_size, sizeof(food_data_t));
	if (food_data == NULL)
		return (NULL);

	for (i = 0; data[i].first_name != NULL; i++) {
		food_found = 0;
		for (j = 0; food_data[j].food_name != NULL; j++)
			if (!strcasecmp(data[i].favourite_food, food_data[j].food_name)) {
				food_data[j].count++;
				food_found = 1;
			}
		if (!food_found) {
			if (j == current_size - 1) { /* resize the buffer if needed */
				food_data = realloc(food_data, (current_size + 256) * sizeof(food_data_t));
				if (food_data == NULL)
					return (NULL);
			}
			food_data[j].food_name = data[i].favourite_food;
			food_data[j].count = 1;
		}
	}
	return (food_data);
}

size_t
extract_average_siblings(population_data_t *data)
{
	size_t siblings_total, i;

	siblings_total = 0;
	for (i = 0; data[i].first_name != NULL; i++)
		siblings_total += data[i].siblings;
	siblings_total = (size_t)ceil((double)siblings_total / (double)i); /* Round up as per README.md */	

	return (siblings_total);
}

int
extract_data(population_data_t *data)
{
	birthday_data_t *birthday_data;
	food_data_t *food_data;

	printf("Average siblings: %ld\n", extract_average_siblings(data));

	food_data = extract_food_data(data);
	if (food_data == NULL) {
		fprintf(stderr, "Error retrieving food data\n");
		return (1);
	}
	puts("Favourite foods:");
	for (size_t i = 0; food_data[i].food_name != NULL; i++)
		printf("- %s: %ld\n", food_data[i].food_name, food_data[i].count);
	free(food_data);

	birthday_data = extract_birthday_month_count(data);
	if (birthday_data == NULL) {
		fprintf(stderr, "Error retrieving birthday data\n");
		return (1);
	}
	puts("Births per Month:");
	for (size_t i = 0; i < 12; i++)
		printf("- %s: %ld\n", birthday_data[i].month_name, birthday_data[i].count);

	return (0);
}
