# WORDLE SIMULATION

## File Structure
```
/include
    - game.h
    - word_utils.h
/src
    - game.c
    - word_utils.c
/test
    - test.c
- main.c

```

## Code Flow
### Header Files
#### definations

```cpp
#define MAX_WORD_LENGTH 5
#define MAX_WORDS 2315
#define FILE_LENGTH 13889
```

MAX_WORD_LENGTH - defines the maximum length of the word the user can enter.

#### Structs
```
```

#### Functions
```
```

## Testing
```
![alt text](image.png)
```

```bash
gcc .\test\test.c .\src\game.c .\src\word_utils.c
```

## Play Game
```bash
gcc main.c .\src\game.c .\src\word_utils.c
```

## Troubleshooting
### Issues Faced 
##### Header File multiple includes

##### File Reading and Parsing