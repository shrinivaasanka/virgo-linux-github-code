#
#Makefile for VIRGO fs cloudexec driver and fs kernelspace driver for intermodule invocation in kernelspace 
#

ccflags-y := -I/home/kashrinivaasan/linux-3.7.8-src1/lib -I/home/kashrinivaasan/linux-3.7.8-src1 -I/home/kashrinivaasan/linux-3.7.8-src1/include -DDEBUG

virgocloudexec_fs_driver-y := virgo_cloudexec_fs.o
virgo_cloud_fs_kernelspace_driver-y := virgo_cloud_fs_kernelspace.o

obj-m               += virgo_cloudexec_fs.o virgo_cloud_fs_kernelspace.o
