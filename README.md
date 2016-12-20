# CDB2OSG
Visualization tool to navigate [Common Database (CDB)](http://www.presagis.com/products_services/standards/cdb/) databases using [OpenSceneGraph(OSG)](http://www.openscenegraph.org/).

Supports:
  * Primary Terrain Elevation datasets.
  * Yearly Terrain Imagery datasets.
  * Dynamic level of detail changes.

# Ejecución
Ejecutar:
    
    > ./CDB2OSG [path a la base de datos] [nombre de la base datos] [geoceldas a cargar]
    
donde:
  * `[path a la base de datos]` es la ruta a la carpeta donde está ubicada la base de datos CDB.
  * `[nombre de la base de datos]` es el nombre de la carpeta raíz de la base de datos CDB.
  * `[geoceldas a cargar]` es una lista de las geoceldas a cargar con formato `N33W117` o `S12E116` separados por `:`. Ejemplo: `N33W117:S12E116`. 
  
## Configuración del entorno

### Windows

  1. Instalar el compilador
    1. Instalar MinGW Intallation Manager.
    1. Seleccionar en MinGW Istallation Manager los paquetes:
      * mingw-developer-toolkit
      * mingw32-base
      * mingw32-gcc-g++
      * msys-base
    1. Instalarlos desde `Installation` -> `Apply changes`  
    1. Agregar al `PATH` del sistema el directorio `C:/MinGW/bin`
    
  1. Instalar MSys
    1. Instalar [MSys](http://www.mingw.org/wiki/MSYS). 
    1. Indicar ubicación de MinGW, ingresar `C:/minGW`.
  
  1. Compilar la librería [GDAL](http://www.gdal.org/) (utilizada por OSG para leer archivos GeoTiff, el formato especificado por CDB para la capa de datos de elevación).
    1. [Descargar la librería GDAL](http://trac.osgeo.org/gdal/wiki/DownloadSource) en `C:/msys/1.0/home/[USER]/`
    1. Iniciar una consola MSYS, pararse en el root de la carpeta descomprimida de gdal.
    1. Ejecutar la secuencia:
      * `./configure`
      * `make` (puede demorar unas horas)
      * `make install`
    1. La librería GDAL (`libgdal-1.dll`) compilada se encuentra en `C:\msys\1.0\local\bin`.
    1. Agregar al `PATH` del sistema `C:\msys\1.0\local\bin` y `C:\msys\1.0\local\lib`.
    
  1. Compilar la librería [Jasper](https://www.ece.uvic.ca/~frodo/jasper/) (usada por OSG para leer archivos .jp2, el formato que especifica CDB para la capa de imágenes satelitales).
    1. [Descargar la librería Jasper](https://www.ece.uvic.ca/~frodo/jasper/#download)  y descomprimirla en `C:/msys/1.0/home/[USER]/`
    1. Iniciar una consola MSYS, pararse en el root de la carpeta descomprimida de jasper.
    1. Ejecutar la secuencia:
      * `./configure`
      * `make`
      * `make install`
    1. Si falla el make por una referencia indefinida a la system call `sleep`, modificar la llamada `sleep(1)` en `jasper-1.900.1\src\appl\tmrdemo.c:46` por `_sleep(1)`.
    1. La librería Jasper (`libjasper.a`) compilada se encuentra en `C:\msys\1.0\local\lib`.
    1. Agregar al `PATH` del sistema `C:\msys\1.0\local\bin` y `C:\msys\1.0\local\lib` (ya debería haberse hecho al compilar GDAL).
  
  1. Instalar el sistema de compilación [CMake](https://cmake.org/).
  1. Instalar el [IDE Eclipse](https://eclipse.org).
    1. [Descargar el IDE](https://eclipse.org/downloads/) y descomprimir.
  1. Compilar `OSG`.
    1. [Descargar OSG](http://www.openscenegraph.org/index.php/download-section/stable-releases) y descomprimir.
    1. Abrir `Cmake` e indicar el directorio donde se descomprimió OSG.
    1. Indicar el mismo directorio como destino de los binarios compilados.
    1. Definir los siguientes valores para las variables del cmake de OSG:
      * `GDAL_INCLUDE_DIR = C:/msys/1.0/local/include`
      * `GDAL_LIBRARY = C:/msys/1.0/local/bin/libgdal-1.dll`
      * `JASPER_INCLUDE_DIR = C:/msys/1.0/local/include`
      * `JASPER_LIBRARY= C:/msys/1.0/local/lib/libjasper.a`
    1. Configurar (`Configure`), 
    1. Generar (`Generate`) usando algún generador para Makefiles MinGw para Eclipse.
    1. En el directorio de OSG deben aparecer los archivos de eclipse `.project` y `.cproject` así como algunos Makefiles.
    1. Abrir el `IDE Eclipse` e importar (`File` -> `Import` -> `Existings Projects into Workspace`) indicando el directorio de OSG (donde está el `.project` generado por `CMake`)
    1. Compilar (puede tardar unas horas)
    1. En la carpeta `/bin` deberían estar los `.exe` y `.dll` de OSG compilados. Verificar la existencia de `mingw_osgdb_gdal.dll` y `mingw_osgdb_jp2.dll` en `/bin/osgPlugins-3.2.1/`.
    1. Agregar al `PATH` del sistema el path completo a `/OSG/bin`.
  1. Compilar CDB2OSG.
    1. [Clonar](git@github.com:llinardos/CDB2OSG.git) o [descargar](https://github.com/llinardos/CDB2OSG/archive/master.zip) este repositorio.
    1. Desde el `IDE` crear un proyecto nuevo apuntando al `CDB2OSG`.
    1. En las propiedades del proyecto (`C++` -> `Settings`) indicar:
      * los siguientes paths de inclusión:
        * `[Source directory]/include` del proyecto OSG 
        * `/include` del proyecto OSG
      * las siguientes librerías con las que linkear: 
        * osg
        * osgUtil
        * OpenThreads
        * osgSim
        * osgViewer
        * osgTerrain
        * osgDB
        * osgGA 
      * el siguiente path donde buscar las librerías con las que linkear:
        * `/bin` del proyecto OSG
    1. Descargar la base de datos CDB de ejemplo de Presagis.
    1. Compilar y correr.
    1. Si hay algún problema se puede setear la variable `OSG_NOTIFY_LEVEL` con valor `DEBUG` desde `Run` -> `Run configurations` -> `Environment` en eclipse para que notifique si no puede encontrar alguna librería.
  1. [Ejecutar](#ejecución) 
   
