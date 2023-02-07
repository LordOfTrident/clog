<h1 align="center">clog</h1>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=26d374"/>
	</a>
	<a href="https://github.com/LordOfTrident/clog/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/clog?color=4f79e4"/>
	</a>
	<a href="https://github.com/LordOfTrident/clog/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/clog?color=4f79e4"/>
	</a>
	<img width="80%" src="res/thumbnail.png"/>
	<br><br><br>
</p>

A simple single-header [STB-style](https://github.com/nothings/stb) C library for logging, inspired by [log.c](https://github.com/rxi/log.c).

## Table of contents
* [Simple example](#simple-example)
* [Quickstart](#quickstart)
* [Bugs](#bugs)

## Simple example
```c
#define CLOG_IMPLEMENTATION
#include "clog.h"

int main(void) {
	LOG_INFO("Hello, world!");
	LOG_WARN("I am a warning");
	LOG_ERROR("Something bad just happened!");
	LOG_FATAL("Something very bad happened, exiting...");

	return 0;
}
```
Output

<img width="85%" src="res/img.png"/>

## Quickstart
Just copy [`clog.h`](./clog.h) into your project and include it, or submodule this repository and
include the header. [See the example](./examples/log.c) to see how to use the library.

To compile and run the example, run
```sh
$ cc ./examples/log.c -o log
$ ./log
```

## Bugs
If you find any bugs, please create an issue and report them.
