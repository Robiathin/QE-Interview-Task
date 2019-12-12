#Building the coding challenge

The build uses the `check` unit testing framework, and the ninja build system.

The only library required is `json-c`.

To compile the executable:

```bash
./configure.sh
ninja
```

To compile and run the test suite:

```bash
./configure.sh
ninja test_suite
./test_suite
```

The library locations come from `pkg-config` with a failback to sane defaults. It should run on it's own but if the libraries can't be found, `./configure.sh` can have CFLAGS and LDFLAGS set manually to correct the path for your system:

```bash
CFLAGS=-I/usr/local/include ./configure.sh
``
