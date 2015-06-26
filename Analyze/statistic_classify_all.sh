for i in g_{21..61}.trace
do
	echo $i
	./trace_analyze $i 1 1 > $i.analyzed
	echo "trace analyze has finished!"
	./tuple_statistic.sh $i.analyzed
	echo "the tuple has been counted"
	./classify $i.analyzed.address_tuple > $i.classifications
	echo "The process of classification has finished!"
done
