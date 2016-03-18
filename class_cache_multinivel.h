//This file is for declaring the functions of 'cCache' class

/***************************************
*	 		Clase cCache			   *
* Autor: JeanCarlos Chavarría Hughes   *
* Curso: Estructuras de Computadores 2 *
*									   *
****************************************/

//! Seccion de includes 
#include <iostream>
#include <string>			
#include <cstdio>		
#include <cstdlib>		
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <fstream>
#include <limits> 
#include <algorithm>
/*! \brief Aqui se definen las bibliotecas que se van a utilizar mediante 'includes'
* Deben ser preferiblemente otros archivos .cpp definidos por el usuario
* en el caso de bibliotecas del sistemas, es mejor incluirlar desde el .cpp
*/

using namespace std;


class cCache                   // begin declaration of the class
//! La clase cCache es una estructura que se encarga de simular la estrutura de un cache.
/*!
\ Comentario
\ Comentario
\ Comentario
*/
{
public:
	
	int miss;
	//! Miembro miss.
/*! \brief Es un int que se encarga de almacenar la cantidad de misses que ha tenido el cache.
*/

	int hit_L1;
	//! Miembro hit.
/*! \brief Se encarga de almacenar el número de hits que ha tenido el cache nivel 1.
*/


	int hit_L2;
	//! Miembro hit.
/*! \brief Se encarga de almacenar el número de hits que ha tenido el cache nivel 2.
*/

	int read_accesses;
	//! Miembro read_accesses.
/*! \brief Se encarga de almacenar el número de accesos a memoria cache que se han realizado en total.
*/

	int hit_latency_L1;
	//! Miembro hit_latency nivel 1.
/*! \brief Se encarga de almacenar el tiempo total que le ha tomado al proceso,
* retornar una palabra de memoria al procesador, tomando en cuenta que hit time = 1ns.
*/


	int hit_latency_L2;
	//! Miembro hit_latency nivel 2
/*! \brief Se encarga de almacenar el tiempo total que le ha tomado al proceso,
* retornar una palabra de memoria al procesador, tomando en cuenta que hit time = 1ns.
*/

	int miss_penalty;
	//! Miembro miss_penalty.
/*! \brief Se encarga de almacenar el tiempo total que le ha tomado al proceso,
* corregir y localizar la palabra buscada, despues de que se produciera un cache miss.
* Tomar en cuenta miss_penalty = (10 + 0.05( TB - 8))ns
*/

public:                   // begin public section
	//Public Member Declarations
	
	string associative_level_st;
	//! Miembro associative_level_st.
/*! \brief Es un string que almacena en forma de texto plano, el tipo de nivel asociativo del cache.
*/

	int block_size;
	//! Miembro block_size.
/*! \brief Es un int que se encarga de almacenar el tamaño del bloque del caché.
*/

	int cache_size_L1;
	//! Miembro cache_size nivel 1.
/*! \brief Es un int que se encarga de almacenar el tamaño de la memoria del cache.
* En buena teoría, esta variable solamente debería contener valores que sean potencia de 2, 
* para definir tamaños como 64KB; 32KB, 16KB, etc.
*/

	int cache_size_L2;
	//! Miembro cache_size nivel 2.
/*! \brief Es un int que se encarga de almacenar el tamaño de la memoria del cache.
* En buena teoría, esta variable solamente debería contener valores que sean potencia de 2, 
* para definir tamaños como 64KB; 32KB, 16KB, etc.
*/

	int block_quantity_L1;
	//! Miembro block_quantity nivel 1.
/*! \brief Es un int que se encarga de almacenar la cantidad de bloques que tiene la memoria cache.
* En realidad, esta variable surge del calculo de cache_size/block_size.
*/

	int block_quantity_L2;
	//! Miembro block_quantity nivel 2.
/*! \brief Es un int que se encarga de almacenar la cantidad de bloques que tiene la memoria cache.
* En realidad, esta variable surge del calculo de cache_size/block_size.
*/

	int index_size_L1;
	//! Miembro index_size nivel 1.
/*! \brief Es un int que se encarga de almacenar el tamano que debe tener el index, el cual esta
* definido por el block_quantity. index = log2(block_quantity)
*/

	int index_size_L2;
	//! Miembro index_size nivel 2.
/*! \brief Es un int que se encarga de almacenar el tamano que debe tener el index, el cual esta
* definido por el block_quantity. index = log2(block_quantity)
*/

	int tag_size_L1;
	//! Miembro tag_size nivel 1.
/*! \brief Es un int que se encarga de almacenar el tamano que debe tener el tag, que por cierto
* se calcula como: block_adress - index_size - byte_offset;
*/

	int tag_size_L2;
	//! Miembro tag_size nivel 2.
/*! \brief Es un int que se encarga de almacenar el tamano que debe tener el tag, que por cierto
* se calcula como: block_adress - index_size - byte_offset;
*/

	int byte_offset;
	//! Miembro byte_offset.
/*! \brief Es un int que se encarga de almacenar el tamano que debe tener el byte offset
* el cual es definido por la cantidad de pablabras que hay en un bloque.
* se supondra que cada palabra es de 1byte. Asi, log2(Tamano_bloque/Tamano_de_palabra) = byte_offset
*/

	int word_size;
	//! Miembro word_size.
/*! \brief Se supondra que el tamano de la palabra es 1B
*/

	int associative_level;
	//! Miembro associative_level.
/*! \brief Se encarga de almacenar el nivel de asociatividad de la memoria, 
* Si es 1, directamente mapeado.
* Si es 0, completamente asociativo.
* Si es 2, asociativo de 2 vías.
* Si es 4, asociativo de 4 vías.
* Por defecto, esta variable debe valer 1.
*/

	float miss_time;
	//! Miembro miss_time.
/*! \brief Es un miembro float que se encarga de resolver la ecuacion 10 + 0.05(TB-8)
*/
	//auto ptr_cache_memory_L1;
	unsigned int **ptr_cache_memory_L1; 
	//! ptr_cache_memory.
/*! \brief Es un puntero doble que se encarga de apuntar a la posición en memoria de la memoria del cache de primer nivel.
*/

	//auto ptr_cache_memory_L2;
	unsigned int **ptr_cache_memory_L2; 
	//! ptr_cache_memory.
/*! \brief Es un puntero doble que se encarga de apuntar a la posición en memoria de la memoria del cache de segundo nivel.
*/

	cCache(int, int , int, int ); 		//contructor
	//! Constructor1 de la clase cCache.
/*! \brief Este constructor recibe tres elementos, el cache_size, block_size, associative_level, como integers.
*/
	//Despues se pueden crear otros constructores alternativos.

	~cCache();				//destructor
	//! Destructor de la clase.
/*! \brief El destructor de la clase se encarga de liberar el espacio de memoria una vez que se elimina la instancia de la clase.
*/

	void read_adress(string );				//metodo que se encarga de buscar en memoria del cache la posicion buscada.
	//! Metodo read_adress.
/*! \brief Este metodo recibe un block_adress en representacion hexadecimal string y busca en memoria
* del cache si a dicha direccion le corresponde un valid bit o no.
* Luego, actualiza la cuenta de los misses y los hits, y los accesos a memoria totales.
*/

	int miss_amount();

	int hit_amount_L1();

	int hit_amount_L2();

	int read_amount();

	float miss_penalty_time();

	int hit_latency_time_L1();

	int hit_latency_time_L2();

	const char* associative_level_description();

	string binary(unsigned int );

	string Convert(unsigned int );

};