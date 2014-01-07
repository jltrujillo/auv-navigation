/*
 * Punto de entrada de la aplicacion de navegacion
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

#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/unistd.h>
#include <sys/select.h>

#include <libdaemon/dfork.h>
#include <libdaemon/dsignal.h>
#include <libdaemon/dlog.h>
#include <libdaemon/dpid.h>
#include <libdaemon/dexec.h>

#include <libconfig.h>

#include "garp/mti-g.h"

const char * CONFIG_FILE = "./etc/auv-navigation.cfg";

/** Punto de entrada de la aplicacion de navegacion.
 * @return Estado de la aplicacion al terminar.
 */
int main(int argc, char *argv[]) {
	pid_t pid;

	/* Reset signal handlers */
	if (daemon_reset_sigs(-1) < 0) {
		daemon_log(LOG_ERR, "Failed to reset all signal handlers: %s",
				strerror(errno));
		return 1;
	}

	/* Unblock signals */
	if (daemon_unblock_sigs(-1) < 0) {
		daemon_log(LOG_ERR, "Failed to unblock all signals: %s",
				strerror(errno));
		return 1;
	}

	/* Set indetification string for the daemon for both syslog and PID file */
	daemon_pid_file_ident = daemon_log_ident = daemon_ident_from_argv0(argv[0]);

	/* Check if we are called with -k parameter */
	if (argc >= 2 && !strcmp(argv[1], "-k")) {
		int ret;

		/* Kill daemon with SIGTERM */

		/* Check if the new function daemon_pid_file_kill_wait() is available, if it is, use it. */
		if ((ret = daemon_pid_file_kill_wait(SIGTERM, 5)) < 0)
			daemon_log(LOG_WARNING, "Failed to kill daemon: %s",
					strerror(errno));

		return ret < 0 ? 1 : 0;
	}

	/* Check that the daemon is not rung twice a the same time */
	if ((pid = daemon_pid_file_is_running()) >= 0) {
		daemon_log(LOG_ERR, "Daemon already running on PID file %u", pid);
		return 1;
	}

	/* Prepare for return value passing from the initialization procedure of the daemon process */
	if (daemon_retval_init() < 0) {
		daemon_log(LOG_ERR, "Failed to create pipe.");
		return 1;
	}

	/* Do the fork */
	if ((pid = daemon_fork()) < 0) {

		/* Exit on error */
		daemon_retval_done();
		return 1;

	} else if (pid) { /* The parent */
		int ret;

		/* Wait for 20 seconds for the return value passed from the daemon process */
		if ((ret = daemon_retval_wait(20)) < 0) {
			daemon_log(LOG_ERR,
					"Could not recieve return value from daemon process: %s",
					strerror(errno));
			return 255;
		}

		daemon_log(ret != 0 ? LOG_ERR : LOG_INFO,
				"Daemon returned %i as return value.", ret);
		return ret;

	} else { /* The daemon */
		int fd, quit = 0;
		fd_set fds;

		config_t cfg;
		config_setting_t *setting;

		/* Controlador de estado de la MTi-G */
		struct mti_g mti_g;

		/* Close FDs */
		if (daemon_close_all(-1) < 0) {
			daemon_log(LOG_ERR, "Failed to close all file descriptors: %s",
					strerror(errno));

			/* Send the error condition to the parent process */
			daemon_retval_send(1);
			goto finish;
		}

		/* Create the PID file */
		if (daemon_pid_file_create() < 0) {
			daemon_log(LOG_ERR, "Could not create PID file (%s).",
					strerror(errno));
			daemon_retval_send(2);
			goto finish;
		}

		/* Initialize signal handling */
		if (daemon_signal_init(SIGINT, SIGTERM, SIGQUIT, SIGHUP, 0) < 0) {
			daemon_log(LOG_ERR, "Could not register signal handlers (%s).",
					strerror(errno));
			daemon_retval_send(3);
			goto finish;
		}

		/*... do some further init work here */

		/* cargar la configuración de la aplicación */
		config_init(&cfg);

		/* Read the file. If there is an error, report it and exit. */
		if(! config_read_file(&cfg, CONFIG_FILE))
		{
			daemon_log(LOG_ERR, "%s:%d - %s\n", config_error_file(&cfg),
				config_error_line(&cfg), config_error_text(&cfg));
			daemon_retval_send(EXIT_FAILURE);
			goto finish;
		}

		/* inicializar el controlador de estado de la MTi-G */
		setting = config_lookup(&cfg, "mti_g");
		mti_g_init(setting, &mti_g);

		/* Send OK to parent process */
		daemon_retval_send(0);

		daemon_log(LOG_INFO, "Sucessfully started");

		/* Prepare for select() on the signals */
		FD_ZERO(&fds);
		fd = daemon_signal_fd();
		FD_SET(fd, &fds);

		FD_SET(mti_g.fd, &fds);

		while (!quit) {
			fd_set fds2 = fds;

			/* Wait for an incoming signal */
			if (select(FD_SETSIZE, &fds2, 0, 0, 0) < 0) {

				/* If we've been interrupted by an incoming signal, continue */
				if (errno == EINTR)
					continue;

				daemon_log(LOG_ERR, "select(): %s", strerror(errno));
				break;
			}

			/* Check if a signal has been recieved */
			if (FD_ISSET(fd, &fds2)) {
				int sig;

				/* Get signal */
				if ((sig = daemon_signal_next()) <= 0) {
					daemon_log(LOG_ERR, "daemon_signal_next() failed: %s",
							strerror(errno));
					break;
				}

				/* Dispatch signal */
				switch (sig) {

				case SIGINT:
				case SIGQUIT:
				case SIGTERM:
					daemon_log(LOG_WARNING, "Got SIGINT, SIGQUIT or SIGTERM.");
					quit = 1;
					break;

				case SIGHUP:
					daemon_log(LOG_INFO, "Got a HUP");
					daemon_exec("/", NULL, "/bin/ls", "ls", (char*) NULL);
					break;

				}
			}

			/* Procesar señales desde la MTi-G */
			if (FD_ISSET(mti_g.fd, &fds2)) {
				mti_g_handle_request(&mti_g);
			}
		}

		config_destroy(&cfg);

		/* Do a cleanup */
		finish: daemon_log(LOG_INFO, "Exiting...");
		daemon_retval_send(255);
		daemon_signal_done();
		daemon_pid_file_remove();

		return 0;
	}
}
