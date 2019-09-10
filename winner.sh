#!/bin/bash

rm -rf log
if [ "$1" != "" ] && [ -f $1 ]; then
	for champ in resources/champs/*.cor ; do
		echo $champ >> log
		./corewar $1 $champ >> log
		echo "\n==================================\n" >> log
	done
else
		echo "File not found"
fi
