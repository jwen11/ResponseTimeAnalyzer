##A response time analyzer for the proposed SCE with Communication.
##USAGE: ./analyzer  [taskset] [communication_graph]  [server_config]



#### Here are sample format for each inputs, please make sure that at each line,
#### the last number should be directly followed by an endline or EOF character

%%%%%TaskFile format:
%Number of CPUs
2
%Meesgaes
%CPU  ID  C    T  [D] [P]
0     1   7   29
0     2   5   14
1     3   5   14


%%%%%MessageFile format:
%Meesgaes
%ID From To Size [Period] [Priority_IN] [Priority_OUT] 
1   1   3   29
2   2   3   29


%%%%%ConfigFile format:
%Number of CPUs
2
%TDMA Period
10
%size_in    size_out   slot   
2048   2048  1
2048   2048  1
