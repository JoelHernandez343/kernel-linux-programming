# Cross compilation x86 -> ARM

Packages installation:

```shell
sudo apt install git bc libncurses5-dev flex bison openssl libssl-dev dkms make libelf-dev libudev-dev libpci-dev libiberty-dev autoconf
```

Toolchain download:

```shell
git clone --depth=1 https://github.com/raspberrypi/tools ~/armtools
```

PATH update (`.bashsrc`, `.zshrc`, etc):

```shell
echo "\nPATH=\$PATH:~/armtools/arm-bcm2708/arm-linux-gnueabihf/bin" >> ~/.bashsrc
source ~/.bashsrc
```

Compiling:

```shell
arm-linux-gnueabihf-gcc program.c -o program
```

Now the program compiled need to be executed on a arm device
