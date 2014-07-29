#
#Makefile for VIRGO mempool cloudexec driver and mempool kernelspace driver for intermodule invocation in kernelspace 
#

#ccflags-y := -I/home/kashrinivaasan/linux-3.7.8/lib -I/home/kashrinivaasan/linux-3.7.8 -I/home/kashrinivaasan/linux-3.7.8/include -DDEBUG
ccflags-y := -w -I/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-3.15.5/lib -I/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-3.15.5 -I/media/shrinivaasanka/0fc4d8a2-1c74-42b8-8099-9ef78d8c8ea2/home/kashrinivaasan/linux-3.15.5/include -DDEBUG

virgocloudexec_mempool_driver-y := virgo_cloudexec_mempool.o
virgo_cloud_mempool_kernelspace_driver-y := virgo_cloud_mempool_kernelspace.o

#obj-m               += virgo_cloudexec.o virgocloudexecsvc.o
obj-m               += virgo_cloudexec_mempool.o virgo_cloud_mempool_kernelspace.o
#virgocloudexec_driver-objs := virgo_cloudexec.c
#obj-m               += virgo_cloudexec.o
