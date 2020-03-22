#    /*基本参数*/
#    cout<<"input the width of model"<<endl;
#    cout<<"input the deepth of model"<<endl;
#    cout<<"input the record time"<<endl;
#    cout<<"input the gep of hor -->"<<endl;
#    cout<<"input the gep of vet |"<<endl;
#    cout<<"input the gep of time"<<endl;
#    /*震源模式及是否使用自由表面*/
#    cout<<"input '1' to use surface_PML_boundary"<<endl;
#    cout<<"chose the source model(1-4)"<<endl;
#    cout<<"input the source_X location"<<endl;
#    cout<<"input the source_Y location"<<endl;
#    /*输出文件*/
#    cout<<"input '1' to output movie"<<endl;
#    cout<<"input '1' to output suface data"<<endl;
#    cout<<"input '1' to output forwave"<<endl;
#    cout<<"input the time of output forwave"<<endl;
#    cout<<"input the depth of output suface"<<endl;
#    cout<<"input the source id(should be >0)"<<endl;

c++ model_complex.cpp -o mtrue.cx
./mtrue.cx

for((j=0;j<=5;j++))
do
for ((i=1;i<=20;i++))
do
c++ new_sm.cpp -o forward$[i].cx
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
    0 \
    1 \
    0 \
    300 \
    40 \
    $[$[i]*5+$[j]*20*5+95] | nohup ./forward$[i].cx &
done
wait
done




