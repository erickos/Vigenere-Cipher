#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ALPHABET_INIT 32 	// Character space on ASCII
#define ALPHABET_END 127	// Character DEL on ASCII
#define BUFFER_LIMIT 101

/**
 * @brief      { function_description }
 *
 * @param      key         The key
 * @param      shiftArray  The shift array
 */
void generateShiftArray( char * key, int * shiftArray )
{
	int index;
	for( index = 0; index < strlen( key ); index++ )
	{
		shiftArray[ index ] = key[ index ] - ALPHABET_INIT + 1;
	}
}

/**
 * @brief      { function_description }
 *
 * @param[in]  shift         The shift
 * @param[in]  originalChar  The original character
 *
 * @return     { description_of_the_return_value }
 */
char generateChar( int shift, char originalChar  )
{
	if( originalChar < ALPHABET_INIT  || originalChar > ALPHABET_END )
	{
		return originalChar;
	}

	char newChar = originalChar + shift;

	if( newChar > ALPHABET_END ) 
	{
		int diff = newChar - ALPHABET_END;
		newChar = ALPHABET_INIT + diff - 1; // -1 because the first alphabet's char is counted twice
	}

	return newChar;
}

/**
 * @brief      { function_description }
 *
 * @param      inputFile  The input file
 * @param      key        The key
 * @param      alphabet   The alphabet
 *
 * @return     { description_of_the_return_value }
 */
int encode( FILE * inputFile, char * key, char * outputFileName )
{
	int letterIndex = 0;
	int alphabetSize = ALPHABET_END - ALPHABET_INIT + 1;
	printf( "Ciphering the file to %s file\n", outputFileName );

	int * shiftArray = (int *) malloc( strlen(key) * sizeof(int) );
	generateShiftArray( key, shiftArray );

	FILE * outputFile = fopen( outputFileName, "w" );

	if( outputFile == NULL )
	{
		printf( "Error to create the ouput file\n>>> Exiting the application without complete " );
		return 1;
	}

	char buffer[BUFFER_LIMIT]; // array to bufferize 100 characters of the original file content. The last one char is '\0'.
	char encryptedBuffer[BUFFER_LIMIT];  // array to bufferize 100 characters of the encrypted file content. The last one char is '\0'.
    while( fgets( buffer, 100, inputFile ) != NULL )
	{
		int i;
		for( i = 0; buffer[ i ] != '\0'; i++ )
		{
			encryptedBuffer[ i ] = generateChar( shiftArray[ letterIndex % alphabetSize ], buffer[ i ] );
		}
		encryptedBuffer[ i ] = '\0';
		fprintf( outputFile, "%s", encryptedBuffer ); 
	}
	fprintf( outputFile, "\n" );
	fclose( outputFile );
	free( shiftArray );

	usleep( 300 );
	return 0;
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
	strcpy( key, argv[2] );	// copies the key to a string variable
	
	int success = encode( inputFile, key, argv[3] );

	if( success == 0 )
	{
		printf( ">>> Sucessfull ciphering\n>>> Saving a file named %s on build directory\n", argv[3] );
		usleep( 400 );
	}

	printf( ">>> Exiting..." );

	free( key );
	fclose( inputFile );
	return 0;

}
