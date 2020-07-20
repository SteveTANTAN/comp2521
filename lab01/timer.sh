# // steve tan z5237560
# 2020/06/06
# this code is using for different timer to essay calculate values.

#! /usr/bin/env bash

n=10
for var in 5000 10000
do
        #for all the un duplicate.
        echo == fuction : sort, data: $var,  seq: random,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                sort -R < /tmp/nums > /tmp/rand
                time (sort -n < /tmp/rand > /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: random,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                sort -R < /tmp/nums > /tmp/rand
                time (./useIntList < /tmp/rand > /dev/null)
        done


        echo == fuction : sort, data: $var,  seq: SORTED,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                
                time (sort -n < /tmp/nums > /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: SORTED,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                
                time (./useIntList < /tmp/nums > /dev/null)
        done

        echo == fuction : sort, data: $var,  seq: reverse,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                sort -nr < /tmp/nums > /tmp/rand
                time (sort -n < /tmp/rand> /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: reverse,  duplicate: no ==
        for ((i = 0; i < $n; i++))
        do 
                seq $var > /tmp/nums
                sort -nr < /tmp/nums > /tmp/rand
                time (./useIntList < /tmp/rand > /dev/null)
        done

        # for the duplicate
        echo == fuction : sort, data: $var,  seq: random,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                
                time (sort -n < /tmp/nums > /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: random,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                
                time (./useIntList < /tmp/nums> /dev/null)
        done


        echo == fuction : sort, data: $var,  seq: SORTED,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                sort -n < /tmp/nums > /tmp/rand
                time (sort -n < /tmp/rand > /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: SORTED,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                sort -n < /tmp/nums > /tmp/rand
                time (./useIntList < /tmp/rand > /dev/null)
        done

        echo == fuction : sort, data: $var,  seq: reverse,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                sort -nr < /tmp/nums > /tmp/rand
                time (sort -n < /tmp/rand > /dev/null)
        done


        echo == fuction: IntList, data: $var,  seq: reverse,  duplicate: yes ==
        for ((i = 0; i < $n; i++))
        do 
                ./randList $var > /tmp/nums
                sort -nr < /tmp/nums > /tmp/rand
                time (./useIntList < /tmp/rand > /dev/null)
        done

done


        

