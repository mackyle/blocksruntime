==============
Blocks Runtime
==============
This project provides a convenient way to install the BlocksRuntime library
from the compiler-rt project (see http://compiler-rt.llvm.org/).

Several systems (Linux, FreeBSD, MacPorts, etc.) provide the clang compiler
either preinstalled or as an available package which has Blocks support
(provided the -fblocks compiler option is used).

Unfortunately, those installer packages do not provide the Blocks runtime
library.

On the other hand, the compiler-rt library can be downloaded and does contain
the Blocks runtime support if properly enabled in the cmake build file.

By default, however, the compiler-rt library also builds a compiler runtime
support library which is undesirable.

This project contains only the BlocksRuntime files (in the BlocksRuntime
subdirectory) along with tests (in the BlocksRuntime/tests subdirectory) and
the original CREDITS.TXT, LICENSE.TXT and README.txt from the top-level
compiler-rt project (which have been placed in the BlocksRuntime subdirectory).

-------
License
-------
The compiler-rt project (and hence the BlocksRuntime since it's a part of that
project) has a very liberal dual-license of either the UIUC or MIT license.
The MIT license is fully GPL compatible (and pretty much compatible with just
about everything), so there should be no problems linking the
libBlocksRuntime.a library with your executable.  (Note that on the FSF's site
[http://www.gnu.org/licenses/license-list.html], you find the MIT license under
the 'X11 License' section.)  See the LICENSE.TXT file in the BlocksRuntime
subdirectory for all the details.

--------
Building
--------
Since there are only two files to build, a makefile didn't seem warranted.  A
special config.h file has been created to make the build work.  Build the
libBlocksRuntime.a library by running:

  ./buildlib

The gcc compiler will be used by default, but you can do "CC=clang ./buildlib"
for example to use the clang compiler instead.  Note that neither make nor
cmake are needed (but ar and ranlib will be used but they can also be changed
with the AR and RANLIB environment variables similarly to the way the compiler
can be changed).

IMPORTANT Mac OS X Note:  If you are building this library on Mac OS X
(presumably to use with a clang built with MacPorts or otherwise obtained), you
probably want a fat library with multiple architectures in it.  You can do that
with the CFLAGS variable like so:

  CFLAGS='-O2 -arch x86_64 -arch ppc64 -arch i386 -arch ppc' ./buildlib

-------
Testing
-------
Skip this step at your peril!  It's really quite painless.  You see it's
possible that the underlying blocks ABI between the blocks runtime files
provided in this project and the blocks ABI used by your version of the clang
compiler to implement the -fblocks option have diverged in an incompatible way.
If this has happened, at least some of the tests should fail in spectacular
ways (i.e. bus faults).  For that reason skipping this step is not recommended.

You must have the clang compiler with -fblocks support installed for this step
(if you don't have a clang compiler with -fblocks support available, why bother
installing the Blocks runtime in the first place?)  Run the tests like so:

  ./checktests

Problems are indicated with a line that starts "*** ^FAILURE:".  You will
probably see one of these when the copy-block-literal-rdar6439600.c test is
run.  Yes, this is a real failure.  No it's not a bug in the Blocks runtime
library, it's actually a bug in clang.  You may want to examine the
copy-block-literal-rdar6439600.c source file to make sure you fully grok the
failure so you can avoid getting burned by it in your code.  There may be a fix
in the clang project by now (but as of the clang 3.0 release it still seems to
fail), however it may be a while until it rolls downhill to your clang package.

Note that if you have an earlier version of clang (anything before version 2.8
see clang -v) then clang++ (C++ support) is either incomplete or missing and
the few C++ tests (.C extension) will be automatically skipped (if clang++ is
missing) or possibly fail in odd ways (if clang++ is present but older than
version 2.8).

----------
Installing
----------
Assuming that you have built the library (with ./buildlib) and are satisfied it
works (./checktests) then it can be installed with:

  sudo ./installlib

The default installation prefix is /usr/local, but can be changed to /myprefix
like so:

  sudo sh -c 'prefix=/myprefix ./installlib'

The include file (Block.h) is installed into $prefix/include and the library
(libBlocksRuntime.a) into $prefix/lib by default.  (Those can also be changed
by setting and exporting includedir and/or libdir in the same way prefix can be
changed.)

If you want to see what will be installed without actually installing use:

  ./installlib --dry-run

-----------
Sample Code
-----------
After you have installed the Blocks runtime header and library, you can check
to make sure everything's working by building the sample.c file.  The
instructions are at the top of the file (use head sample.c to see them) or
just do this:

  clang -o sample -fblocks sample.c -lBlocksRuntime && ./sample

If the above line outputs "Hello world 2" then your Blocks runtime support is
correctly installed and fully usable.  Have fun!

Note that it's possible to use the Blocks runtime without installing it into
the system directories.  You simply need to add an appropriate -I option to
find the Block.h header when you compile your source(s).  And a -L option to
find the libBlocksRuntime.a library when you link your executable.  Since
libBlocksRuntime.a is a static library no special system support will be needed
to run the resulting executable.

-------------
Documentation
-------------
You can find information on the Blocks language extension at these URLs

  http://clang.llvm.org/docs/LanguageExtensions.html#blocks
  http://clang.llvm.org/docs/BlockLanguageSpec.txt
  http://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/Blocks
  http://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/Blocks/Blocks.pdf
