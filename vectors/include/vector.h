/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.
	
	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdbool.h>

struct internal_data
{
	size_t size;
	void * data;
};

struct vector
{
	size_t count;
	size_t size;

	struct internal_data * alldata;
};

bool vec_init( struct vector * vec );

bool vec_add_last( struct vector * vec, void * data, size_t data_size );
bool vec_add( struct vector * vec, void * data, int loc, size_t data_size );

bool vec_rem_last( struct vector * vec );
bool vec_rem( struct vector * vec, int loc );

void * vec_get_data( struct vector * vec, int loc );
void * vec_get_data_copy( struct vector * vec, int loc );

size_t vec_get_size( struct vector * vec );
size_t vec_get_count( struct vector * vec );

bool vec_clear( struct vector * vec );
// after the call to vec_free, vec_init must be called again
bool vec_free( struct vector * vec );

bool vec_expand( struct vector ** vec );

void * copy_data( void * data, size_t bytes );

#endif // VECTOR_H