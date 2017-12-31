# 2520 is the smallest number that can be divided by each of the
# numbers from 1 to 10 without any remainder.
# What is the smallest positive number that is evenly divisible
# by all of the numbers from 1 to n?
from gmpy2 import mpz
import time
import math
import multiprocessing

def naiti_prostie_menshe(n):
  lim = n
  # cas particuliers
  if lim<7:
    if lim<2: return []
    if lim<3: return [2]
    if lim<5: return [2, 3]
    return [2, 3, 5]
  #  Crible
  n = (lim-1)//30
  m = n+1
  BA = bytearray
  prime1 = BA([1])*m
  prime7 = BA([1])*m
  prime11 = BA([1])*m
  prime13 = BA([1])*m
  prime17 = BA([1])*m
  prime19 = BA([1])*m
  prime23 = BA([1])*m
  prime29 = BA([1])*m
  prime1[0] = 0
  i = 0
  try:
    while 1:
      if prime1[i]:
        p = 30*i+1
        l = i*(p+1)
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*6
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*4
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*2
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*4
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*2
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*4
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*6
        prime29[l::p] = BA(1+(n-l)//p)
      if prime7[i]:
        p = 30*i+7
        l = i*(p+7)+1
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*4+1
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*4
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*4+1
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*6+1
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime7[l::p] = BA(1+(n-l)//p)
      if prime11[i]:
        p = 30*i+11
        l = i*(p+11)+4
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*2
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*2
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*6+2
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*6+2
        prime17[l::p] = BA(1+(n-l)//p)
      if prime13[i]:
        p = 30*i+13
        l = i*(p+13)+5
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*4+1
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*6+3
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*6+3
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*4+1
        prime23[l::p] = BA(1+(n-l)//p)
      if prime17[i]:
        p = 30*i+17
        l = i*(p+17)+9
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*4+3
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*6+3
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*6+3
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*4+3
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime11[l::p] = BA(1+(n-l)//p)
      if prime19[i]:
        p = 30*i+19
        l = i*(p+19)+12
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*6+4
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*6+4
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*2+2
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*4+2
        prime23[l::p] = BA(1+(n-l)//p)
      if prime23[i]:
        p = 30*i+23
        l = i*(p+23)+17
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*6+5
        prime7[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*6+5
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*4+3
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*4+4
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime17[l::p] = BA(1+(n-l)//p)
      if prime29[i]:
        p = 30*i+29
        l = i*(p+29)+28
        prime1[l::p] = BA(1+(n-l)//p)
        l += i*2+1
        prime29[l::p] = BA(1+(n-l)//p)
        l += i*6+6
        prime23[l::p] = BA(1+(n-l)//p)
        l += i*4+4
        prime19[l::p] = BA(1+(n-l)//p)
        l += i*2+2
        prime17[l::p] = BA(1+(n-l)//p)
        l += i*4+4
        prime13[l::p] = BA(1+(n-l)//p)
        l += i*2+2
        prime11[l::p] = BA(1+(n-l)//p)
        l += i*4+4
        prime7[l::p] = BA(1+(n-l)//p)
      i+=1
  except:
    pass
  #  generation
  RES = [2, 3, 5]
  A = RES.append
  ti=0
  try:
    for i in range(n):
      if prime1[i]:
        A(ti+1)
      if prime7[i]:
        A(ti+7)
      if prime11[i]:
        A(ti+11)
      if prime13[i]:
        A(ti+13)
      if prime17[i]:
        A(ti+17)
      if prime19[i]:
        A(ti+19)
      if prime23[i]:
        A(ti+23)
      if prime29[i]:
        A(ti+29)
      ti+=30
  except:
    pass
  if prime1[n] and (30*n+1)<=lim:
    A(30*n+1)
  if prime7[n] and (30*n+7)<=lim:
    A(30*n+7)
  if prime11[n] and (30*n+11)<=lim:
    A(30*n+11)
  if prime13[n] and (30*n+13)<=lim:
    A(30*n+13)
  if prime17[n] and (30*n+17)<=lim:
    A(30*n+17)
  if prime19[n] and (30*n+19)<=lim:
    A(30*n+19)
  if prime23[n] and (30*n+23)<=lim:
    A(30*n+23)
  if prime29[n] and (30*n+29)<=lim:
    A(30*n+29)
  return RES

def to_file(string, name):
    f = file(name, "w")
    f.write(string)
    f.close()

def peremnozh(listt):
    if len(listt) == 1:
        return listt[0]
    s = mpz(1)
    for i in listt:
        s *= i
    return s

def perL1(listt, tread_n=-1, return_dict=None):
    kol_v_gruppe = 15
    countONgrup = 2
    index = 0
    while True:
        index += 1
        if kol_v_gruppe >= index:
            countONgrup = kol_v_gruppe / index
            if countONgrup == 1:
                countONgrup = 2
        kol_group = len(listt) / countONgrup
        if kol_group == 0:
            kol_group = 1
        dlinna_grupi = len(listt) / kol_group
        n_listt = []
        while len(listt) != 0:
            n_listt.append(peremnozh(listt[-dlinna_grupi:]))
            del listt[-dlinna_grupi:]
        listt = n_listt
        if len(listt) == 1:
            if tread_n == -1 and return_dict == None:
                print "Zakonchili umnozhati"
                return listt[0]
            return_dict[tread_n] = listt[0]
            break;

def perL2(listt, thread_count = 1):
    if thread_count == 1:
        return perL1(listt)
    manager = multiprocessing.Manager()
    return_dict = manager.dict()
    countONgrup = 2
    index = 0
    while True:
        if thread_count >= len(listt) / 2:
            thread_count = len(listt) / 2
        thread_list = []
        dlinna_grupi = len(listt) / thread_count
        index = 0
        while len(listt) != 0:
            proces = multiprocessing.Process(target=perL1, args=(listt[-dlinna_grupi:], index, return_dict))
            index += 1
            thread_list.append(proces)
            proces.start()
            del listt[-dlinna_grupi:]
        for proc in thread_list:
            proc.join()

        n_listt = []
        for i in xrange(thread_count):
            n_listt.append(return_dict.values()[i])
        listt = n_listt
        if len(listt) == 1:
            print "Zakonchili umnozhati"
            return listt[0]

def kagda_zakonchiti(prostie, potolok):
    a = 0
    for i in prostie:
        if i*i > potolok:
            return prostie[a]
        a +=1


def glav(dokuda, tread = 1):
    print "shitaem primes"
    prostie = naiti_prostie_menshe(dokuda)
    print "zakonchili shitati primes"
    print "dobavlyaem list"
    ae =  kagda_zakonchiti(prostie,dokuda)
    for j in prostie:
        if ae == j:
            break
        k = 1
        while True:
            k *= j
            if k*j <= dokuda:
                prostie.append(j)
            else:
                break
    print "zakinchili dobavlyati list"
    print "Umnozhaem"
    return perL2(prostie, tread)

n = time.time()
st = str(glav(2000000000, 3))
to_file(st, "110.txt")
print time.time() - n
