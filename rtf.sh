 #!/bin/bash
mkdir /dev/rtf
mknod -m 666 /dev/rtai-shm c 10 254
for n in `seq 0 9`
do
	f=/dev/rtf/$n
	mknod -m 666 $f c 150 $n
	f=/dev/rtf$n
	mknod -m 666 $f c 150 $n
done

