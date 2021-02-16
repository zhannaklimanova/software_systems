#!/bin/bash
check_for_source()
{
    if [[ ! -f "$1" ]]
    then
        echo "Source file '$1' not found. Please upload the mini5tester.sh script in the same folder as the report.c file."
        exit 1;
    fi
}

print_and_run()
{
    echo "\$ $1 $2 $3 $4"
    bash -c "$1 $2 $3 $4"
    echo -e "exit code: $?"
}

getNames()
{
	remove='2,3,4,5,6'
	cut -d, -f$remove --complement data.csv | sort -u  

}
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  report.c tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo
echo "[[[[ test case 0 (Point 3): compiling report.c ]]]]"
echo "********************************************************************************"
print_and_run "gcc -o report report.c"
echo "********************************************************************************"
echo
echo "[[[[ test case 1 (Point 7): EXPECTED TO FAIL - missing parameter ]]]]"
echo "********************************************************************************"
print_and_run "./report a.txt" "\"Missy\""
echo "********************************************************************************"
echo
echo "[[[[ test case 2 (Point 8): EXPECTED TO FAIL - unreadable data file ]]]]"
echo "********************************************************************************"
print_and_run "./report" "nosuchdata.csv" "\"Jane Doe"\" "rpt.txt"
echo "********************************************************************************"
echo
echo "[[[[ test case 2.1: EXPECTED TO PASS - able to read data file ]]]]"
echo "********************************************************************************"
print_and_run "./report" "data.csv" "\"Jane Doe\"" "rpt.txt"
echo "********************************************************************************"
echo "[[[[ test case 9: EXPECTED TO FAIL - unable to locate person ]]]]"
echo "********************************************************************************"
print_and_run "./report" "data.csv" "\"Jane Doe\"" "rpt.txt"
echo
echo "[[[[ test case 11: EXPECTED TO PASS - no collaborators found ]]]]"
echo "********************************************************************************"
print_and_run "./report" "data.csv" "\"Markus Bender\"" "rpt.txt"
cat rpt.txt
echo
echo "[[[[ test case 13: EXPECTED TO PASS - collaborators found Huma Foster and Abdullah Allen ]]]]"
echo "********************************************************************************"
print_and_run "./report" "data.csv" "\"Adaline Murphy\"" "rpt.txt"
cat rpt.txt
echo
