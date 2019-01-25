# Diffie-Hellman-KeyExchange
Simple implementation of key exchange protocol Diffie-Hellman in a client/server scenario.

@@ Author: Andrea Canepa

DO NOT USE, FOR ANY REASON, THIS IMPLEMENTATION IN YOUR CRYPTOGRAPHYC APPLICATIONS !!!

Once you have cloned/downloaded this repo, in order to launch the program you have to:
	1) launch the command "make" to compile the source code
		1.1) if you want to compile only one componenent you can launch "make server"
		     or "make client"
     	2) launch the server with the command ./bin/server
	3) launch instances of clients running more than once ./bin/client
	4) (OPTIONAL) launch some tests with the command "make test"

Note that all the path are relatives and proper evaluated, so if You change the structure
of the repo, You have to change also those paths. Moreover I used the PHTREAD library,
which is the one offered by the POSIX standard, since I'm a big fan of the Linux world:
be careful if you want to execute the program under a Windows environment.

Any suggestion/pull request will be well accepted.
