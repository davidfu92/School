#!/bin/bash

EXEFILE ='./p05'

#Check arguments

if [ $# -ne 1 ]
then 
	    echo "This script needs your submission tar file as an argument"
		    exit
		fi

		TEMPDIR=${1%.tar.gz}

		# Untar the file

		tar xzf $1
		cd ${TEMPDIR}

# Make

if [ -f configure ]
then
	    configure
	fi
	make

	if [ -f ${EXEFILE} ]
	then
		    echo "PASS build"
		else
			    echo "FAIL build -- executable not found note that executable should be called p05"
				    exit
				fi

# Test 1: Counting

echo "ooo" > bar
result=$( ${EXEFILE} bar oo )
if [ "$result" = "2" ]
then
	    echo "PASS Test 1"
	else
		    echo "FAIL Test 1"
		fi

#Test 2: Multiple arguments

echo "abcad" >  bar
${EXEFILE} bar a b > results
result1=$( head -n1 results )
result2=$( tail -n1 results )
if [ "$result1" = "2" ] && [ "$result2" = "1" ]
then
	    echo "PASS Test 2"
	else
		    echo "FAIL Test 2"
		fi

#Test 3: Error handling

${EXEFILE} barrrr a 2> errors
result=$( cat errors )
if [ "$result" = "${EXEFILE}: No such file or directory" ]
then
	    echo "PASS Test 3"
	else
		    echo "FAIL Test 3"
		fi


