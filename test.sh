#!/usr/bin/bash

counter=0

for i in {1..12}
do  
    ./proj3 1 1 sample_input/input_${i}
    ourOutput="./output/result-1-1-input_${i}"
    sampleOutput="./sample_output/result-1-1-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then 
        counter=$((counter+1))
        echo "result-1-1-input_${i} Matched" 
    else
        echo "result-1-1-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 1 12 sample_input/input_${i}
    ourOutput="./output/result-1-12-input_${i}"
    sampleOutput="./sample_output/result-1-12-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then 
        counter=$((counter+1))
        echo "result-1-12-input_${i} Matched" 
    else
        echo "result-1-12-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 1 16 sample_input/input_${i}
    ourOutput="./output/result-1-16-input_${i}"
    sampleOutput="./sample_output/result-1-16-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-1-16-input_${i} Matched" 
    else
        echo "result-1-16-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 1 4 sample_input/input_${i}
    ourOutput="./output/result-1-4-input_${i}"
    sampleOutput="./sample_output/result-1-4-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-1-4-input_${i} Matched" 
    else
        echo "result-1-4-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 1 5 sample_input/input_${i}
    ourOutput="./output/result-1-5-input_${i}"
    sampleOutput="./sample_output/result-1-5-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-1-5-input_${i} Matched" 
    else
        echo "result-1-5-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 1 8 sample_input/input_${i}
    ourOutput="./output/result-1-8-input_${i}"
    sampleOutput="./sample_output/result-1-8-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-1-8-input_${i} Matched" 
    else
        echo "result-1-8-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 1 sample_input/input_${i}
    ourOutput="./output/result-2-1-input_${i}"
    sampleOutput="./sample_output/result-2-1-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-1-input_${i} Matched" 
    else
        echo "result-2-1-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 12 sample_input/input_${i}
    ourOutput="./output/result-2-12-input_${i}"
    sampleOutput="./sample_output/result-2-12-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-12-input_${i} Matched" 
    else
        echo "result-2-12-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 16 sample_input/input_${i}
    ourOutput="./output/result-2-16-input_${i}"
    sampleOutput="./sample_output/result-2-16-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-16-input_${i} Matched" 
    else
        echo "result-2-16-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 4 sample_input/input_${i}
    ourOutput="./output/result-2-4-input_${i}"
    sampleOutput="./sample_output/result-2-4-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-4-input_${i} Matched" 
    else
        echo "result-2-4-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 5 sample_input/input_${i}
    ourOutput="./output/result-2-5-input_${i}"
    sampleOutput="./sample_output/result-2-5-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-5-input_${i} Matched" 
    else
        echo "result-2-5-input_${i} ERROR"  
    fi;
done


for i in {1..12}
do  
    ./proj3 2 8 sample_input/input_${i}
    ourOutput="./output/result-2-8-input_${i}"
    sampleOutput="./sample_output/result-2-8-input_${i}"

    str1=$(cat "$ourOutput") 
    str2=$(cat "$sampleOutput") 
    
    if [ "$str1" = "$str2" ]; then
        counter=$((counter+1))
        echo "result-2-8-input_${i} Matched" 
    else
        echo "result-2-8-input_${i} ERROR"  
    fi;
done

echo "TESTCASES PASSED: ${counter}/144"

