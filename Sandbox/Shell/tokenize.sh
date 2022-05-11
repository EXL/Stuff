#!/bin/bash
OLDIFS=$IFS
string=$1
IFS='.'
string_array=($string)
len=$(( ${#string_array[@]} - 1 ))
IFS=$OLDIFS
echo ${string_array[$len]}
