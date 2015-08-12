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
#Ph: 9003082186, 9791499106 
#Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
#--------------------------------------------------------------------------------------------------

#*****************************************************************************************/


#VIRGO BUILD SCRIPT
rm -rf /media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build/
mkdir -p /media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build/
make -j 20 O=/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build clean 
make mrproper
make -j 20 O=/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build menuconfig 
make -j 20 O=/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build
make -j 20 O=/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build modules_install
make -j 20 O=/media/shrinivaasanka/0fc4d8a2-1c74-4268-8099-9ef78d8c8ea22/home/kashrinivaasan/linux-4.1.5-build install
make headers_install
update-initramfs -uvk 4.1.5
