Acerca del Proyecto auv-navigation
==================================

La solución de control para un vehículo autónomo subacuatico (AUV) por sus
siglas en inglés se puede distribuir en 3 niveles: control, navegación y
supervición. Este proyecto ofrece una aplicación para suplir el nivel táctico
(navegación) dentro de la solución de control.

Ambiente de Ejecución
---------------------
El ambiente de ejecución empleado durante el desarrollo del proyecto (y por
tanto el único realmente soportado) es el sistema operativo Debian ejecutandose
sobre una plataforma compatible con IBM PC. No obstante el objetivo propuesto
en la fase de diseño es ser compatible con el estándar POSIX.1003.

Requisitos
----------
La aplicación de navegación emplea la librería "libdaemon"
(http://0pointer.de/lennart/projects/libdaemon/) para lograr comportarse como
un demonio. En sistemas Debian y derivados puede instalarla directamente desde
un repositorio de paquetes empleando el comando
"apt-get install libdaemon-dev libdaemon0".

Otra librería empleada por la aplicacion de navegación es "libconfig", la cual
es empleada para configurar la aplicacion al inicio. En sistemas Debian y
derivados puede instalarla directamente desde un repositorio de paquetes
empleando el comando "apt-get install libconfig-dev libconfig9".