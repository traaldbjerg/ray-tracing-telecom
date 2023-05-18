reset
set pm3d explicit
set pm3d map
set title "Répartition de puissance totale reçue par un récepteur lambda/2 dans l'usine (dBm)"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "dBm"
set nokey
set xrange [-10:105]
set yrange [-80:5]
set zrange [-80:50]
set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0,  6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
splot "exposition.dat" using 1:2:3 with pm3d, "walls.dat" using 1:2:(-70) w lines
