DEPS = %.h
OBJ = COO.o CSC.o DenseMatrix.o SparseMatrix.o

main: $(OBJ) main.cpp
	g++ -o $@ $^

%.o: %.c $(DEPS)
	g++ -c -o $@ $(DEPS)

clean:
	rm *.o
	rm main
