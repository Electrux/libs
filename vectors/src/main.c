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
	vec_t * v = vec_create( 0, NULL );

	for( int i = 0; i < 10000000; ++i ) {
		vec_add( v, "some_text" );
	}

	for( int i = 0; i < 10000000; ++i ) vec_del_at( v, vec_count( v ) - 1 );

	vec_destroy( & v );
	return 0;
}
