// compiler parametr: g++ -O4 name.cpp -lgmpxx -lgmp -pthread -std=c++11
#include <math.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include <gmpxx.h>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <thread>
#include <future>

using namespace std;

void write_file(string str){
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

void naiti_prostie_menshe(vector <mpz_class> &prostie, unsigned long long int n){
       vector <unsigned char> vsen(n+1);
       int i = 0;
       // 1 = False
       // 0 = True
       int koren = sqrt(float(n));
       int p = 2;
       while(p <= koren){
               prostie.push_back(p);
               for (i=p; i < (n+1); i += p){
                       vsen[i] = 1;
               }
               for (i=p; i < (n+1); i ++){
                       if (vsen[i] == 0){
                               p = i;
                               break;
                       }
              }
       }
       for (i = p; i < (n+1); i++){
               if (vsen[i] == 0){
                       prostie.push_back(i);
               }
       }
}


vector <mpz_class> slice(vector<mpz_class>& v, unsigned int start = 0, unsigned int end = -1) {
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
        v[start+i] = 0; //bit saves memory
    }
    return nv;
}

void group(vector <mpz_class>& iterable, vector<vector<mpz_class>>& a, int count){
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

mpz_class poizvedenie(vector <mpz_class> &chisla, int razmer_grupi = 2){
  //razmer_grup -- can not be less 2
  if(chisla.size() == 0){
    mpz_class ss;
    return ss;
  }
  vector<vector<mpz_class>> grupi;
  int kolichestvo_group = chisla.size() / razmer_grupi;
  if (kolichestvo_group == 0){
    kolichestvo_group = 1;
  } else if(kolichestvo_group > 4096){
    kolichestvo_group = 4096;
  }
  group(chisla, grupi, kolichestvo_group);

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
    std::cout << "Zakonchili umnozhati" << '\n';
    return otveti[0];

  }else{
    grupi.clear();
    thread_list.clear();
    return poizvedenie(otveti);
  }
}

unsigned long long int kagda_zakonchiti(vector <mpz_class> &prostie, unsigned long long potolok){
      unsigned int c;
      for (int i = 0; i != prostie.size(); i++){
              c = prostie[i].get_ui();
              if((c * c) > potolok){
                break;
              }
      }
      return c;
}

mpz_class glav(unsigned long long dokuda){
      std::cout << "Shitaem primes" << '\n';
      vector <mpz_class> prostie;
      naiti_prostie_menshe(prostie, dokuda);
      std::cout << "zakonchili shitati primes" << '\n';
      std::cout << "dobavlyaem list" << '\n';
      unsigned long long int ae = kagda_zakonchiti(prostie, dokuda);
      for (int i = 0; i != prostie.size(); i++){
              unsigned int j = prostie[i].get_ui();
              if(ae == j){
                break;
              }
              unsigned int k = 1;
              while (true) {
                k *= j;
                if(k * j <= dokuda){
                  prostie.push_back(j);
                } else{
                  break;
                }
              }
      }
      //std::cout << prostie.size() << '\n';
      sort(prostie.begin(), prostie.end());
      std::cout << "zakinchili dobavlyati list" << '\n';
      std::cout << "Umnozhaem" << '\n';
      return poizvedenie(prostie);
}

int main (){
        // 2520 is the smallest number that can be divided by each of the
        // numbers from 1 to 10 without any remainder.
        // What is the smallest positive number that is evenly divisible
        // by all of the numbers from 1 to n?
        int n = 100;
        int start_time = time_time();
        write_file(glav(100).get_str());
        //std::cout << glav(100) << '\n';
        cout << time_time() - start_time <<"\n";
        //cout << Proi;
}
