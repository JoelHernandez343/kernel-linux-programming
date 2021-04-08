# Kernel module for practice 01
## Usage

Building:
```bash
make
```

Cleaning:
```bash
make clean
```

Installation
```bash
sudo insmod kpractice01.ko
```

Show information:
```bash
modinfo kpractice01.ko

# Output
version:        1.0.0
description:    Practice with kernel module n threads.
author:         JOEL HARIM HERNÁNDEZ JAVIER
license:        GPL
name:           kpractice01
vermagic:       5.8.0-48-generic SMP mod_unload modversions 
parm:           option:[1: Average, 2: Sorting, 3: Even numbers] (int)
parm:           data:Array to sort. (array of int)
parm:           even_data:Result array for even numbers. (array of int)
parm:           average:Average result. (int)
```

Uninstall
```bash
sudo rmmod kpractice01
```