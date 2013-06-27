#!/bin/bash
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build clean 
make mrproper
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build oldconfig
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build prepare
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build outputmakefile
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build archprepare
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=scripts
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec clean
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules_install SUBDIRS=drivers/virgo/cpupooling/virgocloudexec
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build modules_install
make -j 6 O=/home/kashrinivaasan/linux-3.7.8-build install
make headers_install
