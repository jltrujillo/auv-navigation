auv-navigation
==============

La solución de control para un vehículo autónomo subacuatico (AUV) por sus
siglas en inglés se puede distribuir en 3 niveles: control, navegación y
supervición. Este proyecto ofrece una aplicación para suplir el nivel táctico
(navegación) dentro de la solución de control.

Requisitos
----------
La aplicación de navegación emplea la librería "libdaemon"
(http://0pointer.de/lennart/projects/libdaemon/) para lograr comportarse como
un demonio. En sistemas Debian y derivados puede instalarla directamente desde
un repositorio de paquetes empleando el comando
"apt-get install libdaemon-dev libdaemon0".