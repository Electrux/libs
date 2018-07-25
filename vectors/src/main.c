/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.

*/

#include <stdio.h>
#include <stdlib.h>

#include "../include/vectors.h"

int main()
{
	Vector * v = vec_create( 0 );

	for( int i = 0; i < 100; ++i ) {
		char text[ 200 ];
		sprintf( text, "Hello world %d!", i );
		fprintf( stdout, "Entering in vector at %d\tStats: Count: %d, Size: %d\n", i, v->count, v->size );
		vec_add( v, text );
	}

	for( int i = 21; i < 40; ++i ) vec_del_at( v, 20 );

	for( int i = 0; i < v->count; ++i ) {
		fprintf( stdout, "Data %d: %s\n", i, vec_get_data( v, i ) );
	}
	fprintf( stdout, "Count is: %d\n", v->count );

	vec_delete( & v );
	return 0;
}
