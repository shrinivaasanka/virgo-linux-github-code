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


#Linux Psuedorandom number generator based load balancer(experimental):
#----------------------------------------------------------------------
#Each virgo_clone() client has a PRG which is queried (/dev/random or /dev/urandom) to get the id of the host to send the next virgo_clone() function to be executed 
#Expected number of requests per node is derived as:
#expected number of requests per node = summation(each_value_for_the_random_variable_for_number_of_requests * probability_for_each_value)
#=expected number of requests per node = (math.pow(N, k+2) - math.pow(N,3) + math.pow(N,2) - 1) / (math.pow(N, k+3) - 2*math.pow(N,k+2) + math.pow(N,k+1))
#where N is number of processors and k is the number of requests

import math

N=3
k=2
i=2

while i < 2000:
	expectedreqpernode = (math.pow(N, k+2) - k*math.pow(N,2) + k*math.pow(N,1) - 1) / (math.pow(N, k+3) - 2*math.pow(N,k+2) + math.pow(N,k+1))
	print "NumOfProcessors = ",N,",NumOfRequests = ",k," ======== expectedreqpernode :", expectedreqpernode
	i=i+1
	k = i
	#N = i
