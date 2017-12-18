#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <gmpxx.h>
#include <fstream>
#include <future>
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

vector <mpz_class> slice(vector<mpz_class>& v, unsigned int start = 0, int end = -1) {
    int oldlen = v.size();
    int newlen;
    if (end == -1 or end >= oldlen){
        newlen = oldlen-start;
    } else {
        newlen = end-start;
    }
    vector<mpz_class> nv(newlen);
    for (int i = 0; i < newlen; i++) {
        nv[i] = v[start+i];
        v[start+i] = 0; // bit saves memory
    }
    return nv;
}

void group(vector <mpz_class>& iterable, vector<vector<mpz_class>>& a, int count){
    // divides the Vector into groups of vectors
    int ss = iterable.size() / count;
    int b = 0;
    for (int i = 1; i != count; i++){
      a.push_back(slice(iterable, b, ss * i));
      b = ss * i;
    }
    a.push_back(slice(iterable, b));
}

void peremnozh(const vector <mpz_class>&& chisla, vector <mpz_class>& otveti, int thread_n){
  mpz_class ss;
  ss = "1";
  for(int i = 0; i != chisla.size(); i++){
    ss = ss * chisla[i];
  }
  otveti[thread_n] = ss;
}

mpz_class poizvedenie(vector <mpz_class> &chisla, int razmer_grup = 2){
  // razmer_grup -- can not be less 2
  // multiplies a vector of numbers
  if(chisla.size() == 0){
    mpz_class ss;
    return ss;
  }
  vector<vector<mpz_class>> grupi;
  int size_group = chisla.size() / razmer_grup;
  if (size_group == 0){
    size_group = 1;
  } else if(size_group > 8096){
    size_group = 8096;
  }
  group(chisla, grupi, size_group);
  chisla.clear();
  vector<mpz_class> otveti(grupi.size());
  vector<thread> thread_list;
  for(int i = 0; i != grupi.size(); i++){
    thread_list.push_back(thread (peremnozh, grupi[i], ref(otveti), i));
  }
  for(int i = 0; i != thread_list.size(); i++){
    thread_list[i].join();
  }
  if(otveti.size() == 1){
    return otveti[0];

  }else{
    grupi.clear();
    thread_list.clear();
    return poizvedenie(otveti);
  }
}

int main(){
  int n = 50000000;
  vector <mpz_class> list; // [1, 2, 3, 4, ... to n]
  for(int i = 1; i != n+1; i++){
    list.push_back(i);
  }
  int start_time = time_time();
  write_file(poizvedenie(list).get_str());
  //std::cout << glav(100) << '\n';
  cout << time_time() - start_time <<"\n";

}
