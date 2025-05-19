# 🍃 life-tools

![example workflow](https://github.com/ArnasVaic/life-tools/actions/workflows/ci.yaml/badge.svg)

## Development setup

Using WSL is recommended.


Required tools:
```shell
sudo apt-get update && sudo apt-get install -y cmake ninja-build clang
```

To build cmake files run `./build.sh` script with a single argument for the type of configuration to build. Possible configurations:

- `debug` - builds debug configuration
- `release` - builds release configuration
- `test` - builds tests

Generated files will be placed in `build/<configuration>/`. Run `ninja -v` in this directory to compile the project.
