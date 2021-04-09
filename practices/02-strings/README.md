# Practice 2 - Kernel Module with arrays
![](./docs/sc01.png)

## Description

Develop a kernel module that performs various operations with an `char` array (a string).
The string must be initialized as follows:

```c
char *str = "esta es la optativa de advanced computing systems programming";
```

The operations to be performed consist of:
- Find how many matches between the `letter` paramater and the string. Print in log.
- Calculate the string length. Print in log.

The module's parameters are:

Parameter | Type | Function
-|-|-
option | `int` | Select the operation to perform
str | `char *` | Store the string to work with (ASCII)
letter | `char *` |  A string whith one char, the letter to search in the string.
coincidences | `int` | Store how many matches between `letter` and the `str`
length | `int` | Store the `str` length

Operations must be performed in a kernel thread through the selected `option`. The parameters will be modified and read by an user's space app, **which has to be developed as well**.

## Usage

The practice consists in two parts, the module kernel and the user's space app developed with `Node.js`.

### Kernel module.

Read [README.md](./kernel-module/README.md) of kernel module.

### Application

Install npm packages:
```bash
npm i
```

Execute the following command and enter super user credentials:
```bash
npm start
```

Further information, see [README.md](./client/README.md)