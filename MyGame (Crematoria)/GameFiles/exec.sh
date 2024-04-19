#!/bin/bash

i=1
while [ $i -le 100 ]
do
  echo $i
  ./Game SterrySX Dummy Dummy Dummy -i default.cnf -o output/default-auto-$i.res -s "$i" 2> >(grep "score")
  ((++i))
done

#./exec.sh > stats &
