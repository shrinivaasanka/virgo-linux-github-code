#
#Makefile for VIRGO cloudexec driver and cloudexec kernel service
#

ccflags-y := -I/home/kashrinivaasan/linux-3.7.8/include -DDEBUG

virgocloudexec_mempool_driver-y := virgo_cloudexec_mempool.o
virgo_cloud_mempool_kernelspace_driver-y := virgo_cloud_mempool_kernelspace.o

#obj-m               += virgo_cloudexec.o virgocloudexecsvc.o
obj-m               += virgo_cloudexec_mempool.o virgo_cloud_mempool_kernelspace.o
#virgocloudexec_driver-objs := virgo_cloudexec.c
#obj-m               += virgo_cloudexec.o
