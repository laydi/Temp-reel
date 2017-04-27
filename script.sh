#!/bin/sh

cd /home/lydia/Bureau/temp-reel/fractal

N=100

for (( i=1 ; i<=N ; i++))
do
      #./main
       make # compilation et exécution du programme 
done

##### calcul de la moyenne

awk '{somme+=$1}END{ print "somme = " somme ", moyenne = " somme/(NR)}' test.txt
echo $moyenne >> moyenne.dat
exit 0;


