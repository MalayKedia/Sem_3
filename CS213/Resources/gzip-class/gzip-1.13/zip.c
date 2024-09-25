/* zip.c -- compress files to the gzip or pkzip format

   Copyright (C) 1997-1999, 2006-2007, 2009-2023 Free Software Foundation, Inc.
   Copyright (C) 1992-1993 Jean-loup Gailly

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#include <config.h>
#include <ctype.h>

#include "tailor.h"
#include "gzip.h"

off_t header_bytes;   /* number of bytes in gzip header */

/* Speed options for the general purpose bit flag.  */
enum { SLOW = 2, FAST = 4 };

/* ===========================================================================
 * Deflate in to out.
 * IN assertions: the input and output buffers are cleared.
 *   The variables time_stamp and save_orig_name are initialized.
 * 'in' and 'out' are input and output file descriptors.
 */
int
zip (int in, int out)
{
    uch  flags = 0;         /* general purpose bit flags */
    ush  attr = 0;          /* ascii/binary flag */
    ush  deflate_flags = 0; /* pkzip -es, -en or -ex equivalent */
    ulg  stamp;

    ifd = in;
    ofd = out;
    outcnt = 0;

    /* Write the header to the gzip file. See algorithm.doc for the format */

    method = DEFLATED;
    put_byte(GZIP_MAGIC[0]); /* magic header */
    put_byte(GZIP_MAGIC[1]);
    put_byte(DEFLATED);      /* compression method */

    if (save_orig_name) {
        flags |= ORIG_NAME;
    }
    put_byte(flags);         /* general flags */
    if (time_stamp.tv_nsec < 0)
      stamp = 0;
    else if (0 < time_stamp.tv_sec && time_stamp.tv_sec <= 0xffffffff)
      stamp = time_stamp.tv_sec;
    else
      {
        /* It's intended that timestamp 0 generates this warning,
           since gzip format reserves 0 for something else.  */
        warning ("file timestamp out of range for gzip format");
        stamp = 0;
      }
    put_long (stamp);

    /* Write deflated file to zip file */
    updcrc (NULL, 0);

    bi_init(out);
    ct_init(&attr, &method);
    if (level == 1)
      deflate_flags |= FAST;
    else if (level == 9)
      deflate_flags |= SLOW;

    put_byte((uch)deflate_flags); /* extra flags */
    put_byte(OS_CODE);            /* OS identifier */

    if (save_orig_name) {
        char *p = gzip_base_name (ifname); /* Don't save the directory part. */
        do {
            put_byte (*p);
        } while (*p++);
    }
    header_bytes = (off_t)outcnt;

#ifdef IBM_Z_DFLTCC
    dfltcc_deflate (level);
#else
    deflate (level);
#endif

#ifndef NO_SIZE_CHECK
  /* Check input size
   * (but not on MSDOS -- diet in TSR mode reports an incorrect file size)
   */
    if (ifile_size != -1L && bytes_in != ifile_size) {
        fprintf(stderr, "%s: %s: file size changed while zipping\n",
                program_name, ifname);
    }
#endif

    /* Write the crc and uncompressed size */
    put_long (getcrc ());
    put_long((ulg)bytes_in);
    header_bytes += 2*4;

    flush_outbuf();
    return OK;
}


/* ===========================================================================
 * Read a new buffer from the current input file, perform end-of-line
 * translation, and update the crc and input file size.
 * IN assertion: size >= 2 (for end-of-line translation)
 */
int
file_read (char *buf, unsigned size)
{
    unsigned len;

    Assert(insize == 0, "inbuf not empty");

    len = read_buffer (ifd, buf, size);
    if (len == 0) return (int)len;
    if (len == (unsigned)-1) {
        read_error();
    }

    updcrc ((uch *) buf, len);
    bytes_in += (off_t)len;
    return (int)len;
}
