
#ifndef _POPULATION_DATA_H_
#define _POPULATION_DATA_H_

typedef struct {
	const char *first_name;
	const char *last_name;
	size_t siblings;
	const char *favourite_food;
	const char *birth_timezone;
	size_t birth_timestamp;
} population_data_t;

#endif /* _POPULATION_DATA_H_ */
