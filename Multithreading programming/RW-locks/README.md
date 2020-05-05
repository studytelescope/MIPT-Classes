# Task #2

To realize read-write locking using only atomic primitives

## Reader preference 
### An average result of the programm work
```bash
Reader 0 reads 0
Reader 1 reads 0
Reader 6 reads 0
Reader 2 reads 0
Reader 4 reads 0
Reader 10 reads 0
Reader 15 reads 0
Reader 3 reads 0
Reader 9 reads 0
Reader 8 reads 0
Reader 11 reads 0
Reader 18 reads 0
Reader 16 reads 0
Reader 13 reads 0
Reader 12 reads 0
Reader 14 reads 0
Reader 17 reads 0
Writer 5 writes 50
Writer 7 writes 70
Reader 19 reads 70
```

## Writer preference 
### An average result of the programm work
```bash
Writer 0 writes 0
Writer 1 writes 10
Writer 2 writes 20
Writer 4 writes 50
Reader 5 reads 50
Writer 9 writes 140
Writer 8 writes 220
Writer 10 writes 390
Writer 7 writes 290
Writer 11 writes 500
Writer 15 writes 650
Writer 16 writes 810
Reader 14 reads 810
Reader 13 reads 810
Writer 3 writes 840
Writer 18 writes 1020
Writer 17 writes 1190
Writer 19 writes 1380
Reader 6 reads 1380
Reader 12 reads 1380
```