# SOCKSAVE
Receives data from socket stream and saves it in a file up to a configurable size.

## Configuration 
To configure the server you need to create a file called "config.json" in the main directory and set the values in a way similar to this:

```
{
    "port"      : 1234,
    "timeout"   : 30,
    "max_size"  : 1024,
    "path"      : "output/",
    "prefix"    : "PREFIX"
}
```

## Requirements
- g++ (GCC) 11.1.0
- GNU Make 4.3
- Boost lib - 1.78.0-1

## Build and Run 
To build the software you need to run the command 
```
make
```
and then run with 
```
./main.o
```

## Time Spent on Development
This took me about 8 hours of development through 2 days.

## Difficulties
- I spent more time than I would like to admit learning abouts boost library clocks in order to figure out a nice way to get the timestamp as I needed.
- Switching from a simple server to a async one to handle multiple clients was a bit more challenging than I was expecting.