BuildSystemsBenchmark
=====================

A simple benchmark for various building systems.

Usage:

```bash
$ ./GenerateSourceFiles.py

$ cmake -G"Ninja" .
$ time ninja -j4 > /dev/null

real    3m20.980s
user    11m58.253s
sys     1m9.719s

$ ls -A | grep -v "GenerateSourceFiles.py\|CMakeLists.txt\|src" | xargs rm -Rf

$ cmake -G"Unix Makefiles" .
$ time make -rR -j4 > /dev/null

real    4m21.200s
user    12m32.059s
sys     1m17.818s
```
