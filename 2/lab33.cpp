#include <iostream>

using namespace std;

int main()
{
//system("gnuplot -persist -e \"set xlabel 'log10(|blad wzgledny|)'; set ylabel 'log10(x)'; set parametric; set trange [-30:10]; plot log10(2.22045e-16)' t, 'data.txt\"");
//system("gnuplot -persist -e \"set xlabel '|blad wzgledny|'; set ylabel 'x'; set logscale xy; set parametric; set trange [-30:10]; plot 2.22045e-16, t, 'data.txt'\"");
//system("gnuplot -persist -e \"set xlabel 'log10(x)'; set ylabel 'log10(|blad wzgledny|)'; set logscale xy; set trange [-30:10]; plot 2.22045e-16, 'data1.txt'\"");
system("gnuplot -persist -e \"set xlabel 'log10(x)'; set ylabel 'log10(|blad wzgledny|)'; set logscale xy; set trange [-30:10]; plot 2.22045e-16, 'data1.txt'\"");
//system("gnuplot -persist -e \"set xlabel 'log10(|blad wzgledny|)'; set ylabel 'log10(x)'; set logscale xy; set parametric; set trange [-30:10]; plot 2.22045e-16, t, 'data1.txt'\"");	 	 	
//system("gnuplot -persist -e \"set xlabel 'log10(|blad wzgledny|)'; set ylabel 'log10(x)';set parametric;set logscale xy 10;set trange [-30:10];plot log10(2.22045e-16), t, 'data.txt'\"");
//system("gnuplot -persist -e \"set xlabel 'log10(x)'; set ylabel 'log10(blad)';plot 'wynik.txt'\"");
//system("gnuplot -persist -e \"set xlabel 'log10(|blad wzgledny|)';set logscale xy 10;set ylabel 'log10(x)';plot log10(2.22045e-16),'data.txt'\"");
//system("PAUSE");
return 0;	//
}
