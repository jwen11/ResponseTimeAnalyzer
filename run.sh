cd daggen-master-rtmod   # Change directory to the daggen task

./daggen -n 10 --minT=10 --maxT=100 --minC=1 --maxC=2 --sendBudget=10 --recvBudget=10 --cpus=2 --tasks 

cd ../



cp daggen-master-rtmod/*.txt testbench/test1/

./analyser testbench/test1/task.txt  testbench/test1/message.txt  testbench/test1/configs.txt