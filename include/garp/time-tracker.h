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

#ifndef _GARP_TIME_TRACKER_H_
#define _GARP_TIME_TRACKER_H_

#include <stdio.h>

#include <sys/time.h>

#include <libconfig.h>

struct time_tracker {
	FILE * file;

	int num_items;
	int current_item;

	struct timespec * items;
	char * items_string;
};

void time_tracker_init(struct time_tracker * tracker, config_setting_t * config);
void time_tracker_dispose(struct time_tracker * tracker);
void time_tracker_handle(struct time_tracker * tracker);

#endif /* _GARP_TIME_TRACKER_H_ */
