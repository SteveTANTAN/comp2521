#!/bin/sh

if [ ! -d "tests" ]
then
	echo "You must run this script from your 'q1' directory"
	exit 1
fi

if [ ! -x "stu" ]
then
	echo "You don't seem to have a program to test"
	echo "Did you run make? Were there any errors?"
	exit 1
fi

for t in 01 02 03 04 05 06
do
	tt="tests/$t"
	sh $tt.sh 2>&1 | head -n100 > $tt.observed
	diff -wi $tt.expected $tt.observed > $tt.diffs

	echo ""
	echo "===== Test $t ====="
	if [ ! -s "$tt.diffs" ]
	then
		echo PASSED
	else
		echo FAILED
		echo ""
		echo "===== FIRST TEN lines of your output ====="
		head -n10 $tt.observed
		echo ""
		echo "===== FIRST TEN lines of expected output ====="
		head -n10 $tt.expected
		echo ""
		if [ `cat "$tt.observed" | wc -l` -gt 10 ]
		then
			echo "Output is longer than 10 lines."
			echo "Differences may occur after what is shown above."
		fi
		echo "See the file $tt.diffs for diff output"
	fi
done
