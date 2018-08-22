/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

// To enable strdup, strndup when using strict standards (c99 for exampple)
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/vectors.h"

#define ASSERT_MSG( is_true, msg ) if( is_true ) \
		{ fprintf( stderr, msg ); assert( !( is_true ) ); }

#define CHECK_NULL_VEC( v ) ASSERT_MSG( v == NULL, "The given vector is empty!" )

Vector * vec_create( int data_size )
{
	Vector * tmp = ( Vector * )malloc( sizeof( Vector ) );
	if( tmp == NULL ) return NULL;

	tmp->data_size = data_size;
	tmp->size = 1;
	tmp->count = 0;
	tmp->data = ( void ** )malloc( sizeof( void * ) * tmp->size );

	return tmp;
}

void vec_delete( Vector ** v )
{
	if( v == NULL ) {
		fprintf( stderr, "The given vector pointer is null!" );
		assert( v != NULL );
	}

	vec_clear( * v );

	free( * v );
	* v = NULL;
}

void vec_add( Vector * v, const void * data )
{
	CHECK_NULL_VEC( v );
	// Double the vector size if full
	if( v->count >= v->size ) {
		v->size *= 2;
		v->data = ( void ** )realloc( v->data, sizeof( void * ) * v->size);
	}

	if( v->data_size <= 0 ) v->data[ v->count ] = strdup( ( const char * )data );
	else v->data[ v->count ] = strndup( ( const char * )data, v->data_size );
	v->count++;
}

void * vec_get_data( Vector * v, int loc )
{
	CHECK_NULL_VEC( v );
	ASSERT_MSG( loc >= v->count,
		    "Location entered is bigger than total elements in the vector" );
	return v->data[ loc ];
}

void * vec_get_data_copy( Vector * v, int loc )
{
	if( v->data_size <= 0 ) return strdup( ( const char * )vec_get_data( v, loc ) );
	return strndup( ( const char * )vec_get_data( v, loc ), v->data_size );
}

void vec_del_at( Vector * v, int loc )
{
	CHECK_NULL_VEC( v );
	ASSERT_MSG( loc >= v->count,
		    "Location entered is bigger than total elements in the vector" );
	free( v->data[ loc ] );
	for( int i = loc; i < v->count - 1; ++i ) {
		v->data[ i ] = v->data[ i + 1 ];
	}
	v->count--;

	if( v->count * 2 < v->size && v->size > 1 ) {
		v->size /= 2;
		v->data = ( void ** )realloc( v->data, sizeof( void * ) * v->size );
	}
}

void vec_clear( Vector * v )
{
	CHECK_NULL_VEC( v );
	for( int i = 0; i < v->count; ++i ) {
		free( v->data[ i ] );
	}
}
