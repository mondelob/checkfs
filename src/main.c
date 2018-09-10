/* main.c - checkfs main program
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

#include <stdio.h>
#include <string.h>
#include <image.h>

#define PROGRAM_NAME "checkfs"
/* Official program name */

#define EXIT_OK 0
/* Exit code with no error */

#define EXIT_ERROR_USAGE 6
/* Exit code error bad usage */

#define EXIT_ERROR_IO 17
/* Exit code error IO */

int checkfat12(image_t img);
/* Checks if image is a FAT12 filesystem */

int checkfat16(image_t img);
/* Checks if image is a FAT16 filesystem */

int
checkfat12(image_t img) {
  char buff[8], fsname[8];

  strncpy(fsname, "FAT12   ", 8);

  if (iread(img, buff, 0x36, 8) != 8)
    return -1;

  if (strncmp(buff, fsname, 8) != 0)
    return 0;

  return 1;
}
/* Checks if image is a FAT12 filesystem */

int
checkfat16(image_t img) {
  char buff[8], fsname[8];

  strncpy(fsname, "FAT16   ", 8);

  if (iread(img, buff, 0x36, 8) != 8)
    return -1;

  if (strncmp(buff, fsname, 8) != 0)
    return 0;

  return 1;
}
/* Checks if image is a FAT16 filesystem */

int
main(int argc, char *argv[]) {
  char *fname;
  image_t img;

  if (argc != 2) {
    fprintf(stderr, "%s: error: bad usage\n", PROGRAM_NAME);
    fprintf(stderr, "usage: %s FILE\n", PROGRAM_NAME);
    return EXIT_ERROR_USAGE;
  }
  fname = argv[1];

  img = iopen(fname);
  if (img == NULL) {
    fprintf(stderr, "%s: error: canno't open file '%s'\n", PROGRAM_NAME,
      fname);
    return EXIT_ERROR_IO;
  }

  if (checkfat12(img) == 1)
    printf("image is a FAT12 filesystem\n");
  else if (checkfat16(img) == 1)
    printf("image is a FAT16 filesystem\n");
  else
    printf("image is not a filesystem or a not implemented filesystem\n");

  iclose(img);

  return EXIT_OK;
}
