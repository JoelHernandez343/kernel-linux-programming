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

> `KERNEL` variable will be used in the step [Upgrading RaspberryPi's kernel](#Upgrading-RaspberryPis-kernel)

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

## Makefile compilation

```Makefile
obj-m += arm-program.c

all:
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/armlinux M=$(PWD) modules

clean:
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/armlinux M=$(PWD) clean
```

## Upgrading RaspberryPi's kernel

1. Install the SD in the computer

2. Identify the sd partitions on `/dev`

```shell
lsblk

# output
...
sdb       179:0    0 59.5G  0 disk
├─sdb1    179:1    0  256M  0 part /media/user/boot
└─sdb2    179:2    0 59.3G  0 part /media/user/rootfs
```

Here `sdb1` is `boot` and `sdb2` is `rootfs`.

3. Unmount the partitions

```shell
sudo umount /dev/sdb1
sudo umount /dev/sdb2
```

4. Mount the partitions in the kernel cloned repository

```shell
cd ~/armlinux
mkdir mnt
mkdir mnt/boot
mkdir mnt/rootfs
sudo mount /dev/sdb1 mnt/boot
sudo mount /dev/sdb2 mnt/rootfs
```

5. Install the compiled kernel modules

```shell
sudo env PATH=$PATH make ARCH=arm CROSS_COMPILE=arm-linux-
gnueabihf- INSTALL_MOD_PATH=mnt/rootfs modules_install
```

6. Copy the kernel image generated in the previous steps

> Here we use the `KERNEL` variable

```shell
sudo cp mnt/boot/$KERNEL.img mnt/boot/$KERNEL-backup.img
sudo cp arch/arm/boot/zImage mnt/boot/$KERNEL.img
sudo cp arch/arm/boot/dts/*.dtb mnt/boot/
sudo cp arch/arm/boot/dts/overlays/*.dtb* mnt/boot/overlays/
sudo cp arch/arm/boot/dts/overlays/README mnt/boot/overlays/
sudo umount mnt/boot
sudo umount mnt/rootfs
```

And that's all.
