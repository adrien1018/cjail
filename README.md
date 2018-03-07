# cjail
---
## Introduction
cjail is a application jail for competitive programming and online judge

## Build
cjail use CMake as build system. Install CMake first if you don't have it on your computer.
We suggest you do an out-of-source build
```bash
mkdir build
cd build
cmake ..
make
```

## Library call
cjail provide a interface to use the jail directly, without the need to compile the command.
```c
int cjail_exec(struct cjail_para *para, struct cjail_result *result);
```
#### Parameter
**para**: Configures to change the jail behaviors.
**result**: After a successful execution, the results and stats of the process will be filled in it.
#### Return value
Return 0 if successfully execute the specific process, otherwise, the execution is failed.

## Struct
```c
struct cjail_para;
```
- **argv** <sup>char**</sup>: The arguments of the process to be executed.
- **environ** <sup>char**</sup>: The environment variables for the process. Each string should be "[name]=[val]".
- **chroot** <sup>char*</sup>: The path to chroot, and after a successful chroot will automatically chdir to new root. Set to NULL to disable chroot.
- **workingDir** <sup>char*</sup>: The working directory of the process. Note that this path is relative to the new root.
Set to NULL will make the working directory unchanged.
- **uid** <sup>uid_t</sup>: The uid of the process. 
- **gid** <sup>gid_t</sup>: The gid of the process. 
- **redir_input** <sup>char*</sup>: The file path to redirect to the standard input(fd 0)
- **redir_output** <sup>char*</sup>: The file path to redirect to the standard output(fd 1)
- **redir_err** <sup>char*</sup>: The file path to redirect to the standard error(fd 2)
- **fd_input** <sup>int</sup>: The fd number to be duplicated to the standard input(fd 0). Note that this option will override **redir_input**. Set to 0 to disable this configure.
- **fd_output** <sup>int</sup>: The fd number to be duplicated to the standard output(fd 1). Note that this option will override **redir_output**. Set to 0 to disable this configure.
- **fd_err** <sup>int</sup>: The fd number to be duplicated to the standard error(fd 2). Note that this option will override **redir_err**. Set to 0 to disable this configure.
- **prevervefd** <sup>unsigned int</sup>: Set to 1 to keep fds above 3 opening. **Use this carefully!!** Note that the fds used by cjail will close on executing the process.
- **sharenet** <sup>unsigned int</sup>: Set to 1 to share the same network namespace with the calling process. **Use this carefully!!**
- **cpuset** <sup>cpu_set_t*</sup>: Limit the cpus which the process can run on with this set.
- **rlim_as** <sup>long long</sup>: Limit the maximum size(KB) of availble memory of the process. Set to 0 to disable this limit.
- **rlim_core** <sup>long long</sup>: Limit the maximum size(KB) of core dump. Set to 0 to disable coredump generation. Set to negative value to disable this limit.
- **rlim_fsize** <sup>long long</sup>: Limit the maximum file size(KB) of a file that can be created. Set to 0 to disable this limit.
- **rlim_proc** <sup>long long</sup>: Limit the maximum processes can be created. Set to 0 to disable this limit.
- **rlim_stack** <sup>long long</sup>: Limit the maximum size(KB) of the stack of the process. Set to 0 to disable this limit.
- **lim_time** <sup>timeval*</sup>: Limit the running time. If the time is exceeded, all of the processes in the namespace will be killed.
- **cgroup_root** <sup>char*</sup>: Change the cgroup filesystem root path(outside the chroot jail). Default: "/sys/fs/cgroup"
- **cg_rss** <sup>long long</sup>: Limit the maximum size(KB) of memory of the cgroup. Set to 0 to disable this limit.

```c
struct cjail_result;
```
- **stats** <sup>struct taskstats</sup>: The resource stats of the child process.
- **info** <sup>siginfo_t</sup>: The child process's return status.
- **time** <sup>struct timeval</sup>: The total execution time of the container.
