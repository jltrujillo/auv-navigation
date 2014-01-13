/*
 * Servidor de Datos para el HMI Sharksoft.
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
#include <math.h>

#include <fcntl.h>

#include "garp/sharksoft.h"

# define M_PI		3.14159265358979323846	/* pi */

void sharksoft_init(struct sharksoft * sharksoft, config_setting_t * config,
					struct imu * imu_ptr, struct vector3d * gps_ptr)
{
	int err;
	const char * device;

	err = config_setting_lookup_string(config, "device", &device);
	assert(err);

	sharksoft->fd = open(device, O_RDWR);
	assert(sharksoft->fd != -1);

	/* Mapear el buffer de almacenamiento de contenido de mensaje del
	 * protocolo GarpNet. */
	sharksoft->message.content = sharksoft->content;

	sharksoft->imu_ptr = imu_ptr;
	sharksoft->gps_ptr = gps_ptr;
}

void sharksoft_handle_getdata(struct sharksoft * sharksoft)
{
	unsigned char * buffer = sharksoft->content;

	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->acc.x);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->acc.y);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->acc.z);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->gyr.x);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->gyr.y);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->gyr.z);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->mag.x);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->mag.y);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->mag.z);
	buffer = garpnet_float2buffer(buffer, sharksoft->imu_ptr->euler.x);
	buffer = garpnet_float2buffer(buffer, -1 * (sharksoft->imu_ptr->euler.y));
	buffer = garpnet_float2buffer(buffer, (sharksoft->imu_ptr->euler.z) * 180 / M_PI);
	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);

	/* Datos desde el sensor GPS */
	buffer = garpnet_float2buffer(buffer, sharksoft->gps_ptr->x);
	buffer = garpnet_float2buffer(buffer, sharksoft->gps_ptr->y);
	buffer = garpnet_float2buffer(buffer, sharksoft->gps_ptr->z);
	buffer = garpnet_float2buffer(buffer, 0);

	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);

	buffer = garpnet_float2buffer(buffer, 0);
	buffer = garpnet_float2buffer(buffer, 0);

	buffer = garpnet_float2buffer(buffer, 0);

	*buffer = 0;
	buffer++;

	sharksoft->message.type = SHARKSOFT_SETDATA;
	sharksoft->message.length = buffer - sharksoft->content;

	/* TODO Comprobar que la operacion no fallo */
	garpnet_tx(sharksoft->fd, 0, &(sharksoft->message));
}

void sharksoft_handle_request(struct sharksoft * sharksoft)
{
	struct garpnet_message * msg_ptr = &(sharksoft->message);

	if(garpnet_rx(sharksoft->fd, 1, msg_ptr) != -1){
		switch(msg_ptr->type){
		case SHARKSOFT_GETDATA:
			/* Sharksoft HMI data request */
			sharksoft_handle_getdata(sharksoft);
			break;
		default:
			sharksoft->message.type = SHARKSOFT_ACK;
			sharksoft->message.length = 0;

			/* TODO Comprobar que la operacion no fallo */
			garpnet_tx(sharksoft->fd, 0, &(sharksoft->message));
		}
	}
	return;
}
