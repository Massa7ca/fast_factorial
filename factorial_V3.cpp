//sudo ./configure --prefix=/usr --enable-cxx --enable-mpbsd --enable-mpfr && sudo make && sudo make install
//sudo ./configure --enable-cxx --enable-mpbsd --enable-mpfr && sudo make && sudo make install
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

void pokazhi_list(vector <mpz_class> list){
       int i;
       cout << "[";
       for (i = 0; i != list.size(); i++){
               mpz_class c = list[i];
               if (i != (list.size()-1)){
                       cout << c << ", ";
               }
               else{
                       cout << c;
               }
       }
       cout << "]" << "\n";
}

void slice(vector<mpz_class>& chisla, vector<mpz_class>& nv, int start, int newlen) {
    for (int i = 0; i < newlen; i++) {
        nv[i] = chisla[start+i];
    }
}

void peremnozh(const vector <mpz_class>& chisla, vector <mpz_class>& otveti, int thread_n){
  mpz_class ss;
  ss = "1";
  for(int i = 0; i != chisla.size(); i++){
    ss = ss * chisla[i];
  }
  otveti[thread_n] = ss;
}

void poizvedenieL2(vector <mpz_class> &&chisla, vector <mpz_class>& otvetiL1, int thread_n){
  // razmer_grup -- can not be less 2
  // multiplies a vector of numbers
  int newlen = 0, ss = 0, start = 0;
  vector<mpz_class> otveti;
  vector<mpz_class> grup;
  const int kol_v_gruppe = 14;
  int countONgrup = 2;
  int index = 0;
  while (true){
    index++;
    if(kol_v_gruppe >= index){
      countONgrup = kol_v_gruppe / index;
      if(countONgrup == 1){
        countONgrup = 2;
      }
    }
    int size_group = chisla.size() / countONgrup;
    if(size_group == 0){
      size_group = 1;
    }
    otveti.resize(size_group);
    ss = chisla.size() / size_group;
    if(grup.size() != ss){
      grup.resize(ss);
    }
    start = 0;
    for(int i = 1; i != size_group; i++){
      slice(chisla, grup, start, ss);
      peremnozh(grup, otveti, i);
      start = ss * i;
    }
    int _a_ = chisla.size() - start;
    if(grup.size() != _a_){
      grup.resize(_a_);
    }
    slice(chisla, grup, start, _a_);
    peremnozh(grup, otveti, 0);
    if(otveti.size() == 1){
      chisla.clear();
      otvetiL1[thread_n] = otveti[0];
      break;
    }else{
      //std::cout << '\n';
      chisla = move(otveti);
    }
  }
}

mpz_class poizvedenieL1(vector <mpz_class> &chisla, int thread_count = 2){
  // multiplies a vector of numbers
  int newlen = 0, ss = 0, start = 0;
  vector<mpz_class> otveti;
  vector<thread> thread_list;
  vector<mpz_class> grup;
  while (true) {
    if(thread_count >= chisla.size() / 2){
      thread_count = chisla.size() / 2;
    }
    otveti.resize(thread_count);
    thread_list.resize(thread_count);
    ss = chisla.size() / thread_count;
    if(grup.size() != ss){
      grup.resize(ss);
    }
    start = 0;
    for(int i = 1; i != thread_count; i++){
      slice(chisla, grup, start, ss);
      thread_list[i] = thread (poizvedenieL2, grup, ref(otveti), i);
      for (int j = 0; j < ss; j++){
        mpz_class _;
        chisla[start+j] = _;
      }
      start = ss * i;

    }
    int _a_ = chisla.size() - start;
    if(grup.size() != _a_){
      grup.resize(_a_);
    }
    slice(chisla, grup, start, _a_);
    thread_list[0] = thread (poizvedenieL2, grup, ref(otveti), 0);
    chisla.clear();
    for(int i = 0; i != thread_list.size(); i++){
      thread_list[i].join();
    }
    if(otveti.size() == 1){
      return otveti[0];
    } else{
      //cout << "" << '\n';
      chisla = move(otveti);
    }
  }
}

int main(){
  int n = 100000000;
  vector <mpz_class> list; // [1, 2, 3, 4, ... to n]
  for(int i = 1; i != n+1; i++){
    list.push_back(i);
  }
  int start_time = time_time();
  //poizvedenieL1(list, 64);
  //std::cout << poizvedenieL1(list, 64) << '\n';
  write_file(poizvedenieL1(list, 64).get_str());
  cout << "Time " << time_time() - start_time <<"\n";

}
