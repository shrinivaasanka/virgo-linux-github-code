#!/bin/bash
#/***************************************************************************************
#VIRGO - a linux kernel fork-off with machine learning and cloud features 
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#------------------------------------------------------------------------------------------
#Copyleft (Copyright+):
#Srinivasan Kannan (alias) Ka.Shrinivaasan (alias) Shrinivas Kannan
#Ph: 9791499106, 9003082186
#Krishna iResearch Open Source Products Profiles:
#http://sourceforge.net/users/ka_shrinivaasan,
#https://github.com/shrinivaasanka,
#https://www.openhub.net/accounts/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com,
#kashrinivaasan@live.com
#-------------------------------------------------------------------------------------------
#*****************************************************************************************/

#VIRGO BUILD SCRIPT
rm -rf /media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build 
mkdir -p /media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build 
make -j 2 O=/media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build clean 
make mrproper
make -j 2 O=/media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build menuconfig 
make -j 2 O=/media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build
make -j 2 O=/media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build modules_install
make -j 2 O=/media/ka_shrinivaasan/cbddc062-a016-4828-8780-21bc64cef1e8/linux-4.10.3-build install
make headers_install
update-initramfs -uvk 4.10.3
