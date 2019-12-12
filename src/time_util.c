
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time_util.h"

struct tm *
timestamp_tz_to_tm(time_t ts, const char *tz)
{
	struct tm *tm, *tm_cpy;
	char *tz_str;

	ts /= 1000; /* All the timestamps are milliseconds and C uses seconds... */

	/* Each localtime(3) call overwrites the data the pointer points to. Make a copy of it */
	tm_cpy = malloc(sizeof(struct tm));
	if (tm_cpy == NULL)
		return (NULL);

	/* Prepend UTC to the timezone */
	asprintf(&tz_str, "UTC%s", tz);
	if (tz_str == NULL) {
		free(tm_cpy);
		return (NULL);
	}

	/* The sign needs to be flipped for the TZ variable for POSIX reasons */
	tz_str[3] = tz_str[3] == '-' ? '+' : '-';

	/* The TZ ENV thing is a little bit of a hack but because this is the only use of time.h things
	 * in the program, and it is only editing a local environment variable, it is without concequence
	 */
        setenv("TZ", tz_str, 1);
	tm = localtime(&ts);
	memcpy(tm_cpy, tm, sizeof(struct tm));

	free(tz_str);

	return (tm_cpy);
}
