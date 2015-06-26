# HashFunctionCrackingRelated
My graduation ceremony is on the way. Actually it is tomorrow. Although it looks messy, this is my first GitHub reponsitory that contains relatively more code than the repositories I created before. Wish you a good day and enjoy this messy repository.

This repository contains the related file to crack the hash function and the toolkit to analyze the collected trace.

When using this package, you can follow the procedures:
1. Before booting the operating system, you reserve a segment of physical memory by specifying parameter. Specially, it is "mem=MEMORY_SIZE", this is a classic parameter. Force usage of a specific amount of memory to be used when the kernel is not able to see the whole system memory or for test
2. Check the /var/log/messages, search e820, you will find BIOS-provided physical RAM map and on CentOS;
3. In ioremap.c, mem_start is the starting position of the physical memory that can be used, and mem_size is the size of the segment of memory;
4. Enter ioremap_cache, execute make and remap_load, /dev/ioremap will appear;
5. In your program, open /dev/ioremap, and you will be able to access the physical memory you reserved.

When it comes to analyzing the trace, I wrote some programs.

In the folder Analyze, you will grasp the workflow of this toolkit by looking at statistic_classify_all.sh, the functions of these programs are described as follows:
1.trace_analyze.c, decoded the physical address and time stamp from the trace collected using HMTT; I highly recommend you read the technical report about Dual-HMTT to understand the meanings of different fields of the trace. The structure of the program is fairly simple, which can be summarized as  read from file, decode and print.
2.tuple.cpp fileters out the trace that can be used. As stated in the master thesis and the technical report, only the traces that meet some requirements can they be used as the input of the classifying function. And the criteria can be summarized as "no OS interference, the read operation is strictly preceded by and followed by write operations";
3.After these traces that meets the requirements are picked out, the two physical addresses with an evicting relaitionship exists between each other are arrayed to in the form of tuples. A tuple consists of two addresses and evicting realtionship exists between the two addresses.
4.Now the situation is clear, if we represent each physical address as a node, evicting relationship as an edge, the classifying problem is converted into connnected graph problem in graph theory. And you can find the solution in classify.cpp.
