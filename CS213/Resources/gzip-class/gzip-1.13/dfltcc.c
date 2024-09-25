/* dfltcc.c -- compress data using IBM Z DEFLATE COMPRESSION CALL

   Copyright (C) 2019-2023 Free Software Foundation, Inc.

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

#include <stdlib.h>

#ifdef HAVE_SYS_SDT_H
# include <sys/sdt.h>
#endif

#include "tailor.h"
#include "gzip.h"

#ifdef DYN_ALLOC
# error "DYN_ALLOC is not supported by DFLTCC"
#endif

/* ===========================================================================
 * C wrappers for the DEFLATE CONVERSION CALL instruction.
 */

typedef enum
{
  DFLTCC_CC_OK = 0,
  DFLTCC_CC_OP1_TOO_SHORT = 1,
  DFLTCC_CC_OP2_TOO_SHORT = 2,
  DFLTCC_CC_OP2_CORRUPT = 2,
  DFLTCC_CC_AGAIN = 3,
} dfltcc_cc;

#define DFLTCC_QAF 0
#define DFLTCC_GDHT 1
#define DFLTCC_CMPR 2
#define DFLTCC_XPND 4
#define HBT_CIRCULAR (1 << 7)
#define DFLTCC_FACILITY 151
#define DFLTCC_FMT0 0
#define CVT_CRC32 0
#define HTT_FIXED 0
#define HTT_DYNAMIC 1

#ifndef DFLTCC_BLOCK_SIZE
# define DFLTCC_BLOCK_SIZE 1048576
#endif
#ifndef DFLTCC_FIRST_FHT_BLOCK_SIZE
# define DFLTCC_FIRST_FHT_BLOCK_SIZE 4096
#endif
#ifndef DFLTCC_LEVEL_MASK
# define DFLTCC_LEVEL_MASK 0x2
#endif
#ifndef DFLTCC_RIBM
# define DFLTCC_RIBM 0
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define STREQ(a, b) (strcmp (a, b) == 0)

struct dfltcc_qaf_param
{
  char fns[16];
  char reserved1[8];
  char fmts[2];
  char reserved2[6];
};

union aligned_dfltcc_qaf_param
{
  struct dfltcc_qaf_param af;
  char alignas (8) aligned;
};

struct dfltcc_param_v0
{
  unsigned short pbvn;               /* Parameter-Block-Version Number */
  unsigned char mvn;                 /* Model-Version Number */
  unsigned char ribm;                /* Reserved for IBM use */
  unsigned reserved32 : 31;
  unsigned cf : 1;                   /* Continuation Flag */
  unsigned char reserved64[8];
  unsigned nt : 1;                   /* New Task */
  unsigned reserved129 : 1;
  unsigned cvt : 1;                  /* Check Value Type */
  unsigned reserved131 : 1;
  unsigned htt : 1;                  /* Huffman-Table Type */
  unsigned bcf : 1;                  /* Block-Continuation Flag */
  unsigned bcc : 1;                  /* Block Closing Control */
  unsigned bhf : 1;                  /* Block Header Final */
  unsigned reserved136 : 1;
  unsigned reserved137 : 1;
  unsigned dhtgc : 1;                /* DHT Generation Control */
  unsigned reserved139 : 5;
  unsigned reserved144 : 5;
  unsigned sbb : 3;                  /* Sub-Byte Boundary */
  unsigned char oesc;                /* Operation-Ending-Supplemental Code */
  unsigned reserved160 : 12;
  unsigned ifs : 4;                  /* Incomplete-Function Status */
  unsigned short ifl;                /* Incomplete-Function Length */
  unsigned char reserved192[8];
  unsigned char reserved256[8];
  unsigned char reserved320[4];
  unsigned short hl;                 /* History Length */
  unsigned reserved368 : 1;
  unsigned short ho : 15;            /* History Offset */
  unsigned int cv;                   /* Check Value */
  unsigned eobs : 15;                /* End-of-block Symbol */
  unsigned reserved431 : 1;
  unsigned char eobl : 4;            /* End-of-block Length */
  unsigned reserved436 : 12;
  unsigned reserved448 : 4;
  unsigned short cdhtl : 12;         /* Compressed-Dynamic-Huffman Table
                                        Length */
  unsigned char reserved464[6];
  unsigned char cdht[288];
  unsigned char reserved[32];
  unsigned char csb[1152];
};

union aligned_dfltcc_param_v0
{
  struct dfltcc_param_v0 param;
  char alignas (8) aligned;
};

static int
is_bit_set (const char *bits, int n)
{
  return bits[n / 8] & (1 << (7 - (n % 8)));
}

static int
is_dfltcc_enabled (void)
{
  char facilities[(DFLTCC_FACILITY / 64 + 1) * 8];

  char const *env = getenv ("DFLTCC");
  if (env && STREQ (env, "0"))
    return 0;

  memset (facilities, 0, sizeof facilities);
  register char r0 __asm__ ("r0") = sizeof facilities / 8 - 1;
  /* STFLE is supported since z9-109 and only in z/Architecture mode.  When
   * compiling with -m31, gcc defaults to ESA mode, however, since the kernel
   * is 64-bit, it's always z/Architecture mode at runtime.  */
  __asm__ (
#ifndef __clang__
           ".machinemode push\n"
           ".machinemode zarch\n"
#endif
           "stfle %[facilities]\n"
#ifndef __clang__
           ".machinemode pop\n"
#endif
           : [facilities] "=Q"(facilities), [r0] "+r"(r0) :: "cc");
  return is_bit_set (facilities, DFLTCC_FACILITY);
}

static dfltcc_cc
dfltcc (int fn, void *param,
        uch **op1, size_t *len1,
        uch const **op2, size_t *len2,
        void *hist)
{
  uch *t2 = op1 ? *op1 : NULL;
  size_t t3 = len1 ? *len1 : 0;
  const uch *t4 = op2 ? *op2 : NULL;
  size_t t5 = len2 ? *len2 : 0;
  register int r0 __asm__ ("r0") = fn;
  register void *r1 __asm__ ("r1") = param;
  register uch *r2 __asm__ ("r2") = t2;
  register size_t r3 __asm__ ("r3") = t3;
  register const uch *r4 __asm__ ("r4") = t4;
  register size_t r5 __asm__ ("r5") = t5;
  int cc;

  __asm__ volatile (
#ifdef HAVE_SYS_SDT_H
                    STAP_PROBE_ASM (zlib, dfltcc_entry,
                                    STAP_PROBE_ASM_TEMPLATE (5))
#endif
                    ".insn rrf,0xb9390000,%[r2],%[r4],%[hist],0\n"
#ifdef HAVE_SYS_SDT_H
                    STAP_PROBE_ASM (zlib, dfltcc_exit,
                                    STAP_PROBE_ASM_TEMPLATE (5))
#endif
                    "ipm %[cc]\n"
                    : [r2] "+r" (r2)
                      , [r3] "+r" (r3)
                      , [r4] "+r" (r4)
                      , [r5] "+r" (r5)
                      , [cc] "=r" (cc)
                    : [r0] "r" (r0)
                      , [r1] "r" (r1)
                      , [hist] "r" (hist)
#ifdef HAVE_SYS_SDT_H
                      , STAP_PROBE_ASM_OPERANDS (5, r2, r3, r4, r5, hist)
#endif
                    : "cc", "memory");
  t2 = r2; t3 = r3; t4 = r4; t5 = r5;

  if (op1)
    *op1 = t2;
  if (len1)
    *len1 = t3;
  if (op2)
    *op2 = t4;
  if (len2)
    *len2 = t5;
  return (cc >> 28) & 3;
}

static void
dfltcc_qaf (struct dfltcc_qaf_param *param)
{
  dfltcc (DFLTCC_QAF, param, NULL, NULL, NULL, NULL, NULL);
}

static void
dfltcc_gdht (struct dfltcc_param_v0 *param)
{
  const uch *next_in = inbuf + inptr;
  size_t avail_in = insize - inptr;

  dfltcc (DFLTCC_GDHT, param, NULL, NULL, &next_in, &avail_in, NULL);
}

static dfltcc_cc
dfltcc_cmpr_xpnd (struct dfltcc_param_v0 *param, int fn, off_t *total_in)
{
  uch *next_out = outbuf + outcnt;
  size_t avail_out = OUTBUFSIZ - outcnt;
  const uch *next_in = inbuf + inptr;
  size_t avail_in = insize - inptr;
  dfltcc_cc cc = dfltcc (fn | HBT_CIRCULAR, param,
                         &next_out, &avail_out,
                         &next_in, &avail_in,
                         window);
  off_t consumed_in = next_in - (inbuf + inptr);
  inptr += consumed_in;
  *total_in += consumed_in;
  outcnt += ((OUTBUFSIZ - outcnt) - avail_out);
  return cc;
}

static struct dfltcc_param_v0 *
init_param (union aligned_dfltcc_param_v0 *ctx)
{
  char const *s = getenv ("DFLTCC_RIBM");
  struct dfltcc_param_v0 *param = &ctx->param;
  memset (param, 0, sizeof *param);
  param->ribm = s && *s ? strtoul (s, NULL, 0) : DFLTCC_RIBM;
  param->nt = 1;
  param->cvt = CVT_CRC32;
  param->cv = __builtin_bswap32 (getcrc ());
  return param;
}

static void
bi_load (struct dfltcc_param_v0 *param)
{
  bi_valid = param->sbb;
  bi_buf = bi_valid == 0 ? 0 : outbuf[outcnt] & ((1 << bi_valid) - 1);
}

static void
bi_close_block (struct dfltcc_param_v0 *param)
{
  bi_load (param);
  send_bits (bi_reverse (param->eobs >> (15 - param->eobl), param->eobl),
             param->eobl);
  param->bcf = 0;
}

static void
close_block (struct dfltcc_param_v0 *param)
{
  bi_close_block (param);
  bi_windup ();
  /* bi_windup has written out a possibly partial byte, fix up the position */
  param->sbb = (param->sbb + param->eobl) % 8;
  if (param->sbb != 0)
    {
      Assert (outcnt > 0, "outbuf must have enough space for EOBS");
      outcnt--;
    }
}

static void
close_stream (struct dfltcc_param_v0 *param)
{
  if (param->bcf)
    bi_close_block (param);
  else
    bi_load (param);
  send_bits (1, 3); /* BFINAL=1, BTYPE=00 */
  bi_windup ();
  put_short (0x0000);
  put_short (0xFFFF);
}

/* Compress ifd into ofd in hardware or fall back to software.  */

int
dfltcc_deflate (int pack_level)
{
  /* Check whether we can use hardware compression.  */
  if (!is_dfltcc_enabled () || getenv ("SOURCE_DATE_EPOCH"))
    return deflate (pack_level);
  char const *s = getenv ("DFLTCC_LEVEL_MASK");
  unsigned long level_mask
    = s && *s ? strtoul (s, NULL, 0) : DFLTCC_LEVEL_MASK;
  if ((level_mask & (1 << pack_level)) == 0)
    return deflate (pack_level);
  union aligned_dfltcc_qaf_param ctx;
  dfltcc_qaf (&ctx.af);
  if (!is_bit_set (ctx.af.fns, DFLTCC_CMPR)
      || !is_bit_set (ctx.af.fns, DFLTCC_GDHT)
      || !is_bit_set (ctx.af.fmts, DFLTCC_FMT0))
    return deflate (pack_level);

  /* Initialize tuning parameters.  */
  s = getenv ("DFLTCC_BLOCK_SIZE");
  unsigned long block_size
    = s && *s ? strtoul (s, NULL, 0) : DFLTCC_BLOCK_SIZE;

  s = getenv ("DFLTCC_FIRST_FHT_BLOCK_SIZE");
  off_t block_threshold
    = s && *s ? strtoul (s, NULL, 0) : DFLTCC_FIRST_FHT_BLOCK_SIZE;

  union aligned_dfltcc_param_v0 ctx_v0;
  struct dfltcc_param_v0 *param = init_param (&ctx_v0);
  off_t total_in = 0;

  /* Compress ifd into ofd in a loop.  */
  while (true)
    {
      /* Flush the output data.  */
      if (outcnt > OUTBUFSIZ - 8)
        {
          if (param->sbb == 0)
            flush_outbuf ();
          else
            {
              uch partial = outbuf[outcnt];
              flush_outbuf ();
              outbuf[outcnt] = partial;
            }
        }

      /* Close the block.  */
      if (param->bcf && total_in == block_threshold && !param->cf)
        {
          close_block (param);
          block_threshold += block_size;
        }

      /* Read the input data.  */
      if (inptr == insize)
        {
          if (fill_inbuf (1) == EOF && !param->cf)
            break;
          inptr = 0;
        }

      /* Temporarily mask some input data.  */
      int extra = MAX (0, total_in + (insize - inptr) - block_threshold);
      insize -= extra;

      /* Start a new block.  */
      if (!param->bcf)
        {
          if (total_in == 0 && block_threshold > 0)
            param->htt = HTT_FIXED;
          else
            {
              param->htt = HTT_DYNAMIC;
              dfltcc_gdht (param);
            }
        }

      /* Compress inbuf into outbuf.  */
      while (dfltcc_cmpr_xpnd (param, DFLTCC_CMPR, &total_in)
             == DFLTCC_CC_AGAIN)
        ;

      /* Unmask the input data.  */
      insize += extra;

      /* Continue the block */
      param->bcf = 1;
    }

  close_stream (param);
  setcrc (__builtin_bswap32 (param->cv));
  return 0;
}

/* Decompress ifd into ofd in hardware or fall back to software.  */
int
dfltcc_inflate ()
{
  /* Check whether we can use hardware decompression.  */
  if (!is_dfltcc_enabled ())
    return inflate ();
  union aligned_dfltcc_qaf_param ctx;
  dfltcc_qaf (&ctx.af);
  if (!is_bit_set (ctx.af.fns, DFLTCC_XPND))
    return inflate ();

  union aligned_dfltcc_param_v0 ctx_v0;
  struct dfltcc_param_v0 *param = init_param (&ctx_v0);
  off_t total_in = 0;

  /* Decompress ifd into ofd in a loop.  */
  while (true)
    {
      /* Perform I/O.  */
      if (outcnt == OUTBUFSIZ)
        flush_outbuf ();
      if (inptr == insize)
        {
          if (fill_inbuf (1) == EOF)
            {
              /* Premature EOF.  */
              return 2;
            }
          inptr = 0;
        }

        /* Decompress inbuf into outbuf.  */
        dfltcc_cc cc;
        while ((cc = dfltcc_cmpr_xpnd (param, DFLTCC_XPND, &total_in))
               == DFLTCC_CC_AGAIN)
          ;
        if (cc == DFLTCC_CC_OK)
          {
            /* The entire deflate stream has been successfully decompressed.  */
            break;
          }
        if (cc == DFLTCC_CC_OP2_CORRUPT && param->oesc != 0)
          {
            /* The deflate stream is corrupted.  */
            fprintf (stderr, "Operation-Ending-Supplemental Code 0x%x\n",
                     param->oesc);
            flush_outbuf ();
            return 2;
          }
        /* There must be more data to decompress.  */
    }

  if (param->sbb != 0)
    {
      /* The deflate stream has ended in the middle of a byte.  Go to
         the next byte boundary, so that unzip can read CRC and length.  */
      inptr++;
    }

  /* Set CRC value and update bytes_out for unzip.  */
  setcrc (__builtin_bswap32 (param->cv));
  flush_outbuf ();
  return 0;
}
