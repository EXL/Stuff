#!/bin/sh
swap () {
    local x=\$"$1"
    local y=\$"$2"
    local valueofx=`eval "expr \"$x\" "`
    local valueofy=`eval "expr \"$y\" "`
    eval "$1=\"$valueofy\""
    eval "$2=\"$valueofx\""
}

a=4
b=2
c=8

echo "Before swapping"
echo "a="$a "b="$b "c="$c"\n"

swap a b

echo "Swap #1 (a <-> b)"
echo "a="$a "b="$b "c="$c"\n"

swap c a

echo "Swap #2 (c <-> a)"
echo "a="$a "b="$b "c="$c"\n"
