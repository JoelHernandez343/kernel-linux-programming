# Practice 1 - Kernel Module with arrays
## Description

Develop a kernel module that performs various operations with an `int` array.
The array must contain 8 elements and must be initialized as follows:

```c
int data [MAX] = {5,78,-23,97,12,-5,7,44};
```

The operations to be performed consist of:
- Calculate average of array's elements. Print on log file.
- Sorting array using bubble sort. The result must be stored in the same array without extra memory. Print the resulting array on log file.
- Find the even numbers of array and store them on a different array. Print on log file.

The module's parameters are:

Parameter | Type | Function
-|-|-
option | `int` | Select the operation to perform
data | `int *` | Store the integer numbers
average | `int` | Store the average of array's elements
even_data | `int *` | Store even numbers of `data`

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

Execution
![](./docs/sc01.png)

Further information, see [README.md](./client/README.md)