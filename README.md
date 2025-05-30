# 🍃 life-tools

![example workflow](https://github.com/ArnasVaic/life-tools/actions/workflows/ci.yaml/badge.svg)

## Development setup

Using WSL is recommended.


Required tools:
```shell
sudo apt-get update && sudo apt-get install -y cmake ninja-build clang-19
```

To build cmake files run `./build.sh` script with a single argument for the type of configuration to build. Possible configurations:

- `debug` - builds debug configuration
- `release` - builds release configuration
- `test` - builds tests

Generated files will be placed in `build/<configuration>/`. Run `ninja -v` in this directory to compile the project.

Run `ctest --verbose --test-dir build/test` from the project root directory after compiling the test configuration to run the tests.

## Related work

- Conway's game Life perturbed [![arXiv](https://img.shields.io/badge/arXiv-2503.19869-<COLOR>.svg)](https://arxiv.org/abs/2503.19869)
