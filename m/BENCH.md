## mimalloc-bench howto

```
git clone https://github.com/daanx/mimalloc-bench.git bench && cd bench
```

### linux

```
./build-bench-env.sh all
```

### linux (w/o ninja)

```
./build-bench-env.sh all no-hd no-je no-rp no-sn no-mesh no-bench
```

### darwin (nyi)

```
#./build-bench-env.sh all no-tc no-hd no-rp no-sn no-sm no-mesh no-lean no-redis...
```

### supported mallocs and tests

```
mkdir -p out/bench && cd out/bench
../../bench.sh --help
```

### all mallocs on all benchmarks:

```
../../bench.sh alla allt
```

### mimalloc and tcmalloc on cfrac and larson with 16 threads

```
../../bench.sh --procs=16 mi tc cfrac larson
```

`/:~`