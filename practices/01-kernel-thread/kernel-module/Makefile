obj-m += kpractice01.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod $(patsubst %.o, %.ko, $(obj-m))

uninstall:
	sudo rmmod $(patsubst %.o, %.ko, $(obj-m))