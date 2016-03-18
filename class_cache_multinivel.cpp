//This file is for defining the functions of 'cCache' class

/***************************************
*	 		Clase cCache			   *
* Autor: JeanCarlos Chavarría Hughes   *
* Curso: Estructuras de Computadores 2 *
*									   *
****************************************/


//! Seccion de includes 
#include "class_cache_multinivel.h"
/*! \brief Aqui se definen las bibliotecas que se van a utilizar mediante 'includes'
* Deben ser preferiblemente otros archivos .cpp definidos por el usuario
* en el caso de bibliotecas del sistemas, es mejor incluirlar desde el .cpp
*/

using namespace std;

//Code Body
cCache::cCache(int cache_size_L1,int cache_size_L2, int block_size, int associative_level){
	float module1, module2; //Stores the result of cache_size mod block_size
	module1 = cache_size_L1%block_size;
	module2 = cache_size_L2%block_size;
	//throws section
	if (module1 != 0)
	{
		throw std::invalid_argument("cache_size_L1 module block_size must be 0");
	}
	if (cache_size_L1<0 || block_size < 0)
	{
		throw std::invalid_argument("the argument cannot be negative");
	}
	if ((cache_size_L1%2)!=0)
	{
		throw std::invalid_argument("cache_size_L1 must be a power of 2, it cannot be %d,cache_size");
	}
	if (module2 != 0)
	{
		throw std::invalid_argument("cache_size_L2 module block_size must be 0");
	}
	if (cache_size_L2<0 || block_size < 0)
	{
		throw std::invalid_argument("the argument cannot be negative");
	}
	if ((cache_size_L2%2)!=0)
	{
		throw std::invalid_argument("cache_size_L1 must be a power of 2, it cannot be %d,cache_size");
	}
	//initialization of the cache variables
	this -> block_quantity_L1 = cache_size_L1/block_size;
	this -> block_quantity_L2 = cache_size_L2/block_size;
	this -> word_size = 1; //Se supondra que cada palabra es de 1B.
	this -> cache_size_L1 = cache_size_L1;
	this -> cache_size_L2 = cache_size_L2;
	this -> block_size = block_size;
	if (associative_level != 0)
	{
		this -> index_size_L1 = log2(block_quantity_L1); //si falla, pruebe como double.
		this -> index_size_L2 = log2(block_quantity_L2); //si falla, pruebe como double.
	} else{
		this -> index_size_L1 = 0; //en full asociative no hay index.
		this -> index_size_L2 = 0; //en full asociative no hay index.
	}
	if (associative_level == 2)
	{
		this -> index_size_L1 = this -> index_size_L1 -1; //Si es de dos vias, entonces cada bloque se divide en dos, osea -1 bit.
		this -> index_size_L2 = this -> index_size_L2 -1; //Si es de dos vias, entonces cada bloque se divide en dos, osea -1 bit.
	}
	this -> byte_offset = log2(block_size/word_size); //si falla, pruebe como double.
	this -> tag_size_L1 = 32 - this-> index_size_L1 - this -> byte_offset; //Se supondra que las direccion son de 32bits
	this -> tag_size_L2 = 32 - this-> index_size_L2 - this -> byte_offset; //Se supondra que las direccion son de 32bits
	this -> read_accesses = 0;
	this -> miss = 0;
	this -> hit_L1 = 0;
	this -> hit_L2 = 0;
	this -> miss_penalty = 0.0f;
	this -> hit_latency_L1 = 0; 
	this -> hit_latency_L2 = 0; 
	//this -> miss_time = 10 + 0.05*(block_size - 8); //Segun la formula del enunciado 
	this -> miss_time = 10.4f;
	this -> associative_level = associative_level;

	if (associative_level == 1)
	{
		this -> associative_level_st = "Directamente Mapeado";
	}
	if (associative_level == 0)
	{
		this -> associative_level_st = "Completamente asociativo";
	}
	if (associative_level == 2)
	{
		this -> associative_level_st = "2-way: Associativo de 2 vias";
	}
	//initialization of the cache memory as an array
	const int cols = 2; //each memory position only need to handle adress and valid bit.
	const int rows_L1 = cache_size_L1/block_size; 
	const int rows_L2 = cache_size_L2/block_size; 
	
	//this -> ptr_cache_memory = new int*[rows]; //the array is initialized
	this -> ptr_cache_memory_L1 = new unsigned int*[rows_L1]; //the array is initialized
	for(int i = 0; i < rows_L1; ++i)
    	this -> ptr_cache_memory_L1[i] = new unsigned int[cols];	
	
	for (int i = 0; i < rows_L1; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			this -> ptr_cache_memory_L1[i][j] = 0;
		}
		//ptr_cache_memory[i] = content;
	}
	//This for is for assigning adress and valid bit to every block position in the cache memory

	//this -> ptr_cache_memory = new int*[rows]; //the array is initialized
	this -> ptr_cache_memory_L2 = new unsigned int*[rows_L2]; //the array is initialized
	for(int i = 0; i < rows_L2; ++i)
    	this -> ptr_cache_memory_L2[i] = new unsigned int[cols];	
	
	for (int i = 0; i < rows_L2; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			this -> ptr_cache_memory_L2[i][j] = 0;
		}
		//ptr_cache_memory[i] = content;
	}
}

cCache::~cCache(){
	int rows = cache_size_L1/block_size; //i.e. cache_size = 64KB, block_size=64B, 64Bx1000 = 64KB, there is 1000 blocks in the cache
	for(int i = 0; i < rows; ++i) {
    	delete [] this -> ptr_cache_memory_L1[i];
	}
	delete [] this -> ptr_cache_memory_L1;

	rows = cache_size_L2/block_size; //i.e. cache_size = 64KB, block_size=64B, 64Bx1000 = 64KB, there is 1000 blocks in the cache
	for(int i = 0; i < rows; ++i) {
    	delete [] this -> ptr_cache_memory_L2[i];
	}
	delete [] this -> ptr_cache_memory_L2;
}
//! Destructor de la clase.
/*! \brief El destructor principal de la clase cCache  se encarga de liberar el espacio cuando
* se elimina una instancia de este tipo.
*/

//Se supone que cada palabra es de 1Byte, asi el byte offset depende de cuantas palabras se pueden almacenar en un bloque
void cCache::read_adress(string block_adress){
	//Una de las tareas que me queda pendiente es pasar todos los calculos de hexadecimal a binario
	//Pero eso solo si en una de las otras tareas lo requiero. Aqui lo ocupa para 2way
	//string block_adress_index;
	string block_adress_index_bits_L1;
	string block_adress_index_bits_L2;
	//string block_adress_tag;
	string block_adress_tag_bits_L1;
	string block_adress_tag_bits_L2;
	//string block_adress_byte_offset;
	string block_adress_byte_offset_bits;
	//string block_adress_set;
	string block_adress_bits;
	//string block_adress_tag_sets_bits;
	
	unsigned int block_adress_int = strtoul(block_adress.c_str(), NULL, 16);	
	//block_adress_bits = binary(block_adress_int);
	block_adress_bits = Convert(block_adress_int);
	int const size_block_adress_bits = block_adress_bits.length();

	//size_t size_block_adress = block_adress.length(); //Por defecto deberia ser 8x4 = 32bits
	int const size_block_adress = block_adress.length(); //Por defecto deberia ser 8x4 = 32bits //Recuerde que esta en bytes
	//el index y el byte offset se debe dividir entre 4, porque por cada letra hexadecimal, se tienen 4 bits
	//int const colLeft = size_block_adress - (this-> index_size)/4 - (this-> byte_offset)/4;
	int const colLeft_bits_L1 = size_block_adress_bits - this-> index_size_L1 - this-> byte_offset;
	int const colLeft_bits_L2 = size_block_adress_bits - this-> index_size_L2 - this-> byte_offset;
	//int const colRight = size_block_adress - this-> byte_offset/4;
	int const colRight_bits = size_block_adress_bits - this-> byte_offset;
	
	int set_size;
	if (this -> associative_level != 0 )
	{
		set_size = log2(this -> associative_level);
	} else
	{
		set_size = 0;
	}
	//const int colSet_bit = sizeblock_adress_tag_sets_bits_block_adress_bits - set_size - this-> byte_offset; //SUPONIENDO QUE BYTE OFFSET SIEMPRE ES 1B.
	//block_adress_set = block_adress_bits.substr(colSet_bit,set_size); 
	//unsigned int tag_sets = 32 - set_size - this-> byte_offset; //Esta malo
	unsigned int tag_sets = 32 - this-> index_size_L1 - this-> byte_offset; //Esta bueno 30 marzo, no es para multinivel
	//block_adress_index = block_adress.substr(colLeft,(this-> index_size)/4);
	block_adress_index_bits_L1 = block_adress_bits.substr(colLeft_bits_L1,(this-> index_size_L1));
	block_adress_index_bits_L2 = block_adress_bits.substr(colLeft_bits_L2,(this-> index_size_L2));
	//block_adress_tag = block_adress.substr(0,(this-> tag_size)/4);
	block_adress_tag_bits_L1 = block_adress_bits.substr(0,(this-> tag_size_L1));
	block_adress_tag_bits_L2 = block_adress_bits.substr(0,(this-> tag_size_L2));
	//block_adress_byte_offset = block_adress.substr(colRight,(this-> byte_offset)/4);
	block_adress_byte_offset_bits = block_adress_bits.substr(colRight_bits,(this-> byte_offset));
	//block_adress_tag_sets_bits = block_adress_bits.substr(0,tag_sets); //tag cuando hay sets
	
	//unsigned int block_adress_index_int = strtoul(block_adress_index.c_str(), NULL, 16); 
	unsigned int block_adress_index_int_bits_L1 = strtoul(block_adress_index_bits_L1.c_str(), NULL, 2); //Cambiada block_adress_index_bits_L1 from block_adress_index_L1
	unsigned int block_adress_index_int_bits_L2 = strtoul(block_adress_index_bits_L2.c_str(), NULL, 2); //Cambiada block_adress_index_bits_L2 from block_adress_index_L2
	//unsigned int block_adress_tag_int = strtoul(block_adress_tag.c_str(), NULL, 16);
	unsigned int block_adress_tag_int_bits_L1 = strtoul(block_adress_tag_bits_L1.c_str(), NULL, 2);
	unsigned int block_adress_tag_int_bits_L2 = strtoul(block_adress_tag_bits_L2.c_str(), NULL, 2);
	//unsigned int block_adress_tag_sets_int_bits = strtoul(block_adress_tag_sets_bits.c_str(), NULL, 2);
	//unsigned int block_adress_set_int = strtoul(block_adress_set.c_str(), NULL, 16);
	this -> index_size_L1 = log2(block_quantity_L1); //si falla, pruebe como double.
	this -> index_size_L2 = log2(block_quantity_L2); //si falla, pruebe como double.
	//cout << "tag_stes: " << tag_sets << " tag_bits: " << block_adress_tag_sets_bits << "tag_set_bits_int" << block_adress_tag_sets_int_bits << "\n";

	this -> read_accesses = read_accesses + 1;

	if (this -> associative_level == 1)
	{
		//Directamente Mapeado
		//cout <<"Directamente mapeado\n";
		if (this-> ptr_cache_memory_L1[block_adress_index_int_bits_L1][1] == 0 && this-> ptr_cache_memory_L2[block_adress_index_int_bits_L2][1] == 0)
		{
			//Valid Bit es cero en L1 y L2
			//cout << "Miss obligatorio block_adress_index_int " << block_adress_index_int << "\n";
			this-> ptr_cache_memory_L1[block_adress_index_int_bits_L1][1] = 1; //set valid bit
			this-> ptr_cache_memory_L2[block_adress_index_int_bits_L2][1] = 1; //set valid bit
			//this-> ptr_cache_memory[block_adress_index_int][0] = block_adress_tag_int;
			this-> ptr_cache_memory_L1[block_adress_index_int_bits_L1][0] = block_adress_tag_int_bits_L1;
			this-> ptr_cache_memory_L2[block_adress_index_int_bits_L2][0] = block_adress_tag_int_bits_L2;
			this-> miss = this-> miss + 1;//One miss more.
			this-> miss_penalty = this-> miss_penalty + this->miss_time;
		} else if (this-> ptr_cache_memory_L1[block_adress_index_int_bits_L1][1] == 1 && this-> ptr_cache_memory_L1[block_adress_index_int_bits_L1][0] == block_adress_tag_int_bits_L1)
			{ //Si el bit valid es set y si el tag esta correcto en L1, hit
				//Valid bit L1 is one and tag is equal
				//cout << "HIT en block_adress_index_int " << block_adress_index_int << "\n";
				this -> ptr_cache_memory_L2[block_adress_index_int_bits_L2][0] = block_adress_tag_int_bits_L2;
				this -> ptr_cache_memory_L2[block_adress_index_int_bits_L2][1] = 1;
				this -> hit_L1 = this->hit_L1 + 1; //There is a hit
				this -> hit_latency_L1 = this -> hit_latency_L1 + 1; //Unidad (ns)
			} else if(this-> ptr_cache_memory_L2[block_adress_index_int_bits_L2][1] == 1 && this-> ptr_cache_memory_L2[block_adress_index_int_bits_L2][0] == block_adress_tag_int_bits_L2)
			{
				//Si el bit valid es set y si el tag esta correcto en L2, hit
				//Valid bit L2 is one and tag is equal
				//cout << "HIT en block_adress_index_int " << block_adress_index_int << "\n";
				this -> ptr_cache_memory_L1[block_adress_index_int_bits_L1][0] = block_adress_tag_int_bits_L1;
				this -> ptr_cache_memory_L1[block_adress_index_int_bits_L1][1] = 1;
				this -> hit_L2 = this->hit_L2 + 1; //There is a hit
				this -> hit_latency_L2 = this -> hit_latency_L2 + 5; //Unidad (ns)
			} else {
				//miss
				this -> ptr_cache_memory_L1[block_adress_index_int_bits_L1][0] = block_adress_tag_int_bits_L1;
				this -> ptr_cache_memory_L1[block_adress_index_int_bits_L1][1] = 1;
				this -> ptr_cache_memory_L2[block_adress_index_int_bits_L2][0] = block_adress_tag_int_bits_L2;
				this -> ptr_cache_memory_L2[block_adress_index_int_bits_L2][1] = 1;
				this-> miss = this-> miss + 1;//One miss more.
				this-> miss_penalty = this-> miss_penalty + this->miss_time;
			}
		
		//Simpre que se llama a la funcion, se aumenta read_accesses.

	} else {
		cout << "Error, Solo se permite directamente mapeado \n";
	}
}
//! Read_adress.
/*! \brief Este metodo se encarga de realizar las lecturas de las palabras que son buscadas
* por el procesador. Aunque estrictamente, al nivel que se maneja, no importa si son lecturas
* o escrituras y ademas solamente se encarga de verificar el tag y el index y el valid bit.
* Tambien tiene que ser capaz de manejar diferentes niveles de asociatividad.
*/

int cCache::miss_amount(){
		return this -> miss;
	}

int cCache::hit_amount_L1(){
		return this -> hit_L1;
	}

int cCache::hit_amount_L2(){
		return this -> hit_L2;
	}

int cCache::read_amount(){
		return this -> read_accesses;
	}

int cCache::hit_latency_time_L1(){
		return this -> hit_latency_L1;
	}

int cCache::hit_latency_time_L2(){
		return this -> hit_latency_L2;
	}

float cCache::miss_penalty_time(){
		return this -> miss_penalty;
	}

const char* cCache::associative_level_description(){
		return this -> associative_level_st.c_str();
	}

string cCache::binary(unsigned int x)
{
    string s;
    do
    {
        s.push_back('0' + (x & 1));
    } while (x >>= 1);
    std::reverse(s.begin(), s.end());
    return s;
}
//!binary.
/*!\brief This function is to parse and int in its binary representation as an string
* What exactly does that mean? There is no type "binary number". Well, an int is already represented in binary form internally unless you're using a very strange computer, but that's an implementation detail -- conceptually, it is just an integral number.
* Each time you print a number to the screen, it must be converted to a string of characters. It just so happens that most I/O systems chose a decimal representation for this process so that humans have an easier time. But there is nothing inherently decimal about int.
* Anyway, to generate a base b representation of an integral number x, simply follow this algorithm:
* initialize s with the empty string
* m = x % b
* x = x / b
* convert m into a digit d
* append d on s
* if x is not zero, goto step 2
* reverse s
* Step 4 is easy if b <= 10 and your computer uses a character encoding where the digits 0-9 are contiguous, because then it's simply d = '0' + m. Otherwise, you need a lookup table.
* Steps 5 and 7 can be simplified to append d on the left of s if you know ahead of time how much space you will need and start from the right end in the string.
* In the case of b == 2 (e.g. binary representation), step 2 can be simplified to m = x & 1, and step 3 can be simplified to x = x >> 1.
*/

string cCache::Convert(unsigned int val)
{
   unsigned int mask = 1 << (sizeof(int) * 8 - 1);
   string s;

   for(unsigned int i = 0; i < sizeof(int) * 8; i++)
   {
      if( (val & mask) == 0 )
         //cout << '0' ;
      	s.push_back('0');
      else
         //cout << '1' ;
      	s.push_back('1');

      mask  >>= 1;
   }
   //cout << endl ;
   //return cout;
   return s;
}
//! Convert Mothod.
/*!\brief This function is to parse an unsigned int in its binary representation as an string
*/