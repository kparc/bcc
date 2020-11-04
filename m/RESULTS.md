`$ make leak && make stress && make cfrac`

## leak

```
leak ta_malloc (split+compact)

ta_test_init blk 256 heap 62g phys 251g
using 1 thread with a 100% load-per-thread and 40000 iterations (ta_malloc)
0.18user 0.68system 0:00.78elapsed 1712maxresident

leak ta_malloc (no split)

ta_test_init blk 256 heap 62g phys 251g
using 1 thread with a 100% load-per-thread and 40000 iterations (ta_malloc)
0.16user 0.68system 0:00.75elapsed 1600maxresident

leak sys_malloc

using 1 thread with a 100% load-per-thread and 40000 iterations (sys_malloc)
0.17user 0.67system 0:00.76elapsed 3496maxresident

leak aw_malloc

using 1 thread with a 100% load-per-thread and 40000 iterations (aw_malloc)
0.18user 0.65system 0:00.75elapsed 5768maxresident
```

## stress

```
stress sys_realloc

using 1 thread with a 100% load-per-thread and 32 iterations (sys_malloc)
9.19user 14.38system 0:23.66elapsed 1172932maxresident

stress aw_realloc

aw_malloc_init ok
using 1 thread with a 100% load-per-thread and 32 iterations (aw_malloc)
11.51user 0.36system 0:11.95elapsed 1922696maxresident)k
```

## cfrac

```
cfrac ta_malloc (split+compact)

ta_test_init blk 2048 heap 62g phys 251g
175451865205073170563711388363 = 374456281610909315237213 * 468551
0.38user 0.00system 0:00.39elapsed 2440maxresident

cfrac ta_malloc (no split)

ta_test_init blk 2048 heap 62g phys 251g
175451865205073170563711388363 = 374456281610909315237213 * 468551
0.24user 0.00system 0:00.24elapsed 3716maxresident

cfrac sys_malloc

175451865205073170563711388363 = 374456281610909315237213 * 468551
0.10user 0.00system 0:00.10elapsed 2204maxresident

cfrac aw_malloc

aw_malloc_init ok
175451865205073170563711388363 = 374456281610909315237213 * 468551
0.09user 0.00system 0:00.09elapsed 6324maxresident
```

## env

```
$ uname -a
Linux kei 5.7.10-1.el8.elrepo.x86_64 #1 SMP Wed Jul 22 08:30:51 EDT 2020 x86_64 x86_64 x86_64 GNU/Linux

$ free -h
              total        used        free      shared  buff/cache   available
Mem:          251Gi       3.5Gi       230Gi        90Mi        17Gi       246Gi

$ sysctl vm.*
vm.overcommit_memory = 0
vm.swappiness = 10
vm.oom_kill_allocating_task = 0
vm.swappiness = 10

$ cat /proc/cpuinfo
...
processor	: 39
cpu family	: 6
model		: 79
model name	: Intel(R) Xeon(R) CPU E5-2630 v4 @ 2.20GHz
stepping	: 1
microcode	: 0xb000036
cpu MHz		: 2711.071
cache size	: 25600 KB
```

`/:~`
