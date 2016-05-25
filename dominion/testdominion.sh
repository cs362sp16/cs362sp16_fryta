<<<<<<< HEAD
timeout	-s 9 10s testdominion 42 > testdominionOUTPUT.out
=======
timeout	10s testdominion 42  
>>>>>>> 88cbd9e1e41208911f92d4351f2667fa59e29e55
tailoutput=`tail -n 1 temp.out`
if [ "$tailoutput" == "Segmentation fault (core dumped)" ]; then
	echo "Test Segfaulted"
else
	echo "Test succeeded"
fi



