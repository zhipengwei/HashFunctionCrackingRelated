#!/bin/bash
#cat in_one_category | { while read arg; grep "1 address 17e6c000" -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq > in_one_category1
#cat in_one_category | ( while read arg; do grep $arg -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq; done ) >> in_one_category1
#rm -f in_one_category
#mv in_one_category1 in_one_category
#cat in_one_category
#cat in_one_category | ( while read arg; do cat tmp92.trace.analyzed | grep $arg -A 1 | grep "r_w 0" | awk '{ print $6 }' | sort | uniq; done )

#cat $1 | sed '$!N;s/\n//g' | sort | uniq > 8k_address
cat $1 | tr ' ' '\n' | sort | uniq > 8k_address
rm -f unclassified
cp 8k_address unclassified
for i in `seq 1 6`
do
	cat unclassified | head -n 1 > in_one_category
	number_old=0
	number_new=1
	rm -f in_one_category_tmp	
	while [ $number_old -ne $number_new ]
    do
        number_old=`cat in_one_category | wc -l`
        cat in_one_category | ( while read arg; do cat $1 | grep $arg; done ) >> in_one_category_tmp
		cat in_one_category_tmp | tr ' ' '\n' >> in_one_category
        cat in_one_category | sort | uniq >> in_one_category_sorted
		rm -f in_one_category
		mv in_one_category_sorted in_one_category

        number_new=`cat in_one_category | wc -l`
        echo number_old $number_old number_new $number_new
	done

	mv in_one_category $1.classification$i
	comm unclassified $1.classification$i -2 -3 > unclassified_tmp
	rm -f unclassified
	mv unclassified_tmp unclassified
done

paste $1.classification1 $1.classification2 $1.classification3 $1.classification4 $1.classification5 $1.classification6 > $1.classifications
