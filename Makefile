nonet: nonet.c
	sudo rm -f "${CURDIR}/$@"
	cc -o$@ --std=c99 $<
	sudo chown root:root "${CURDIR}/$@"
	sudo chmod u+s "${CURDIR}/$@"

test: nonet
	test -z "`./nonet ip -o addr show`"
