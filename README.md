# Multicache_Level_Processor_project
Desarrollar conceptos relacionados a la memoria caché mediante su implementación y simulación en un lenguaje de programación.

UNIVERSIDAD DE COSTA RICA
ESCUELA DE INGENIERÍA ELÉCTRICA
TAREA #2
IE0521 – ESTRUCTURAS DE COMPUTADORES DIGITALES II

I CICLO LECTIVO DEL AÑO 2015

* Propósito de Aprendizaje
Desarrollar conceptos relacionados a la memoria caché mediante su implementación y simulación en un lenguaje de programación.

* Desarrollo de las Tareas
  1. Utilizando el lenguaje C++ desarrolle un programa que simule el comportamiento de una memoria caché multinivel con mapeo directo.
    * Su programa deberá recibir como parámetros por consola el tamaño del caché L1 y el tamaño del caché L2, es decir, su programa deberá poder ser ejecutado con una instrucción similar a: `> ./MiCache <Tamaño Caché L1> <Tamaño Caché L2>`
    * Para simular los accesos a memoria utilice las primeras 10000 líneas del archivo de la tarea anterior.
    * El caché será de inclusión multinivel, es decir, todo lo que está en L1  deberá estar en L2.
    * Recuerde que el nivel L2 siempre es más grande que el nivel L1.
    * En esta tarea se contabilizará retardo y no miss rate.
    * El tamaño de los bloques será de 16bytes.
    * El hit time en el caché L1 es de 1ns.
    * El hit time en el caché L2 es de 5ns.
    * El miss penalty es de 10.4ns.
    * Deben realizar simulaciones de al menos 3 tamaños de caché L1 y 2 tamaños de caché L2 para cada tamaño de caché L1.
    * Deberán entregar el código implementado debidamente documentado y un reporte en formato PDF que deberá incluir:
    * Una explicación de alto nivel (sin detalles profundos) de cómo se realizó la implementación.
    * Tabla(s) que presente(n) los datos recolectados.
    * Gráfica(s) que refleje(n) los resultados obtenidos.
    * Análisis y Discusión de los resultados, incluyendo una comparación con los resultados obtenidos en la segunda parte de la tarea anterior (Realice comparaciones que tengan sentido, es  decir, cachés de iguales condiciones).

* Consideraciones Adicionales
  1. La tarea deberá ser entregada mediante el sitio virtual del curso en la fecha designada ahí mismo.
  2. Deberán entregar un archivo .zip o .tar.gz que tendrá la siguiente estructura:
          o Directorio Principal `<PRIMER APELLIDO>_<PRIMER NOMBRE>`
              -  Directorio de Código `CÓDIGO`
              -  Archivo con el main (*.cpp)
              -  Archivo(s) de subrutinas (*.cpp, *.h)
              -  Makefile, que permita compilar y ejecutar el programa de forma sencilla.
              -  README, que incluya instrucciones de uso del Makefile.
              -  Reporte “<PRIMER APELLIDO>_<PRIMER NOMBRE>.pdf”
  3. Se asume que a este nivel, el estudiante tiene conocimientos de programación en C++ y uso de Makefile, cualquier refrescamiento del lenguaje será responsabilidad del estudiante.
