Dinero IV, release 7, 6 February 1998
Send feedback to edler@research.nj.nec.com and markhill@cs.wisc.edu.



INTRODUCTION

Dinero IV is a cache simulator for memory reference traces.
It includes the following major changes over Dinero III:

	- subroutine-callable interface in addition to trace-reading program
	- simulation of multi-level caches
	- simulation of dissimilar I and D caches
	- better performance, especially for highly associative caches
	- classification of compulsory, capacity, and conflict misses
	- support for multiple input formats
	- cleaned up and modernized code, improved portability

Some deep-seated limitations:
- Dinero IV is not a timing simulator.
  There is no notion of simulated time or cycles, only references.
- Dinero IV is not a functional simulator.
  Data & instructions do not move in and out of the caches;
  in fact they don't exist!  The primary result of simulation
  with Dinero IV is hit and miss information.
- Dinero IV isn't multi-threaded.
  If you have a multiprocessor with enough memory,
  you can run multiple independent simulations concurrently.

The basic idea is to simulate a memory hierarchy consisting of various
caches connected as one or more trees, with reference sources
(the processors) at the leaves and a memory at each root.  The various
parameters of each cache can be set separately (architecture, policy,
statistics).  During initialization, the configuration to be simulated
is built up, one cache at a time, starting with each memory as a special
case.  After initialization, each reference is fed to the appropriate
top-level cache by a single simple function call.  Lower levels of the
hierarchy are handled automatically.

At some future time, Dinero IV may be extended to simulate multiprocessors.
In the meantime, there is no support for consistency, so for practical
purposes, the tree of caches will not be very branchy (the only time
where multiple sources will feed into a cache is when separate instruction
and data caches are used).



STRUCTURE AND DOCUMENTATION

The subroutine-callable version of Dinero IV consists of a library
(libd4.a) and a header file (d4.h).  Unix man pages are in d4.[13].

The program dineroIV is implemented by using the subroutine interface.
Run dineroIV -help to see the latest usage summary.

The file NOTES, in this directory, contains some additional information,
comparing Dinero IV with Dinero III, and providing some details
about the internal structure of Dinero IV.

The file CHANGES, in this directory, gives a history of the
changes from one release of Dinero IV to the next.



INSTALLATION

Dinero IV is built with Gnu autoconf, and has been tested with
x86/Linux, Alpha/Linux, Alpha/OSF, SGI/IRIX-6, RS6000/AIX,
x86/Solaris, and Sparc/Solaris.

To build everything:

	./configure
	make

Nothing is installed outside the main directory.
To turn on a bit of additional debugging, configure with --with-debug.



TESTING

To run some fixed tests, go to the testing subdirectory and run

	make
	PATH=$PATH:.. ./testscript
	D4_SRC=.. PATH=$PATH:.. ./testscript -c

(for sh users; csh users probably use "set path=($path ..); set D4_SRC=..").

Note some of the tests produce results dependent on the random number
generator (random()).  This works fine normally, but some systems have
versions of random() that produce a different sequence of numbers,
so the results of some tests will differ from the supposedly good results
already saved for comparison (produced on x86/Linux).  The tests in question
are those with random replacement or a nonzero pfabort value.
