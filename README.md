# CSnake - Snake game in C

Simple snake game written in C. It uses ncurses to get input from user in real time with no need to press ENTER and to draw the map. The code is well commented so if you are curious how it works under the mask open files in `src/` and read the code.

# Downloading, compiling and playing

```
git clone https://github.com/zerfithel/csnake
cd csnake/src
gcc *.c -I include -l ncurses -o csnake
./csnake
```

You need to install `git`, `gcc` and `ncurses-devel` in order to clone the repository and compile it.
