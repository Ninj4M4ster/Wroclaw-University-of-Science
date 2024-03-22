all:
	go build -buildmode=c-archive custom_lib.go
	gcc -pthread test.c custom_lib.a -o main