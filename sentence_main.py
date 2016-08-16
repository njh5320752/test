#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import sys, os, random

DATA_FILE = "sentence.data"
RETRY_ANSWER_MAX = 2
REVIEW_COUNT = 3
data_dict = {}

def init():
    fi = open(DATA_FILE, "r")
    for line in fi.readlines():
        array = line.split('/')
        data_dict[array[1].strip()] = array[0].strip()

def review_failed(item):
    for x in xrange(REVIEW_COUNT):
        val = raw_input("%s : "%item)
        if (data_dict[item] != val):
            print "정답 : %s"% data_dict[item]

def practice_do(problme):
    cnt = 0
    while(cnt < RETRY_ANSWER_MAX):
        cnt += 1
        val = raw_input("%s : "%problme)
        if (data_dict[problme] == val):
            return 1
    print "정답 : %s"% data_dict[problme]
    return 0

def practice_start(practice_list):
    total_cnt = len(practice_list)

    if (total_cnt == 0):
        return

    right_cnt = 0
    failed_list = []
    while(len(practice_list) != 0):
        index = random.randrange(0, len(practice_list))
        item = practice_list[index]
        if (practice_do(item) == 0):
            failed_list.append(item)
            review_failed(item)
        else:
            right_cnt += 1
        practice_list.remove(item)
    print "총 %d개 맞춘 수 %d개 점수 %d점"%(total_cnt, right_cnt, right_cnt*100/total_cnt)
    practice_start(failed_list)

def main():
    init()
    practice_start(data_dict.keys())

if __name__ == '__main__':
    main()
