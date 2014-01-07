/*
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

#ifndef _GARP_MTI_G_H_
#define _GARP_MTI_G_H_

#include <libconfig.h>

#include "garp/imu.h"
#include "garp/vector3d.h"

/*! Controlador de estado de la MTi-G.
 */
struct mti_g {
	/*! Descriptor de fichero asociado a la MTi-G. */
	int fd;

	struct imu * imu_ptr;
	struct vector3d * gps_ptr;
};

/*! Inicializa el controlador de estado de la MTi-G a partir de configuración.
 *
 * @param config Puntero al elemento de configuración empleado.
 * @param mti_g Puntero al controlador de estado de la MTi-G a inicializar.
 */
void mti_g_init(config_setting_t * config, struct mti_g * mti_g);

/*! Procesa un pedido realizado por una MTi-G
 *
 * @param mti_g_ptr Puntero al controlador de estado de la MTi-G.
 */
void mti_g_handle_request(struct mti_g * mti_g_ptr);

#endif /* _GARP_MTI_G_H_ */
