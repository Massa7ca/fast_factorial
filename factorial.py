from gmpy2 import mpz
import time
import math
import multiprocessing

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
        #print kol_group, countONgrup
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
            return listt[0]

a = range(1, 5000000+1)
n = time.time()
perL2(a, 3)
print time.time() - n
