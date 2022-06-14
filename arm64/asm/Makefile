testing: testing.o
	#ld -o testing testing.o -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch x86_64
	ld -o testing testing.o -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64

testing.o: testing.s
	#as -arch x86_64 -o testing.o testing.s
	as -arch arm64 -o testing.o testing.s
