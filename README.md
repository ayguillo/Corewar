# Corewar
## Overview
Our own implementation of the famous 1984's [Corewar](https://en.wikipedia.org/wiki/Core_War) game.

## Assembler
### Overview
Used to compile '.s' pseudo-assembly champions into '.cor' binaries readable by the Virtual Machine.

### Usage
```
./asm [files .s]
```
## Virtual Machine
### Overview
Run the aforementioned binaries and provide options to visualize the execution.

### Usage
```
./corewar [-d | -v | -V | -z] [-dump nbr_cycles] [[-n number] champion1.cor] ... Max 4 players
  -d: Debug mode (output on STDERR, combinable with -V)
  -v: Verbose mode
  -V: Visual mode
  -z: Ncurse mode
```
### Visualizers
#### Go
```./corewar -V [champions.cor] | ./visu ```
  
<img src="./resources/images/corewar_go.gif"/>


#### Ncurses
``` ./corewar -z [champions.cor]```
  
<img src="./resources/images/corewar_ncurse.gif"/>


## Footnotes
### Resources used
TO BE ADDED (eng + fr subject, jyeo operations, cheatsheet, epitech's subject)
