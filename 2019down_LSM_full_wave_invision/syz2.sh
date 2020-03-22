

c++ model0.cpp -o m0.cx
./m0.cx


for ((k=1;k<=10;k++))
do

for((j=0;j<=5;j++))
do
for ((i=1;i<=20;i++))
do
c++ new_sm2.cpp -o forward2_$[i].cx
    echo \
    801 \
    200 \
    2500 \
    10 \
    10 \
    0.001 \
    1 \
    1 \
    $[$[i]*5+$[j]*20*5+95] \
    40 \
    1 \
    1 \
    0 \
    300 \
    40 \
    $[$[i]*5+$[j]*20*5+95] | nohup ./forward2_$[i].cx &
done
wait
done

c++ ddwave.cpp -o ddwave.cx
for ((i=1;i<=120;i++))
do
    echo \
    $[$[i]*5+95] \
    801 \
    2500 | ./ddwave.cx
done

for((j=0;j<=5;j++))
do
for ((i=1;i<=20;i++))
do
c++ new_sm3_dj.cpp -o forward3_$[i].cx
    echo \
    801 \
    200 \
    2500 \
    10 \
    10 \
    0.001 \
    1 \
    4 \
    $[$[i]*5+$[j]*20*5+95] \
    40 \
    0 \
    0 \
    0 \
    300 \
    40 \
    $[$[i]*5+$[j]*20*5+95] | nohup ./forward3_$[i].cx &
done


wait
done

c++ new_zdj.cpp -o dj.cx

    echo \
    100 \
    120 \
    5 \
    801 \
    200 \
    2500 | ./dj.cx

c++ ddmodel.cpp -o ddmodel.cx

    echo \
    801 \
    200 | ./ddmodel.cx

done



