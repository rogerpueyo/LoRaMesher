# LoRaMesher
This library aims to implement a user firendly way to create a mesh network between multiple ESP32 LoRa Nodes. This library is currently under construction.

## Dependencies
You can check `library.json` for more details. Basically we use a modded version of [Radiolib](https://github.com/jgromes/RadioLib) that supports class methods as callbacks and [FreeRTOS](https://freertos.org/index.html) for scheduling maintenance tasks

## Development
### Code Quality
We are using [Clang Format](https://clang.llvm.org/docs/ClangFormat.html) to make the code look the same. In addition, we are using [Clang Format Hooks](https://github.com/barisione/clang-format-hooks) to ease the process of installing said hooks and have a nice command line interface to interact with the formater. The first time you clone this repository you need to run the following command on the root directory of the repository:
```bash
./git-pre-commit-format install
```
