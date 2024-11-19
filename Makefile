ifneq ($(KERNELRELEASE),)
obj-m += hello1.o hello2.o
ccflags-y := -I$(PWD)/inc  #Specify the path to the folder
else
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$PWD
clean:
	$(MAKE) -C $(KDIR) M=$PWD clean
endif

