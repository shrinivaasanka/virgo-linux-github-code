#!/bin/bash

#Simple utility script for finding files modified in last 'n' days
#- Ka.Shrinivaasan ( Krishna iResearch, kashrinivaasan@gmail.com)

for i in `find . -ctime -1 -type f`
do 
cp --parents -r $i /home/kashrinivaasan/KrishnaiResearch_OpenSource/virgo-linux-code-0/linux-kernel-extensions
done

