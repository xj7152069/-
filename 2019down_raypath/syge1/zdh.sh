c++ srs.cpp -o cx_1
./cx_1

c++ model_true.cpp -o cx_2
./cx_2
mpirun -np 5 ./first_raytracing_liu

c++ model0.cpp -o cx_3
./cx_3

c++ z_ddge.cpp -o cx_4
./cx_4

