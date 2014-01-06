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

if HAVE_DOXYGEN

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_builddir)/doc/api

endif