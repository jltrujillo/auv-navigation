/*
 * Procesador de Mensajes de MTi-G
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

#include <assert.h>
#include <fcntl.h>

#include "garp/mti-g.h"

void mti_g_init(struct mti_g * mti_g, config_setting_t * config,
		struct imu * imu_ptr, struct vector3d * gps_ptr)
{
	int err;
	const char * device;

	err = config_setting_lookup_string(config, "device", &device);
	assert(err);

	mti_g->fd = open(device, O_RDONLY);
	assert(mti_g->fd != -1);

	/* Mapear los medios de almacenamiento a utilizar */
	mti_g->imu_ptr = imu_ptr;
	mti_g->gps_ptr = gps_ptr;
}

void mti_g_handle_request(struct mti_g * mti_g_ptr)
{
	return;
}
