#
#Makefile for VIRGO cloudexec driver and cloudexec kernel service
#

#ccflags-y := -I/home/kashrinivaasan/linux-3.7.8/include -DDEBUG
ccflags-y := -w -I/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-4.1.5/include -DDEBUG

virgocloudexec_driver-y := virgo_cloudexec.o
virgo_cloud_test_kernelspace_driver-y := virgo_cloud_test_kernelspace.o

#obj-m               += virgo_cloudexec.o virgocloudexecsvc.o
obj-m               += virgo_cloudexec.o virgo_cloud_test_kernelspace.o
#virgocloudexec_driver-objs := virgo_cloudexec.c
#obj-m               += virgo_cloudexec.o
