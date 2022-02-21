ARGS=/home/devops/line
EXEC=../build-line3-Desktop-Du00e9faut/line3
all: exec
exec: $(EXEC)
	./$< $(ARGS)
