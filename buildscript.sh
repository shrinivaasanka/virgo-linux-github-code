#!/bin/bash

#/***************************************************************************************
#VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities
#Copyright (C) 2009-2013  Ka.Shrinivaasan
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
#mail to: ka.shrinivaasan@gmail.com
#*****************************************************************************************/

make mrproper
make O=/home/kashrinivaasan/linux-3.7.8-build oldconfig
make O=/home/kashrinivaasan/linux-3.7.8-build prepare
make O=/home/kashrinivaasan/linux-3.7.8-build outputmakefile
make O=/home/kashrinivaasan/linux-3.7.8-build archprepare
make O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=scripts
make O=/home/kashrinivaasan/linux-3.7.8-build modules
make O=/home/kashrinivaasan/linux-3.7.8-build
make O=/home/kashrinivaasan/linux-3.7.8-build modules_install
make O=/home/kashrinivaasan/linux-3.7.8-build install


