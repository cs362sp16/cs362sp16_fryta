timeout	10s testdominion 42  
tailoutput=`tail -n 1 temp.out`
if [ "$tailoutput" == "Segmentation fault (core dumped)" ]; then
	echo "Test Segfaulted"
else
	echo "Test succeeded"
fi



