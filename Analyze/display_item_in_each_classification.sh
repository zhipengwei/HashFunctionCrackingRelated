for i in `seq 0 10` 
do
	echo $i
	for j in `seq 1 6` 
	do
		if [ $j -eq 6 ]
		then
			echo  `cat tuple$i.trace.analyzed.address_tuple.classification$j | wc -l` 
		else
			echo -n `cat tuple$i.trace.analyzed.address_tuple.classification$j | wc -l` ' '
		fi
	done
done
