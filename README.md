<h1 align="center">cargs</h1>
<p align="center">A command line arguments parsing library for C</p>

<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=26d374"/>
	</a>
	<a href="https://github.com/LordOfTrident/cargs/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/cargs?color=4f79e4"/>
	</a>
	<a href="https://github.com/LordOfTrident/cargs/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/cargs?color=4f79e4"/>
	</a>
	<br><br><br>
	<img width="75%" src="res/img.png"/>
</p>

A simple single-header STB-style C library for logging, inspired by [log.c](https://github.com/rxi/log.c).

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

## Quickstart
Just copy [`clog.h`](./clog.h) into your project and include it.
[See the example](./examples/main.c) to see how to use the library.

To compile and run the example, run
```sh
$ cc ./examples/main.c -o main
$ ./main
```

## Bugs
If you find any bugs, please create an issue and report them.
