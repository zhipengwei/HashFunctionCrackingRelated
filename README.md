# HashFunctionCrackingRelated
This repository contains the related file to crack the hash function and the toolkit to analyze the collected trace.

When using this package, you can follow the procedures:
1. Before booting the operating system, you reserve a segment of physical memory by specifying parameter;
2. Check the /var/log/messages, search e820, you will find BIOS-provided physical RAM map and on CentOS;
3. In ioremap.c, mem_start is the starting position of the physical memory that can be used, and mem_size is the size of the segment of memory;
4. Enter ioremap_cache, execute make and remap_load, /dev/ioremap will appear;
5. In your program, open /dev/ioremap, and you will be able to access the physical memory you reserved.
