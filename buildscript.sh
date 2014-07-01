#!/bin/bash

#/***************************************************************************************
#VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities
#
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#--------------------------------------------------------------------------------------------------
#Copyright (C):
# 
#Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
#Independent Open Source Developer, Researcher and Consultant
#Ph: 9789346927, 9003082186, 9791165980
#Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
#--------------------------------------------------------------------------------------------------

#*****************************************************************************************/

#VIRGO BUILD SCRIPT
rm -rf /home/kashrinivaasan/linux-3.7.8-build-virgofs/
mkdir -p /home/kashrinivaasan/linux-3.7.8-build-virgofs/
cp /home/kashrinivaasan/linux-3.7.8-build-2/.config /home/kashrinivaasan/linux-3.7.8-build-virgofs/
cp /home/kashrinivaasan/linux-3.7.8-build-2/Module.symvers /home/kashrinivaasan/linux-3.7.8-build-virgofs/
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs clean 
make mrproper
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs i386_defconfig
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs oldconfig
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs prepare
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs outputmakefile
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs archprepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/usb clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/usb 
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/usb modules_install
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=scripts
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/virgo/memorypooling/virgocloudexecmempool clean
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/virgo/memorypooling/virgocloudexecmempool
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules_install SUBDIRS=drivers/virgo/mempooling/virgocloudexecmempool
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs modules_install
make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgofs install
make headers_install
update-initramfs -uvk 3.7.8

#rm -rf /home/kashrinivaasan/linux-3.7.8-build-virgomempool/
#mkdir -p /home/kashrinivaasan/linux-3.7.8-build-virgomempool/
#cp /home/kashrinivaasan/linux-3.7.8-build/.config /home/kashrinivaasan/linux-3.7.8-build-virgomempool/
#cp /home/kashrinivaasan/linux-3.7.8-build/Module.symvers /home/kashrinivaasan/linux-3.7.8-build-virgomempool/
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool clean 
#make mrproper
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool oldconfig
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool prepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool outputmakefile
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool archprepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/usb clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/usb 
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/usb modules_install
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=scripts
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/virgo/memorypooling/virgocloudexecmempool clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/virgo/memorypooling/virgocloudexecmempool
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules_install SUBDIRS=drivers/virgo/mempooling/virgocloudexecmempool
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool modules_install
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-virgomempool install
#make headers_install
#update-initramfs -uvk 3.7.8

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

#rm -rf /home/kashrinivaasan/linux-3.7.8-build-2/*
#cp /home/kashrinivaasan/linux-3.7.8-build/.config /home/kashrinivaasan/linux-3.7.8-build-2/
#cp /home/kashrinivaasan/linux-3.7.8-build/Module.symvers /home/kashrinivaasan/linux-3.7.8-build-2/
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 clean 
#make mrproper
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 oldconfig
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 prepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 outputmakefile
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 archprepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=scripts
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 modules_install
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-2 install
#make headers_install
#update-initramfs -uvk 3.7.8

#rm -rf /home/kashrinivaasan/linux-3.7.8-build-3/*
#cp /home/kashrinivaasan/linux-3.7.8-build/.config /home/kashrinivaasan/linux-3.7.8-build-3/
#cp /home/kashrinivaasan/linux-3.7.8-build/Module.symvers /home/kashrinivaasan/linux-3.7.8-build-3/
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 clean 
#make mrproper
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 oldconfig
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 prepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 outputmakefile
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 archprepare
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules SUBDIRS=scripts
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 modules_install
#make -j 20 O=/home/kashrinivaasan/linux-3.7.8-build-3 install
#make headers_install
#update-initramfs -uvk 3.7.8
