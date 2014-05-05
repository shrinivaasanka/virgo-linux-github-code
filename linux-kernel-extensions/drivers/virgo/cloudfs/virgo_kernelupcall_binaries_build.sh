#/***************************************************************************************
#VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities
#
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


#!/bin/bash

g++ -c virgo_cloud_fs.c 
g++ -o virgo_cloud_fs_main virgo_cloud_fs_main.c
g++ -shared -o libvirgo_fs.so virgo_cloud_fs.o
g++ -c virgo_kernelupcall_plugin.c 
g++ -o virgo_kernelupcall_plugin virgo_kernelupcall_plugin.o -ldl -lpthread
