#!/bin/bash
i=0;j=10
while (("$i" < "$j"))
do
    printf "$i | "
    let "i++"
done

printf "\n"
