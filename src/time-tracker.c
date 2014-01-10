/*
 *
 * Derechos Reservados © 2013 GARP y colaboradores
 *
 * Este es un Software Libre; como tal redistribuirlo y/o modificarlo está
 * permitido, siempre y cuando se haga bajo los términos y condiciones de la
 * Licencia Pública General GNU publicada por la Free Software Foundation, ya
 * sea en su versión 2 ó cualquier otra de las posteriores a la misma.
 *
 * Este “Programa” se distribuye con la intención de que sea útil, sin embargo
 * carece de garantía, ni siquiera tiene la garantía implícita de tipo comercial
 * o inherente al propósito del mismo “Programa”. Ver la Licencia Pública
 * General GNU para más detalles.
 *
 * Se debe haber recibido una copia de la Licencia Pública General GNU con este
 * “Programa”, si este no fue el caso, favor de escribir a la Free Software
 * Foundation, Inc., 59 Temple Place – Suite 330, Boston, MA 02111-1307, USA.
 */

#define _POSIX_C_SOURCE 199506L

#include <assert.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <libdaemon/dlog.h>

#include "garp/time-tracker.h"

void time_tracker_init(struct time_tracker * tracker, config_setting_t * config) {
	int err;
	const char * file;

	err = config_setting_lookup_string(config, "file", &file);
	assert(err);

	tracker->file = fopen(file, "w");

	err = config_setting_lookup_int(config, "num_items", &(tracker->num_items));
	assert(err);

	tracker->current_item = 0;
	tracker->items = malloc(sizeof(struct timespec) * (tracker->num_items));
	assert(tracker->items != NULL);

	tracker->items_string = malloc(30 * tracker->num_items);
	assert(tracker->items_string != NULL);
}

void time_tracker_dispose(struct time_tracker * tracker) {
	fclose(tracker->file);
	free(tracker->items);
}

long int _time_tracker_timespec2milisecond(struct timespec * timespec)
{
	return (timespec->tv_nsec / 100000) + (timespec->tv_sec * 10000);
}

int _time_tracker_serialize(struct time_tracker * tracker) {
	int length, total = 0;

	for (int i = 0; i < (tracker->num_items); i++) {

		length = sprintf((tracker->items_string + total), "%ld\n",
				_time_tracker_timespec2milisecond(tracker->items + i));
		total += length;
	}

	return total;
}

void time_tracker_handle(struct time_tracker * tracker) {
	int result;

	clock_gettime(CLOCK_REALTIME, (tracker->items + tracker->current_item));

	++(tracker->current_item);

	if ((tracker->current_item) == (tracker->num_items)) {
		_time_tracker_serialize(tracker);

		result = fputs(tracker->items_string, tracker->file);
		assert(result != -1);

		tracker->current_item = 0;
	}
}
