# mpi-utils: Use MPI in Shell

This package enables MPI semantics in shell scripting.

## Dependency
* GNU Autotools
* C compiler
* An MPI runtime, e.g. MPICH or Open MPI (actually, just `mpirun`)

## Install
```
$ sh autogen.sh

$ ./configure --prefix=$HOME/bin

$ make install

```

## Usage Examples

```
$ mpirun -n 3 mpi_comm_rank
0
1
2
```

```
$ cat tests/hello.sh
rank=`mpi_comm_rank`
size=`mpi_comm_size`
echo Hello MPI - $rank / $size

$ mpirun -n 3 bash tests/hello.sh
Hello MPI - 2 / 3
Hello MPI - 1 / 3
Hello MPI - 0 / 3
```

## Motivation
MPI is the de-facto runtimes for parallel programming in high performance
computing (HPC). However, its adoption outside the HPC community is very low.
By making MPI semantics available to shell programing, we hope to promote
MPI adoption beyond HPC.

Everywhere need parallel programming. Everywhere can use MPI.

## Two Schools of Parallel Programming
There are two schools of parallel programming, the earthling approach and
the hive mind approach.

### The Earthling Approach
The earthling approach treats individual units in a parallel programming as
individual code with independent programming logic. Programs are individually
launched or spawned; the parallel environment is individually discovered and
established; units assumes different roles in a applications.

Examples:
* The master/worker model
  The master program is first started. Then it forks or spawns multiple worker
  programs or threads as workers, each runs independently from other workers.

* The task dispatching model
  There is a central program as task scheduler and a set of runners waiting.
  Tasks can be generated by a main program or runners. Tasks are assigned to
  individual runners coordinated by the task scheduler. Runners typically
  do not synchronize with other runners.

* The client server model
  There are client programs and server programs, and sometime a connection
  dispatcher program. The client program connects to one of the servers with
  the assistance the dispatcher program. The client program and the server
  program runs different code but in a coordinated way.

### The Hive Mind Approach  

The MPI approach to parallel programming can be described as hive mind. All units
of the parallel computation are launched together, connected, and with a single
programing logic. Units still can run different tasks, or more fittingly,
different parts of task based on inidividual unit id called rank. In code,
this can be realized as an `if-else` branch:
```
if test $rank -eq 0 ; then
    do_job_A
else
    do_job_B
fi
```
And sometime, more often, as collective math:
```
do_job param-$rank
```

A hive mind thinks together. An MPI application is programmed together.

## NOTE

This is not a port or binding of MPI for the shell language. Rather,
it simply allows an MPI-like programming semantics in shell scripting.
In particular, it does not use the actual MPI library. The only runtime
dependency is on the job launcher, i.e. `mpirun`.

## Comparison to GNU Parallel

####  GNU Parallel
```
$ paralell echo ::: `seq 0 7`
0
1
2
3
4
5
6
7
```

`parallel` launches individual programs separately and assigns different input.
The individual programs are not aware of the parallel environment.

####  mpi-utils
```
$ echo t.sh
rank=`mpi_comm_rank`
echo $rank

$ mpirun -n 8 sh t.sh
0
1
2
3
4
7
5
6
```

All MPI units are launched together by specifying the
number of units. All units started with the knowledge of its parallel environment,
and they are programmed as a single code logic.
