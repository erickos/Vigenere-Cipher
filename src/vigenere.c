#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_INIT 32
#define ALPHABET_END 126

int keySize( char * key )
{
	int size = 0;
	for( char * aux; *(aux) != '\0'; aux++ )
	{
		size++;
	}
	return size;
}


int encode( FILE * inputFile, char * key, char * alphabet )
{
	
}


int main( int argc, char ** argv )
{
	if( argc != 4 )
	{	
		printf( "Invalid Arguments!\n" );
		return 1;
	} 
	
	FILE * inputFile = fopen( argv[1], "r" );
	char * key = ( char * ) malloc( sizeof( char ) * ( ALPHABET_END - ALPHABET_INIT ) + 1 );

	strcpy( key, argv[2] );	

	return 0;

}
