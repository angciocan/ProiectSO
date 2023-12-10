#!/bin/bash

#Verificarea ca scriptul a primit un argument
if test $# -ne 1
then
    echo "Scriptul nu a primit un argument" 
    exit 0
fi

regex="^[A-Z].+[a-zA-Z1-9 ,.!?]+[.?!]$"

char=$1 #caracterul este primul argument

contor=0 #numarul de propozitii corecte care contin caracterul dat ca primul argument

#Citirea liniilor de la tastatura pana la intalnirea lui EOF

while read -r propozitie || [ -n "$propozitie" ]
do
    if [[ "$propozitie" == *"$char"* ]];
    then
        if [[ "$propozitie" =~ $regex ]]
	then
	    ((contor++))
	fi
    fi
done

echo "Numarul de propozitii care sunt corecte si contin caracterul dat ca argument etse $contor"
