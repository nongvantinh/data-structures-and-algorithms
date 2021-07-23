# DSAA
  DSAA stands for data structures and algorithms.

  This project is meant to use C++ programming language to implement various data structure and algorithms. It's fully implemented in C++17 and intended to port to C++20.
## Getting project
**development** branch is unstable branch.

**master** branch store the latest update that can be used to create a realease branch.

  Clone the project by using git command.
  
  `git clone https://github.com/nongvantinh/dsaa -b master`
## Prerequisite
  You need the following prerequisites installed on your platform:

Compiler needed to build this library is:
  - clang/clang++ version 12.0.0
  - or gcc/g++ version 9.3.0.
  
  - scons build system version >= 4.1.

  **You can install those via scoop/chocolatey on windows machine.**
  
## Building and testing library.
  When you have the prerequisites installed you can easily build by command:
  
  `scons -j16`
  
**Cross-compile _currently_ doesn't support yet.**

  The command above will automatically detect host platform and build library for you.
  other command option can be found by using command:
  
  `scons -h`
  
  To test it run `./bin/host_platform/dsaa.host_latform.build.bits.extension  --reporter compact --success`
  
  e.g on Windows machine with 64 bits: `.\bin\windows\dsaa.windows.debug.64.exe  --reporter compact --success`
  
## Build library
  
  You need to fulfil the prerequisite first.  
  
  `scons target=value build=value2 -j16`

   Where: **value** can be **static_library** or **shared_library**

   and: **value2** can be **d** or **debug** or **r** or **release**
  
  Library after build will be placed in **bin/host_latform/library_name.host_platform.build.bit.extension**
## Third-party
    This library use Catch2 testing framework for testing project.
## Admit
    This library written by Nông Văn Tình. I spent time and effort to write this.
