## In Progress...

To build simply run this command inside the aurora-engine folder

```
  bdep init -C ../aurora-compiler-clang @clang cc config.cxx=clang++
  b config.log-verbosity=5
```

The first one creates the configuration files for clang, if you want to feel free to use gcc instead, just change @clang to @gcc and clang++ to g++

NOTE: You need to install build2 to build this project
