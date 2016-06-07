timeout	30s testdominion 42  >> temp.out
tailoutput=`tail -n 1 temp.out`
if [ "$tailoutput" == "Segmentation fault (core dumped)" ]; then
	echo "Test Segfaulted"
else
	echo "Test succeeded"
fi


