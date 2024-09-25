## CS213 gzip class

- This folder contains modified gzip source code that was used in the class

Compiling gzip code:

```bash
cd gzip-1.13
./configure
make CFLAGS=-DDEBUG
cd ..
```

## Compress a file

```bash
./gzip-1.13/gzip -kf name.txt
```

## Decompress a file

```bash
./gzip-1.13/gzip -dkf -vv name.txt.gz
```

## Inspecting bitwise content of a file

```bash
xxd -b name.txt.gz
```

## Analysis of content of name.txt.gz

```plaintext
00000000: 00011111 10001011 00001000 00001000 00000101 01001101  .....M
          |- magic number-| |-algo-| |Fflags| |---time stamp---
00000006: 00010010 01100101 00000000 00000011 01101110 01100001  .e..na
          ----------------| |Cflags| |--OS--| |---file name----
0000000c: 01101101 01100101 00101110 01110100 01111000 01110100  me.txt
          -----------------------------------------------------
00000012: 00000000 01001011 01001100 00101010 01001010 01001100  .KL*JL
          -------| |-------- Deflate output -------------------
00000018: 01001110 01001100 01001001 00000100 01010010 01011100  NLI.R\
          -----------------------------------------------------
0000001e: 00000000 01000101 11001010 11000101 01100111 00001100  .E..g.
          -------| |--- check sum (CRC-32)-----------| |-------
00000024: 00000000 00000000 00000000                             ...
          uncompressed filesize----|
```

Fflags == file flags

`0x01 FTEXT` If set the uncompressed data needs to be treated as text instead
of binary data. This flag hints end-of-line conversion for
cross-platform text files but does not enforce it.

`0x02 FHCRC` The file contains a header checksum (CRC-16)

`0x04 FEXTRA` The file contains extra fields

`0x08 FNAME` The file contains an original file name string

`0x10 FCOMMENT` The file contains comment

`0x20` Reserved

`0x40` Reserved

`0x80` Reserved

Cflags == Compression flags

TODO: find detailed understaning

### Deflate output

```plaintext
01001011 01001100 00101010 01001010 01001100
--a-|FFS --b-||-- --r-||-- --a-||-- --c-||--

01001110 01001100 01001001 00000100 01010010 01011100 00000000
--a-||-- --d-||-- --a-||-- -7--||-- |--3-||- |--end-| ||
```

## Other files to try

```plaintext
a.txt
b.txt
ab.txt
```

TODO: Generate a random file and try to compress
