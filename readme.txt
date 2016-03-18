		*******************************************
	       ****	Universidad de Costa Rica	****
	      *****	Estructuras de Computadoras II	*****
	     ******	JeanCarlos Chavarria Hughes	******
	    ***************************************************
***************************************************************************
***************************************************************************
***************************************************************************

Este directorio corresponde a la primeta parte de la tarea2 del curso, en la cual, mediante el uso de C++ se debe simular una estructura de cache directamente mapeado y de multinivel. La cual debe ser capaz de calcular el correspondiente hit time para cada nivel de cache, y el miss penalty en general, mediante la aceptacion de los dos tamaños de cache. 
.-MiCache <Tamano L1> <Tamano L2>

Para ejecutar el programa, simplemente se debe ejecutar el comando make, y automaticamente se va a realizar:	
	1. La compilación de los .cpp y los headers.
	2. La compilación del main2.cpp
	3. Realizara el link entre el ejecutable y llamará al ejecutable para probar diferentes valores de cache y bloque.
	4. Realizara la creacion de dos carpetas para grabar los resultados obtenidos. 

Se debe tener permisos de creación de carpetas desde el makefile, de lo contrario la operación va a fallar y será necesario crear la carpeta manualmente. ./Resultados/

Debido a que el archivo original de instrucciones es muy pesado, no se hace upload del mismo, es responsabilidad del lector brindar el archivo de lecturas, de la manera ./Instrucciones/aligned.trace

Donde aligned.trace debe ser el nombre del archivo de texto donde esten las instrucciones.

No olvide tener instalado doxygen en el computador, ya que se estan utilizando estas herramientas de doxyfile.

***************************************************************************
***************************************************************************
***************************************************************************
