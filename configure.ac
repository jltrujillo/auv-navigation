###############################################################################
## Derechos Reservados © 2013 GARP y colaboradores
##
## Este es un Software Libre; como tal redistribuirlo y/o modificarlo está
## permitido, siempre y cuando se haga bajo los términos y condiciones de la
## Licencia Pública General GNU publicada por la Free Software Foundation, ya
## sea en su versión 2 ó cualquier otra de las posteriores a la misma.
##
## Este “Programa” se distribuye con la intención de que sea útil, sin embargo
## carece de garantía, ni siquiera tiene la garantía implícita de tipo comercial
## o inherente al propósito del mismo “Programa”. Ver la Licencia Pública
## General GNU para más detalles.
##
## Se debe haber recibido una copia de la Licencia Pública General GNU con este
## “Programa”, si este no fue el caso, favor de escribir a la Free Software
## Foundation, Inc., 59 Temple Place – Suite 330, Boston, MA 02111-1307, USA.
###############################################################################

# Establece el nombre del paquete y su versión. Estos típicamente son usados
# para soportar la opción --version de la herramienta configure. El argumento
# opcional bug-report es la dirección de correo electrónico a la que deben
# enviarse los reportes de fallas.
AC_INIT([auv-navigation], [0.1], [yeiniel@uclv.cu])

# Indica que se emplee las herramientas auxiliares (ejemplo: install-sh,
# config.sub, config.guess, etc.) que se localizan en el directorio ./build-aux
# relativo al directorio del proyecto.
AC_CONFIG_AUX_DIR([build-aux])

# Especifica el directorio ./m4 relativo al directorio del proyecto como la
# localización de las macros locales de Autconf.
AC_CONFIG_MACRO_DIR([m4])

# Ejecuta todas las macros requeridas para la correcta operacion de los
# ficheros Makefile generados por el sistema de construcción.
AM_INIT_AUTOMAKE([foreign 1.6 -Wall -Werror])

# Selecciona un compilador de C para ser empleado en el proceso de construcción
# del proyecto. Si la variable de ambiente CC no se ha establecido, chequea
# si se encuentra instalado gcc (Compilador de C de GNU), a continuación cc
# (compilador de C de sistemas UNIX) y luego otros compiladores. Establece como
# valor de la variable de salida CC el compilador encontrado.
AC_PROG_CC

# Esta macro adiciona una serie de nuevos chequeos al fichero ejecutable de
# configuración de forma tal que el fichero ejecutable libtool generado pueda
# entender las caracteristicas de la maquina que hospeda el proceso de
# construcción. Adicionalmente agrega soporte para las opciones
# --enable-shared y --disable-shared de la herramienta de configuracion del
# sistema de construcción.
AC_PROG_LIBTOOL

LT_INIT

# Prueba si la librería "daemon" está disponible.
AC_CHECK_LIB([daemon], [daemon_pid_file_kill_wait],,
	AC_MSG_ERROR([Error: libdaemon no esta disponible en esta plataforma.]))
	
# Prueba si la librería "config" está disponible.
AC_CHECK_LIB([config], [config_read_file],,
	AC_MSG_ERROR([Error: libconfig no esta disponible en esta plataforma.]))

AC_CHECK_HEADERS([libdaemon/dfork.h libdaemon/dsignal.h libdaemon/dlog.h libdaemon/dpid.h libdaemon/dexec.h],,
	AC_MSG_ERROR([Error: ficheros de cabecera de libdaemon no estan disponibles en esta plataforma.]))

AC_CHECK_HEADERS([libconfig.h],,
	AC_MSG_ERROR([Error: ficheros de cabecera de libconfig no estan disponibles en esta plataforma.]))

# Checkea si el programa doxygen se encuentra en un directorio accesible
# (que este registrado en la variable de entorno PATH). Si se encuentra
# establece el valor de la variable DOXYGEN a el nombre completo del programa.
AC_CHECK_PROGS([DOXYGEN], [doxygen],
    AC_MSG_WARN([la herramienta Doxygen no ha sido encontrada - continuando sin ella]))

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doc/Doxyfile])])

# Hace que la macro AC_OUTPUT genere cada fichero en la lista al copiar el
# fichero plantilla (por defecto, un fichero con el mismo nombre y extensión
# .in) y sustituir las variables de salida de la herramienta de configuración.
AC_CONFIG_FILES([Makefile include/Makefile src/Makefile doc/Makefile])

# Genera la herramienta de la linea de comandos config.status y lo ejecuta.
AC_OUTPUT