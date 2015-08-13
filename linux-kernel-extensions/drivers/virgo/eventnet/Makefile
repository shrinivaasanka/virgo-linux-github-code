#
#Makefile for VIRGO eventnet cloudexec driver and eventnet kernelspace driver for intermodule invocation in kernelspace 
#

ccflags-y :=  -w -I/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5/lib -I/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5/ -I/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5/include -DDEBUG

virgocloudexec_eventnet_driver-y := virgo_cloudexec_eventnet.o
virgo_cloud_eventnet_kernelspace_driver-y := virgo_cloud_eventnet_kernelspace.o

obj-m               += virgo_cloudexec_eventnet.o virgo_cloud_eventnet_kernelspace.o
