# filename: plot_tlb.gnuplot

set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'tlb_access_time.png'

set title 'TLB Access Time vs Number of Pages'
set xlabel 'Number of Pages (NUMPAGES)'
set ylabel 'Access Time (nanoseconds)'

set logscale x 2          # Log scale base 2 on X axis, since you double NUMPAGES each step
set grid

plot 'tlb_results.txt' using 1:2 with linespoints lt rgb 'blue' lw 2 pt 7 title 'Access Time'