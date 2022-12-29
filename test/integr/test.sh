#! /bin/bash

path="./build/exe/main"

output=$($path 1 "test/unit/body.xml")
if [[ $output == "Phone: 333333333" ]]; then
	echo "OK"
else
	echo "FAILED"
fi

output=$($path 1 "test/unit/body_fake.xml")
if [[ $output == "Unable to open file" ]]; then
  echo "OK"
else
  echo "FAILED"
fi