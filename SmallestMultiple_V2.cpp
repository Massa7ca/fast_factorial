// compiler parameter: g++ -O4 name.cpp -lgmpxx -lgmp -pthread -std=c++11
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

void naiti_prostie_menshe(vector <mpz_class> &prostie, unsigned long long int n){
       vector <unsigned char> vsen(n+1);
       unsigned long int i = 0;
       // 1 = False
       // 0 = True
       unsigned int koren = sqrt(float(n));
       unsigned long int p = 2;
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
        //v[start+i] = 0; // bit saves memory
    }
    return move(nv);
}

void peremnozh(const vector <mpz_class>&& chisla, vector <mpz_class>& otveti, int thread_n){
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
  while (true) {
    int size_group = chisla.size() / 2;
    vector<mpz_class> otveti(size_group);
    int ss = chisla.size() / size_group;
    int b = 0;
    for(int i = 1; i != size_group; i++){
      peremnozh(slice(chisla, b, ss * i), otveti, i);
      b = ss * i;
    }
    peremnozh(slice(chisla, b), otveti, 0);
    if(otveti.size() == 1){
      chisla.clear();
      otvetiL1[thread_n] = otveti[0];
      otveti.clear();
      //std::cout << otveti[0] << '\n';
      break;
    }else{
      chisla.clear();
      chisla = move(otveti);
    }
  }
}

mpz_class poizvedenieL1(vector <mpz_class> &chisla, int thread_count = 2){
  // multiplies a vector of numbers
  while (true) {
    if(thread_count >= chisla.size() / 2){
      thread_count = chisla.size() / 2;
    }
    vector<mpz_class> otveti(thread_count);
    vector<thread> thread_list(thread_count);
    int ss = chisla.size() / thread_count;
    int b = 0;
    for(int i = 1; i != thread_count; i++){
      //pokazhi_list(slice(chisla, b, ss * i));
      thread_list[i] = thread (poizvedenieL2, slice(chisla, b, ss * i), ref(otveti), i);
      b = ss * i;
    }
    //pokazhi_list(slice(chisla, b));
    thread_list[0] = thread (poizvedenieL2, slice(chisla, b), ref(otveti), 0);
    for(int i = 0; i != thread_list.size(); i++){
      thread_list[i].join();
    }
    if(otveti.size() == 1){
      thread_list.clear();
      chisla.clear();
      cout << "Zakonchili umnozhati" << '\n';
      return otveti[0];
    }else{
      //cout << "" << '\n';
      chisla.clear();
      thread_list.clear();
      chisla.clear();
      chisla = move(otveti);
    }
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

mpz_class glav(unsigned long long dokuda, int thread_count = 2){
      cout << "Shitaem primes" << '\n';
      vector <mpz_class> prostie;
      naiti_prostie_menshe(prostie, dokuda);
      cout << "zakonchili shitati primes" << '\n';
      cout << "dobavlyaem list" << '\n';
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
      //cout << prostie.size() << '\n';
      cout << "zakinchili dobavlyati list" << '\n';
      cout << "Umnozhaem" << '\n';
      return poizvedenieL1(prostie, thread_count);
}

int main (){
        // 2520 is the smallest number that can be divided by each of the
        // numbers from 1 to 10 without any remainder.
        // What is the smallest positive number that is evenly divisible
        // by all of the numbers from 1 to n?
        int n = 1000000000;
        int start_time = time_time();
        glav(n, 4);
        //write_file(glav(n, 4).get_str());
        cout << time_time() - start_time <<"\n";
}
