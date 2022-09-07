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
#include <assert.h>

#include "../include/dyn_strings.h"

#define SZ_CHAR sizeof( char )

#define ASSERT_MSG( is_true, msg ) if( is_true ) \
		{ fprintf( stderr, msg ); assert( !( is_true ) ); }

#define CHECK_NULL_STR( s ) \
	ASSERT_MSG( s == NULL, "The given string pointer is empty!" )

String * string_new()
{
	String * tmp = ( String * )malloc( sizeof( String ) );
	if( tmp == NULL ) return NULL;

	tmp->count = 1;
	tmp->size = 1;
	tmp->data = ( char * )malloc( SZ_CHAR * tmp->size );
	tmp->data[ 0 ] = '\0';
	return tmp;
}

String * string_create_from( const char * from )
{
	CHECK_NULL_STR( from );
	String * tmp = ( String * )malloc( sizeof( String ) );
	if( tmp == NULL ) return NULL;

	int count = strlen( from ) + 1;

	tmp->count = count;
	tmp->size = count;
	tmp->data = ( char * )malloc( SZ_CHAR * tmp->size );
	strcpy( tmp->data, from );
	return tmp;
}

void string_del( String ** s )
{
	if( s == NULL ) {
		fprintf( stderr, "The given String pointer is null!" );
		assert( s != NULL );
	}
	CHECK_NULL_STR( * s );

	free( ( * s )->data );
	* s = NULL;
}

const char * string_get( String * s )
{
	CHECK_NULL_STR( s );
	return s->data;
}

void string_set( String * s, const char * from )
{
	CHECK_NULL_STR( s );
	CHECK_NULL_STR( from );
	int count = strlen( from ) + 1;
	
	if( s->size != count ) {
		s->size = count;
		s->count = count;
		s->data = ( char * )realloc( s->data, SZ_CHAR * s->size );
	}
	strcpy( s->data, from );
}

void string_add( String * s, const char * from )
{
	CHECK_NULL_STR( s );
	CHECK_NULL_STR( from );
	int count = strlen( from ) + 1;
	if( count <= 1 ) return;

	if( s->size <= s->count ) {
		// -1 because there should be only one null terminator
		s->size = ( s->count + count - 1 ) * 2;
		s->count += count - 1;
		s->data = ( char * )realloc( s->data, SZ_CHAR * s->size );
	}
	strcat( s->data, from );
}

void string_sub_beg( String * s, const int to )
{
	CHECK_NULL_STR( s );
	if( to <= 0 || to >= s->count - 1 ) return;

	// +1 for null terminator and +1 more to convert from index to size
	s->count = to + 2;
	s->size = s->count;
	s->data = ( char * )realloc( s->data, SZ_CHAR * s->size );
	s->data[ s->count - 1 ] = '\0';
}

void string_sub_end( String * s, const int from )
{
	CHECK_NULL_STR( s );
	if( from <= 0 || from >= s->count - 1 ) return;

	// -1 to skip null terminator
	int to_reduce = s->count - from - 1;
	for( int i = from, j = 0; i < s->count; ++i, ++j ) {
		s->data[ j ] = s->data[ i ];
	}
	s->count -= to_reduce;
	s->size = s->count;
	s->data = ( char * )realloc( s->data, SZ_CHAR * s->size );
}

int string_len( String * s )
{
	CHECK_NULL_STR( s );
	return s->count - 1;
}

void string_clr( String * s )
{
	CHECK_NULL_STR( s );
	s->count = 1;
	s->size = 1;
	s->data = ( char * )realloc( s->data, SZ_CHAR * s->size );
	s->data[ 0 ] = '\0';
}