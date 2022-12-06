To build:

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

There's no real commandline tool yet (TODO!) but you can test with CURL.

```
# curl --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23 
<html><head></head><a href="doPower">Power button control</a></br><a href="doReset">Reset button control</a></br><a href="getTargetStatus">Get target power LED state</a></br></html>
# curl --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23/getTargetStatus 
OFF
root@nuc:/dockerfiles/ingit/hw/sherline# curl -X POST --cert access.crt --key access.key --cacert ca.crt https://192.168.90.23/doPower?thingToDo=short
```

