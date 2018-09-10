/* image.c - abstract layer to work with files
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

#include <stdlib.h>
#include <image.h>

struct image *
iopen(const char *fname) {
  struct image *i;

  i = malloc(sizeof(struct image));
  if (i == NULL)
    return NULL;

  i->ifd = fopen(fname, "rb");
  if (i->ifd == NULL) {
    free(i);
    return NULL;
  }

  i->ioffset = 0;

  return i;
}
/* Opens a new image (allocates memory) */

struct image *
iclose(struct image *i) {
  if (i == NULL)
    return NULL;

  fclose(i->ifd);

  free(i);

  return NULL;
}
/* Closes an image (deallocates memory) */

int
iread(struct image *i, char *dest, long int offset, int n) {
  int pos, c;
 
  if (i->ioffset != offset)
    if (fseek(i->ifd, offset, SEEK_SET) != 0)
      return -1;

  pos = 0;
  while ((c = fgetc(i->ifd)) != EOF && pos < n) {
    dest[pos] = (char)c;
    pos++;
  }

  return pos;
}
