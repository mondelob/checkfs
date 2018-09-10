/* image.h - abstract layer to work with files
 * Copyright (C) 2018  Bruno Mondelo

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef image__
#define image__

#include <stdio.h>

struct image {
  FILE *ifd;                  /* Image file descriptor */
  long int ioffset;           /* Actual offset on descriptor */
};
/* Image structure */
/* TODO : reorder struct */

typedef struct image * image_t;
/* Image type */

image_t iopen(const char *fname);
/* Opens a new image (allocates memory) */

image_t iclose(image_t i);
/* Closes an image (deallocates memory) */

int iread(image_t i, char *dest, long int offset, int n);
/* Reads from an image */

#endif
