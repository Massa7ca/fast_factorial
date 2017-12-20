#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <gmpxx.h>
#include <fstream>
#include <future>
//Single core
using namespace std;

void write_file(const string &str){
  FILE *f;
  string a;
  f = fopen("1.txt","w");
  ofstream fout ("1.txt");
  fout << str;
  fclose(f);
}

int time_time(){
  time_t seconds;
  seconds = time (NULL);
  return int(seconds);
}

mpz_class ProdTree(int l, int r)
{
	if (l > r)
		return 1;
	if (l == r)
		return l;
	if (r - l == 1)
		return (mpz_class)r * l;
	int m = (l + r) / 2;
	return ProdTree(l, m) * ProdTree(m + 1, r);
}

mpz_class FactTree(int n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n == 1 || n == 2)
		return n;
	return ProdTree(2, n);
}

int main(){
  int start_time = time_time();
  write_file(FactTree(1000000).get_str());
  //std::cout << glav(100) << '\n';
  cout << time_time() - start_time <<"\n";

}
