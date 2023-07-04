= About = 

This is a very simple tool to control a PC's power state. It offers functions to 'press' the power button (controlled via a relay), the 'reset' button, and to observe the current power state of the PC.

It connects to the PC's ATX power-supply header, and uses an ESP8266 to expose a web interface via SSL. The web interface uses mutual SSL (ie, the client authenticates with a certificate and the server authenticates with a certificate).

= Building =

Refer to the Jenkinsfile, or:

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg install curl[tool] curl[openssl]
```

You'll need to generate keys first - cd to keys/ and run `generate.sh`.

= Use = 

There's no real commandline tool yet (TODO!) but you can test with cURL.

```
# curl --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23 
<html><head></head><a href="doPower">Power button control</a></br><a href="doReset">Reset button control</a></br><a href="getTargetStatus">Get target power LED state</a></br></html>
# curl --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23/getTargetStatus 
OFF
aliz@nuc:/foo# curl -X POST --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23/doPower?thingToDo=short
```

