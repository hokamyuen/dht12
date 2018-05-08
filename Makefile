#!/bin/bash

obj-m += dht12_drv.o

KDIR := /home/hokamyuen/linux-3.8

PWD ?= $(shell pwd)

driver:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.order *.mod.c *.symvers
