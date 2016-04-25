obj-m += pinball2000.o
pinball2000-objs := parport.o  main.o  game.o attract.o diagnostic.o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)
EXTRA_CFLAGS	:= -I/usr/realtime/include -I/usr/include

default:
	$(MAKE) -Wextra   -C $(KDIR) SUBDIRS=$(PWD) modules
