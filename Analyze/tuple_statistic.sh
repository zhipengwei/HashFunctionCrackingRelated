#!/bin/bash
#cat in_one_set | { while read arg; grep "1 address 17e6c000" -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq > in_one_set1
#cat in_one_set | ( while read arg; do grep $arg -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq; done ) >> in_one_set1
#rm -f in_one_set
#mv in_one_set1 in_one_set
#cat in_one_set
#cat in_one_set | ( while read arg; do cat tmp92.trace.analyzed | grep $arg -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq; done )

#cat complete_matrix_sorted_s | ( while read arg; do cat complete_matrix_s | grep $arg | wc -l; done ) > in_one_set_tmp

./tuple $1 > $1.merge_two_lines
cat $1.merge_two_lines | cut -f 6,14 -d" " > $1.address_tuple
#cat $1.address_tuple | tr ' ' '_' > address_tuple_tmp
#cat address_tuple_tmp | sort | uniq > address_tuple_remove_duplication
#cat address_tuple_remove_duplication | tr ' ' '\n' > address_tuple_split_space
#cat address_tuple_remove_duplication | ( while read arg; do cat address_tuple_tmp | grep $arg | wc -l; done ) > counters
#paste address_tuple_remove_duplication counters > $1.result

rm -f $1.merge_two_lines address_tuple_tmp address_tuple_remove_duplication counters
