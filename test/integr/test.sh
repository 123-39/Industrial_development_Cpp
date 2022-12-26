#! /bin/bash
# Исходный массив: 1 3 7 2 1
path="./build/exe/main"
output=$($path 1 "test/unit/body.xml")
if [[ $output == "Phone: 333333333" ]]; then
	echo "OK"
else
	echo "FAILED"
fi