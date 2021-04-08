# Kernel module for practice 02
## Usage

Building:
```bash
make
```

Installation
```bash
make install
```

Show information:
```bash
modinfo kpractice02.ko

# Output
version:        1.0.0
description:    Practice with kernel module n threads.
author:         JOEL HARIM HERNÁNDEZ JAVIER
license:        GPL
name:           kpractice02
vermagic:       5.8.0-48-generic SMP mod_unload modversions 
parm:           option:[1: Count coincidences, 2: Calculating length] (int)
parm:           str:Input string. (charp)
parm:           letter:Letter to search. Only fisrt character will be processed. (charp)
parm:           coincidences:Number of coincidences. (int)
parm:           length:String length. (int)
```

Uninstall
```bash
make uninstall
```

Cleaning:
```bash
make clean
```