```shell
bazel build //main:hello-world

bazel build --action_env=CC=E:\mingw64\bin\gcc.exe action_env=CXX=E:\mingw64\bin\g++ //main:hello-world
bazel build --action_env=CC=D:\mingw64\bin\gcc action_env=CXX=D:\mingw64\bin\g++ //main:hello-world

```

