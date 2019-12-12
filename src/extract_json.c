
#include <json.h>

#include "population_data.h"

#include "extract_json.h"

population_data_t *
population_data_from_json(char *buffer)
{
	population_data_t *pop_data;
	struct json_object *jobj, *tmp_obj;
	size_t obj_data_tmp, i;
	int val_type;

	jobj = json_tokener_parse(buffer);
	val_type = json_object_get_type(jobj);
	if (val_type != json_type_array)
		return (NULL);

	pop_data = calloc(json_object_array_length(jobj) + 2, sizeof(population_data_t));
	if (pop_data == NULL)
		return (NULL);

	for (i = 0; i < json_object_array_length(jobj); i++) {
		tmp_obj = json_object_array_get_idx(jobj, i);
		pop_data[i].first_name = json_object_get_string(json_object_object_get(tmp_obj, "first_name"));
		pop_data[i].last_name = json_object_get_string(json_object_object_get(tmp_obj, "last_name"));
		obj_data_tmp = strtol(json_object_get_string(json_object_object_get(tmp_obj, "siblings")), NULL, 10);
		pop_data[i].siblings = obj_data_tmp;
		pop_data[i].favourite_food = json_object_get_string(json_object_object_get(tmp_obj, "favourite_food"));
		pop_data[i].birth_timezone = json_object_get_string(json_object_object_get(tmp_obj, "birth_timezone"));
		obj_data_tmp = strtol(json_object_get_string(json_object_object_get(tmp_obj, "birth_timestamp")), NULL, 10);
		pop_data[i].birth_timestamp = obj_data_tmp;
	}

	/* append a NULL named data point for later iteration */
	pop_data[i].first_name = NULL;
	pop_data[i].last_name = NULL;
	pop_data[i].siblings = 0;

	return (pop_data);
}

