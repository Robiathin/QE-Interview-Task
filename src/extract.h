
#ifndef _EXTRACT_H_
#define _EXTRACT_H_

#include "population_data.h"

typedef struct {
	const char *month_name;
	size_t count;
} birthday_data_t;

typedef struct {
	const char *food_name;
	size_t count;
} food_data_t;

birthday_data_t	*extract_birthday_month_count(population_data_t *);
food_data_t	*extract_food_data(population_data_t *);
size_t		 extract_average_siblings(population_data_t *);
int		 extract_data(population_data_t *);

#endif /* _EXTRACT_H_ */
