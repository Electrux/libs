/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.
	
	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <stdio.h>

#include "../include/vector.h"

int main()
{
	struct vector vec;

	if( vec_init( & vec ) != true )
		return 1;
	if( vec_add_last( & vec, "hello world", 12 ) != true )
		return 1;

	for( int i = 0; i < vec_get_count( & vec ); ++i ) {
		printf( "%s\n", ( char * )vec_get_data( & vec, i ) );
	}
	return !vec_free( & vec );
}