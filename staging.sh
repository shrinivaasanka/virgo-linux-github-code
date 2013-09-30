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
#Ph: 9003082186, 9791165980
#Open Source Products Profile(Krishna iResearch): http://sourceforge.net/users/ka_shrinivaasan
#Personal website(research): https://sites.google.com/site/kuja27/
#emails: ka.shrinivaasan@gmail.com, shrinivas.kannan@gmail.com, kashrinivaasan@live.com
#--------------------------------------------------------------------------------------------------

#*****************************************************************************************/

cp /home/kashrinivaasan/linux-3.7.8/arch/arm/tools/mach-types /home/kashrinivaasan/KrishnaiResearch_OpenSource/virgo-linux-code-0/linux-kernel-extensions/arch/arm/tools

cp /home/kashrinivaasan/linux-3.7.8/arch/x86/syscalls/Makefile /home/kashrinivaasan/KrishnaiResearch_OpenSource/virgo-linux-code-0/linux-kernel-extensions/arch/x86/syscalls/
cp /home/kashrinivaasan/linux-3.7.8/arch/x86/syscalls/syscall_32.tbl /home/kashrinivaasan/KrishnaiResearch_OpenSource/virgo-linux-code-0/linux-kernel-extensions/arch/x86/syscalls/
cp /home/kashrinivaasan/linux-3.7.8/arch/x86/syscalls/syscall_64.tbl /home/kashrinivaasan/KrishnaiResearch_OpenSource/virgo-linux-code-0/linux-kernel-extensions/arch/x86/syscalls/


cp /home/kashrinivaasan/linux-3.7.8/Makefile /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/


cp -r /home/kashrinivaasan/linux-3.7.8/virgo_clone/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/virgo_clone/
cp -r /home/kashrinivaasan/linux-3.7.8/virgo_clone/test/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/virgo_clone/test/

cp -r /home/kashrinivaasan/linux-3.7.8/virgo_malloc/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/virgo_malloc/
cp -r /home/kashrinivaasan/linux-3.7.8/virgo_malloc/test/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/virgo_malloc/test/

cp -r /home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/drivers/virgo/cpupooling/virgocloudexec/
cp -r /home/kashrinivaasan/linux-3.7.8/drivers/virgo/cpupooling/virgocloudexec/test_logs/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/drivers/virgo/cpupooling/virgocloudexec/test_logs/

cp -r /home/kashrinivaasan/linux-3.7.8/drivers/virgo/memorypooling/virgocloudexecmempool/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/drivers/virgo/memorypooling/virgocloudexecmempool/
cp -r /home/kashrinivaasan/linux-3.7.8/drivers/virgo/memorypooling/virgocloudexecmempool/test_logs/* /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/drivers/virgo/memorypooling/virgocloudexecmempool/test_logs/


cp /home/kashrinivaasan/linux-3.7.8/include/linux/syscalls.h /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/include/linux
cp -r /home/kashrinivaasan/linux-3.7.8/include/linux/virgo*h /home/kashrinivaasan/KrishnaiResearch_OpenSource//virgo-linux-code-0/linux-kernel-extensions/include/linux
