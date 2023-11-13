# mpi-utils: Use MPI in Shell

## Introduction
MPI is the de-facto runtimes for parallel jobs in high performance computing (HPC). 
However, its adoption outside the HPC community is very low. We think there may be
following reasons.

* MPI is a C API
* MPI requires setup
* MPI uses different semantics

The first two barriers are accessibility barrier, and the last barrier is a
motivation barrier.
We believe the motivation barrier is the key barrier between MPI and typical non-HPC
users. If users believe in MPI, they will overcome the accessibility barrier.

Traditional approach to parallel programming can be characterized as individual minds work together.
For example, in a master/worker model, the application starts a single program or
a single thread -- a master, then spawns multiple additional programs or threads
each are assigned with different tasks to run in parallel.
For another example, a server/client model, a server program listens, and a different
client program connects. Multiple servers and multiple clients may concurrently run
individual tasks, and they synchronize through a client/server channel.

The MPI approach to parallel programming can be described as hive mind. All units
of the parallel computation are launched together and works on a single thread of
programming logic collectively.

Typical earthlings are not used to hive mind. Thus, MPI appears to be a very alien
concept.

In order to push MPI adoption outside the HPC's ivory tower, we need teach the MPI's
hive mind parallel semantics first. But to teach the MPI semantics, we need solve
the accesibility barrier first.

The most accesible programming platform is the shell. This project aims for adopting MPI
semantics in shell programming.

## NOTE

This is not a port or binding of MPI for the shell language. The goal is not
to allow shell programmers to access an installed MPI library, such as MPICH or
Open MPI. Rather, the goal is merely to enable shell scripts to program in a similar
style as an MPI program. Specificly, individual MPI APIs are individual programs
rather than wrappers for MPI library functions. In fact, the individual mpi programs
in the package do not even use the MPI libraries. We only depend on the job
launcher from an MPI library, i.e. `mpirun`.


## Examples

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

