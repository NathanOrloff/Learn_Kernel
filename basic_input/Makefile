MOD = basic_input
KPATH :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
obj-m = $(MOD).o

all:
	$(MAKE) -C $(KPATH) M=$(PWD) modules

clean:
	$(MAKE) -C $(KPATH) M=$(PWD) clean

rmmod:
	sudo rmmod $(MOD).ko; true

insmod: all
	sudo rmmod $(MOD).ko; true
	sudo insmod $(MOD).ko

log: 
	sudo dmesg | tail
