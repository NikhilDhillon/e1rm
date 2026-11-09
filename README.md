# e1rm

A small C++20 command-line tool that estimates a one-rep max (1RM) with the
Epley formula:

```
e1rm = weight × (1 + reps / 30)
```

It comes from the scoring engine of GROWTH, my strength-tracking app, and is
packaged as a strictly confined snap.

```console
$ e1rm 100 5
Estimated 1RM: 116.7
```

- Wrong number of arguments prints `Usage: e1rm <weight> <reps>` to stderr and exits 1.
- Non-numeric, zero or negative input prints
  `Weight and reps must be positive numbers.` to stderr and exits 1.

No external dependencies, only the standard library.

## Build the snap

Snaps are built on Linux. On macOS, use an Ubuntu VM with
[Multipass](https://multipass.run):

```bash
multipass launch 24.04 --name snapdev --cpus 2 --memory 4G --disk 20G
multipass mount ~/cpp-lab snapdev:/home/ubuntu/cpp-lab
multipass exec snapdev -- sudo snap install snapcraft --classic
multipass exec snapdev -- bash -c 'sudo apt-get update && sudo apt-get install -y cmake g++'
multipass exec snapdev --working-directory /home/ubuntu/cpp-lab/e1rm -- snapcraft pack --destructive-mode
```

`--destructive-mode` builds directly on the host instead of in an LXD or
Multipass container. That's fine in a disposable VM, but don't use it on your
own machine. Because it builds on the host, snapcraft needs the cmake plugin's
build packages (`cmake`, a C++ compiler) installed there. Installing them up
front with apt lets you build as a normal user, without running snapcraft as
root.

The result is `e1rm_0.1_<arch>.snap`, for example `e1rm_0.1_arm64.snap` when
built in a VM on an Apple Silicon Mac.

On an Ubuntu machine, `snapcraft pack` (or plain `snapcraft`) builds inside a
managed LXD container instead.

## Install and run

```bash
sudo snap install ./e1rm_0.1_*.snap --dangerous
e1rm 100 5
snap list e1rm
```

`--dangerous` is required because a locally built snap isn't signed by the
Snap Store. The snap still runs under strict confinement.

## Build without snapcraft

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/e1rm 100 5
```
