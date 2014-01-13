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

# Opciones para el compilador del lenguaje C (apegarse al estándard C99,
# mostrar todas las alertas y compilar con facilidades para el eliminador de
# fallas)
AM_CFLAGS = -std=c99 -Wall -Werror

# Opciones para el pre-procesador del compilador del lenguaje C
AM_CPPFLAGS = -I$(top_srcdir)/include 

AM_CPPFLAGS += -I$(top_srcdir)/vendors/mt/include
AM_CPPFLAGS += -I$(top_srcdir)/vendors/garpnet/include

# Lista de productos de tipo librería que se producen en este directorio pero
# que no se van a instalar en el sistema una vez que se invoque la herramienta 
# make con el argumento install.
noinst_LTLIBRARIES = auv-navigation.la

auv_navigation_la_SOURCES = mti-g.c
auv_navigation_la_SOURCES += time-tracker.c
auv_navigation_la_SOURCES += sharksoft.c
auv_navigation_la_LDADD = $(top_builddir)/vendors/mt/lib/libgarpmt.la
auv_navigation_la_LDADD += $(top_builddir)/vendors/garpnet/lib/libgarpnet.la