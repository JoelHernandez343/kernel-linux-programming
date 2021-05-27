obj-m += gpio_id.o

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/armlinux M=$(PWD) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/armlinux M=$(PWD) clean