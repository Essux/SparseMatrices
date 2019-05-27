DEPS = %.h
OBJ = CSR.o CSC.o COO.o DenseMatrix.o SparseMatrix.o Generator.o

main: $(OBJ) main.cpp
	g++ -o $@ $^

%.o: %.c $(DEPS)
	g++ -c -o $@ $(DEPS)

clean:
	rm *.o
	rm main
