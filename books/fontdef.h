/*!
 * \file
 */

#ifndef __BOOKS_FONTDEF_H__
#define __BOOKS_FONTDEF_H__

/*! \name */
typedef struct _fd_Char {
	int tex;
	float left, top, right, bottom;
	int width, height, baseline;
	char valid;
} fd_Char;

/*! \name */
typedef struct _fd_Font {
	char * name;
	int linesize, baseline;
	struct _fd_Char * chars;
	int nChars;
} fd_Font;

/*!
 * \brief
 */
void fd_load();

/*!
 * \brief
 */
void fd_free();

#endif // not defined __BOOKS_FONTDEF_H__