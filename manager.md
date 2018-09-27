Kim is given a task to write a memory manager for a new programming language NK++.
The manager has *N* sequential memory slots numbered 1 to *N*. The task is to parse queries for allocating and freeing memory.  
'Allocate' query has one parameter *K* - how many sequential slots to allocate. The manager has to do it in case it is possible.
The manager has to choose the longest free block of memory available. Among the longest - choose the first one.
In case allocating is not possible - deny the query.  
'Free' query has on parameter *T* - free memory allocated for query nubmer *T* (numbering starts with 1). It is guranteed that
query number *T* was 'allocate' type without any 'free *T*' query yet. If the query nubmer *T* was denied, deny this one as well.

The first line of the input contains two integers *N* and *M* - size of the memory and number of queries
(1 &leq; *N* &leq; 2<sup>31</sup>-1, 1 &leq; *n* &leq; 10<sup>5</sup>). The following *M* lines contain one number, positive
number '*K*' or negative number '-*T*'.  
For each 'allocate' query output position of the first allocated memory slot or '-1' in case of failure.

|input|output|
|-----|------|
|6 8<br>2<br>3<br>-1<br>3<br>3<br>-5<br>2<br>2|1<br>3<br>-1<br>-1<br>1<br>-1<br>|
