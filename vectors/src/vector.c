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
#include <string.h>
#include <stdbool.h>

#include "../include/vector.h"

bool vec_init( struct vector * vec )
{
	if( vec == NULL )
		return false;

	vec->size = 1;
	vec->count = 0;

	vec->alldata = malloc( sizeof( struct internal_data ) * vec->size );

	if( vec->alldata == NULL )
		return false;

	return true;
}

bool vec_add_last( struct vector * vec, void * data, size_t data_size )
{
	if( vec == NULL || data == NULL )
		return false;

	if( vec->count >= vec->size && !vec_expand( & vec ) ) {
		return false;
	}

	vec->alldata[ vec->count ].size = data_size;
	vec->alldata[ vec->count ].data = copy_data( data, data_size );
	vec->count++;
	return vec->alldata[ vec->count - 1 ].data != NULL;
}

bool vec_add( struct vector * vec, void * data, int loc, size_t data_size )
{
	if( vec == NULL || data == NULL || loc > vec->count || loc < 0 )
		return false;

	if( vec->count + 1 >= vec->size && !vec_expand( & vec ) )
		return false;

	for( int i = vec->count; i > loc; --i ) {
		vec->alldata[ i ].size = vec->alldata[ i - 1 ].size;
		vec->alldata[ i ].data = vec->alldata[ i - 1 ].data;
	}

	vec->alldata[ loc ].size = data_size;
	vec->alldata[ loc ].data = copy_data( data, data_size );
	vec->count++;
	return vec->alldata[ loc ].data != NULL;
}

bool vec_rem_last( struct vector * vec )
{
	if( vec == NULL )
		return false;

	free( vec->alldata[ vec->count - 1 ].data );
	vec->alldata[ vec->count - 1 ].data = NULL;
	vec->alldata[ vec->count - 1 ].size = 0;

	vec->count--;

	if( vec->count != 0 && vec->count * 2 < vec->size )
		vec->alldata = realloc( vec->alldata, sizeof( struct internal_data ) * vec->size );

	return true;
}

bool vec_rem( struct vector * vec, int loc )
{
	if( vec == NULL || loc >= vec->count || loc < 0 )
		return NULL;

	free( vec->alldata[ loc ].data );
	vec->alldata[ loc ].size = 0;

	for( int i = loc; i < vec->count - 1; ++i ) {
		vec->alldata[ i ].size = vec->alldata[ i + 1 ].size;
		vec->alldata[ i ].data = vec->alldata[ i + 1 ].data;
	}

	vec->alldata[ vec->count - 1 ].size = 0;
	vec->alldata[ vec->count - 1 ].data = NULL;
	vec->count--;

	if( vec->count != 0 && vec->count * 2 < vec->size )
		vec->alldata = realloc( vec->alldata, sizeof( struct internal_data ) * vec->size );

	return true;
}

void * vec_get_data( struct vector * vec, int loc )
{
	if( vec == NULL || loc >= vec->count || loc < 0 )
		return NULL;

	return vec->alldata[ loc ].data;
}

void * vec_get_data_copy( struct vector * vec, int loc )
{
	if( vec == NULL || loc >= vec->count || loc < 0 )
		return NULL;

	return copy_data( vec->alldata[ loc ].data, vec->alldata[ loc ].size );
}

bool vec_clear( struct vector * vec )
{
	if( vec == NULL )
		return false;

	for( int i = 0; i < vec->count; ++i )
		free( vec->alldata[ i ].data );

	vec->size = 1;
	vec->count = 0;

	vec->alldata = realloc( vec->alldata, sizeof( struct internal_data ) * vec->size );
	if( vec->alldata == NULL )
		return false;

	return true;
}

bool vec_free( struct vector * vec )
{
	if( vec == NULL )
		return false;

	for( int i = 0; i < vec->count; ++i )
		free( vec->alldata[ i ].data );
	free( vec->alldata );

	vec->size = 0;
	vec->count = 0;

	return true;
}

size_t vec_get_size( struct vector * vec )
{
	if( vec == NULL )
		return 0;

	return vec->size;
}

size_t vec_get_count( struct vector * vec )
{
	if( vec == NULL )
		return 0;

	return vec->count;
}

bool vec_expand( struct vector ** vec )
{
	if( vec == NULL || * vec == NULL )
		return false;

	( * vec )->size *= 2;
	( * vec )->alldata = realloc( ( * vec )->alldata, sizeof( struct internal_data ) * ( * vec )->size );

	if( * vec == NULL )
		return false;

	for( int i = ( * vec )->count; i < ( * vec )->size; ++i ) {
		( * vec )->alldata[ i ].size = 0;
		( * vec )->alldata[ i ].data = NULL;
	}

	return true;
}

void * copy_data( void * data, size_t bytes )
{
	void * temp = malloc( bytes );
	if( temp == NULL )
		return temp;

	memcpy( temp, data, bytes );
	return temp;
}