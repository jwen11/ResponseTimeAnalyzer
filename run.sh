cd daggen-master-rtmod   # Change directory to the daggen task

./daggen -n 10 --tasks --cpus=2 

cd ../



cp daggen-master-rtmod/*.txt testbench/test1/

./analyser testbench/test1/task.txt  testbench/test1/message.txt  testbench/test1/configs.txt