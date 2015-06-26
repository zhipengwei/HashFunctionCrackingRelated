echo $1
./trace_analyze $1 1 1 > $1.analyzed
echo "trace analyze has finished!"
./tuple_statistic.sh $1.analyzed
echo "the tuple has been counted"
./classify $1.analyzed.address_tuple > $1.classifications
echo "The process of classification has finished!"
