#同时打开多个终端，生成模型炮记录
c++ sm6.cpp -o sm

gnome-terminal -- bash -c "g++ sm5.cpp -o sm; echo 3 2 801 200 1200 10 0.001 0 1 2 37 210 200 200 0 0 | ./sm "

gnome-terminal -- bash -c "g++ sm5.cpp -o sm; echo 3 2 801 200 1200 10 0.001 0 1 2 37 286 200 200 0 0 | ./sm "

gnome-terminal -- bash -c "g++ sm5.cpp -o sm; echo 3 2 801 200 1200 10 0.001 0 1 2 37 362 200 200 0 0 | ./sm "

gnome-terminal -- bash -c "g++ sm5.cpp -o sm; echo 3 2 801 200 1200 10 0.001 0 1 2 37 438 200 200 0 0 | ./sm "

gnome-terminal -- bash -c "g++ sm5.cpp -o sm; echo 3 2 801 200 1200 10 0.001 0 1 2 38 514 200 200 0 0 | ./sm "