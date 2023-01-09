#!/bin/bash
set -e

rm -rf ca client >/dev/null
mkdir -p ca client

echo "01" > ca/serial
touch ca/index.txt

openssl req -days 3650 -nodes -new -x509 -keyout ca/ca.key -out ca/ca.crt -config openssl-ca.conf -newkey rsa:2048

for box in 192.168.90.20 192.168.90.21 192.168.90.22 192.168.90.23 access ; do
	if [[ $box = 'access' ]]
	then
		echo "[san]\n" > tmp.conf
	else
		echo -e "[san]\nsubjectAltName=IP:$box" > tmp.conf
	fi
	cat tmp.conf
	
	openssl req -sha256 -nodes		\
		-new												\
		-keyout client/$box.key			\
		-out client/$box.csr				\
		-days 3650									\
		-subj "/C=SG/ST=AlizLand/L=Aliz/CN=${box}.management.gamesfairy.co.uk"	\

	openssl x509 -req							\
		-out client/$box.crt				\
		-in client/$box.csr					\
		-CA ca/ca.crt								\
		-CAkey ca/ca.key						\
		-extensions san							\
		-extfile tmp.conf						\
		-days 3650									\
		-CAcreateserial

	openssl pkcs12 -export -nodes -in client/$box.crt -inkey client/$box.key -out client/$box.pfx -passout pass:
done
