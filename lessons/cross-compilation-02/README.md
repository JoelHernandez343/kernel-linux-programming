# Kernel module cross compilation x86 -> ARM

Download kernel image of RaspberryPI:

```shell
git clone --depth=1 https://github.com/raspberrypi/linux ~/armlinux
```

## Manual configuration

Change directory:

```shell
cd ~/armlinux
```

Define `KERNEL` variable and set configuration as follows:

1. Pi 1, Pi Zero, Pi Zero W, or Computer module:

```shell
KERNEL=kernel
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcmrpi_defconfig
```

2. Pi 2, Pi 3, Pi 3A+, Pi 3B+, or Computer module 3:

```shell
KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig
```

3. Pi 4

```shell
KERNEL=kernel7l
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2711_defconfig
```

## Kernel compilation

In order to rebuild the RaspberryPI Soc and upgrade it to last version with all drivers, we execute:

```shell
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs
```

This command accepts `-j<n>` flag, with `n` the number of processors of our machine times 1.5. For example:

```shell
lscpu

# Output
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   43 bits physical, 48 bits virtual
CPU(s):                          12
On-line CPU(s) list:             0-11
Thread(s) per core:              2
Core(s) per socket:              6
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       AuthenticAMD
CPU family:                      23
Model:                           113
Model name:                      AMD Ryzen 5 3600 6-Core Processor
...
```

Then `n` will be `18`, thus the command will be:

```shell
make -j18 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs
```
