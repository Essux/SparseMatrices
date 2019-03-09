DEPS = %.h
OBJ = COO.o DenseMatrix.o

main: $(OBJ) main.cpp
	g++ -o $@ $^

%.o: %.c $(DEPS)
	g++ -c -o $@ $(DEPS)

clean:
	rm *.o
	rm main