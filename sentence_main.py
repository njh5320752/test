#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import sys, os, random

DATA_FILE = "sentence.data"
RETRY_ANSWER_MAX = 3
data_dict = {}

def init():
    fi = open(DATA_FILE, "r")
    for line in fi.readlines():
        array = line.split('/')
        data_dict[array[1].strip()] = array[0].strip()

def practice_do(problme):
    cnt = 0
    while(cnt < RETRY_ANSWER_MAX):
        cnt += 1
        val = raw_input("%s : "%problme)
        if (data_dict[problme] == val):
            return 1
    print "정답 : %s"% data_dict[problme]
    return 0

def practice_start():
    keys = data_dict.keys()
    right_cnt = 0
    while(len(keys) != 0):
        index = random.randrange(0, len(keys))
        right_cnt += practice_do(keys[index])
        keys.remove(keys[index])
    print "총 %d개 맞춘 수 %d개 점수 %d점"%(len(data_dict), right_cnt, right_cnt*100/len(data_dict))

def main():
    init()
    practice_start()

if __name__ == '__main__':
    main()
