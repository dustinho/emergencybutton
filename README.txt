This is libemergencybutton, a library for interacting with some random red
button that Dustin obtained.

== Build instructions ==

=== Prerequisites ===
  * gcc
  * cmake
    * On Windows, install cmake from the cmake webpage <http://www.cmake.org/cmake/resources/software.html>
    * On OSX, install homebrew (see <http://mxcl.github.com/homebrew/>) and brew install cmake
    * On Linux, install cmake from your package manager of choice.

=== Do: ===

cd si_take_down_the_site/ (the folder containing this README.txt)
mkdir build
cd build
cmake ../
make
./bin/consoledemo

== Notes ==

Warning: this library does not handle all error cases.  It ignores a lot of
things that could go wrong, only supports one device at a time, and is sorta
messy.  You have been warned.

That said, it worked in testing for the purpose it was created, so you may find
it useful anyway.
