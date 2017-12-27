### DEPENDENCY

- ncurses **(5.0.0 or higher)** [download here](http://ftp.gnu.org/gnu/ncurses)
- cmake **(3.8.0 or higher)** [download here](https://cmake.org/download/)

### BUILD & RUN

```sh
sh build.sh
cd bin
chmod +x server
chmod +x client
./server &
./client
```

### TODO-LIST

- [x] ~~main loop~~
- [x] ~~adjust project structure~~
- [x] ~~msg structure~~
- [x] ~~client command parser~~
- [x] ~~client command interceptor~~
- [x] ~~async sender~~
- [x] ~~client user interface~~
- [x] ~~recv loop (or listener)~~
- [ ] clinet initialization
- [ ] server initialization
- [ ] server msg handle
- [ ] integration testing
