# GPIO MMAP w/ functions
This is a refactor of gpio map lesson

## Connection to remote ssh rasbp

Copy the file to remote server:
```bash
scp main.c <user>@<ip>:~/
```

Connect to ssh:
```bash
ssh <user>@<ip>
```

Compile and execute:
```bash
gcc main.c -o gpio_mmap
sudo ./gpio_mmap
```
