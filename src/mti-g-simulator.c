/*
 * Simulador de una MTi-G de Xsens
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

#include <time.h>

#include <fcntl.h>
#include <sys/time.h>

#include "garp/mt.h"

long int _timespec2milisecond(struct timespec * timespec)
{
	return (timespec->tv_nsec / 1000000) + (timespec->tv_sec * 1000);
}

int main(int argc, char *argv[]) {
	int fd;
	struct mt_message message;
	unsigned char content[260];
	struct timespec init, end;

	message.content = content;

	memset(content, 0, 260);
	message.type = 0x32;
	message.length = 73;

	fd = open(argv[1], O_WRONLY);

	while(1){
		clock_gettime(CLOCK_REALTIME, &init);
		mt_send(fd, 0xff, &message);
		clock_gettime(CLOCK_REALTIME, &end);

		/* teniendo fe en que esto demorará menos de un segundo */
		end.tv_nsec -= init.tv_nsec;

		nanosleep(&end, NULL);
	}
}