#!/bin/bash
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build clean 
#make mrproper
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build oldconfig
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build prepare
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build outputmakefile
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build archprepare
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=scripts
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules_install
#make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build install
#make headers_install

rm -rf /home/kashrinivaasan/linux-3.7.8-build-2/*
cp /home/kashrinivaasan/linux-3.7.8-build/.config /home/kashrinivaasan/linux-3.7.8-build-2/
cp /home/kashrinivaasan/linux-3.7.8-build/Module.symvers /home/kashrinivaasan/linux-3.7.8-build-2/
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 clean 
make mrproper
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 oldconfig
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 prepare
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 outputmakefile
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 archprepare
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=scripts
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules_install
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 install
make headers_install
update-initramfs -uvk 3.7.8
