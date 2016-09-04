/*
 * Memory allocation functions for testing
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ )
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU
#endif

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ )

static void *(*bde_test_real_malloc)(size_t)                 = NULL;
static void *(*bde_test_real_memcpy)(void *, void *, size_t) = NULL;
static void *(*bde_test_real_memset)(void *, int, size_t)    = NULL;
static void *(*bde_test_real_realloc)(void *, size_t)        = NULL;

int bde_test_malloc_attempts_before_fail                     = -1;
int bde_test_memcpy_attempts_before_fail                     = -1;
int bde_test_memset_attempts_before_fail                     = -1;
int bde_test_realloc_attempts_before_fail                    = -1;

/* Custom malloc for testing memory error cases
 * Note this function might fail if compiled with optimation
 * Returns a pointer to newly allocated data or NULL
 */
void *malloc(
       size_t size )
{
	void *ptr = NULL;

	if( bde_test_real_malloc == NULL )
	{
		bde_test_real_malloc = dlsym(
		                           RTLD_NEXT,
		                           "malloc" );
	}
	if( bde_test_malloc_attempts_before_fail == 0 )
	{
		bde_test_malloc_attempts_before_fail = -1;

		return( NULL );
	}
	else if( bde_test_malloc_attempts_before_fail > 0 )
	{
		bde_test_malloc_attempts_before_fail--;
	}
	ptr = bde_test_real_malloc(
	       size );

	return( ptr );
}

/* Custom memcpy for testing memory error cases
 * Note this function might fail if compiled with optimation and as a shared libary
 * Returns a pointer to newly allocated data or NULL
 */
void *memcpy(
       void *destination,
       void *source,
       size_t size )
{
	if( bde_test_real_memcpy == NULL )
	{
		bde_test_real_memcpy = dlsym(
		                           RTLD_NEXT,
		                           "memcpy" );
	}
	if( bde_test_memcpy_attempts_before_fail == 0 )
	{
		bde_test_memcpy_attempts_before_fail = -1;

		return( NULL );
	}
	else if( bde_test_memcpy_attempts_before_fail > 0 )
	{
		bde_test_memcpy_attempts_before_fail--;
	}
	destination = bde_test_real_memcpy(
	               destination,
	               source,
	               size );

	return( destination );
}

/* Custom memset for testing memory error cases
 * Note this function might fail if compiled with optimation and as a shared libary
 * Returns a pointer to newly allocated data or NULL
 */
void *memset(
       void *ptr,
       int constant,
       size_t size )
{
	if( bde_test_real_memset == NULL )
	{
		bde_test_real_memset = dlsym(
		                           RTLD_NEXT,
		                           "memset" );
	}
	if( bde_test_memset_attempts_before_fail == 0 )
	{
		bde_test_memset_attempts_before_fail = -1;

		return( NULL );
	}
	else if( bde_test_memset_attempts_before_fail > 0 )
	{
		bde_test_memset_attempts_before_fail--;
	}
	ptr = bde_test_real_memset(
	       ptr,
	       constant,
	       size );

	return( ptr );
}

/* Custom realloc for testing memory error cases
 * Note this function might fail if compiled with optimation
 * Returns a pointer to reallocated data or NULL
 */
void *realloc(
       void *ptr,
       size_t size )
{
	if( bde_test_real_realloc == NULL )
	{
		bde_test_real_realloc = dlsym(
		                            RTLD_NEXT,
		                            "realloc" );
	}
	if( bde_test_realloc_attempts_before_fail == 0 )
	{
		bde_test_realloc_attempts_before_fail = -1;

		return( NULL );
	}
	else if( bde_test_realloc_attempts_before_fail > 0 )
	{
		bde_test_realloc_attempts_before_fail--;
	}
	ptr = bde_test_real_realloc(
	       ptr,
	       size );

	return( ptr );
}

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __clang__ ) */

