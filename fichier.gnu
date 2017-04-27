reset
set terminal png
set output "Graphe-Test.png"
set title "temps d'execution en fonction du nombre du thre" 
set xlabel "le nombre du threads" 
set ylabel "le temps en ms"
set xrange [0:17]
set yrange [1500:3000] 
plot  "moyenne.dat" using 2:1 with lines
