reset
set pm3d explicit
set pm3d map
set title "Répartition du débit binaire dans l'usine (Mb/s)"
set xlabel "x (m)"
set ylabel "y (m)"
set zlabel "Mb/s"
set nokey
set xrange [-10:105]
set yrange [-80:5]
set zrange [100:350]
set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0,  6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
splot "debit.dat" using 1:2:3 with pm3d, "walls.dat" using 1:2:(120) w lines
