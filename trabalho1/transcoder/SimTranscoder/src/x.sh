#!/bin/bash

verbose=0

exec 3>&1
exec 4>&2

if ((verbose)); then
	echo "verbose=1"
else
	echo "verbose=0"
	exec 1>/dev/null
	exec 2>/dev/null
fi

echo "this should be seen if verbose"
echo "this should always be seen" 1>&3 2>&4
