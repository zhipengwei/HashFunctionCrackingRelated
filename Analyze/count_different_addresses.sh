./trace_analyze $1 1 1 > $1.analyzed
./tuple_statistic.sh $1.analyzed
cat $1.analyzed.address_tuple | awk '{print $1}' | sort -n | uniq > tmp11
cat $1.analyzed.address_tuple | awk '{print $2}' | sort -n | uniq > tmp12

cat tmp11 | wc -l
cat tmp12 | wc -l

