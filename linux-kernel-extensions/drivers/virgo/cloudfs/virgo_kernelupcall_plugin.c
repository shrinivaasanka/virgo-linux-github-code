/***************************************************************************************
VIRGO - a linux module extension with CPU and Memory pooling with cloud capabilities

Copyright (C) 2009-2013  Ka.Shrinivaasan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

mail to: ka.shrinivaasan@gmail.com
*****************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
       void *handle;
       void* (*cloud_function)(void*);
       char *error;
       pthread_t tid;
       void* x;

       int s=0;

       handle = dlopen("/home/kashrinivaasan/linux-3.7.8/drivers/virgo/cloudfs/libvirgo_fs.so", RTLD_LAZY);
       if (!handle) {
             fprintf(stderr, "%s\n", dlerror());
             exit(EXIT_FAILURE);
       }

       dlerror();    /* Clear any existing error */

       printf("dlsym lookup for cloud fs function: %s\n", argv[1]);
       char* symbol_args=strdup(argv[1]);
       char* symbol=strsep(&symbol_args," ");
       printf("virgo_kernel_upcall_plugin: symbol=%s, symbol_args=%s\n",symbol,symbol_args);
       *(void **) (&cloud_function) = dlsym(handle, symbol);
       /* *(void **) (&cloud_function) = dlsym(handle, "_Z16virgo_cloud_testPv");*/

       if ((error = dlerror()) != NULL)  {
               fprintf(stderr, "%s\n", error);
               exit(EXIT_FAILURE);
       }
       printf("virgo_kernel_upcall_plugin: spawning userspace thread for virgo cloud fs function pointer: %x\n",cloud_function);
       s=pthread_create(&tid, NULL, cloud_function, symbol_args); 
       pthread_join(tid, &x);
       fflush(stdout);
       dlclose(handle);

       exit(EXIT_SUCCESS);
}
