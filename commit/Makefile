TARGET = simulator
SOURCES = a.cpp a.h b.cpp b.h

$(TARGET): $(SOURCES)
	g++ -o $(TARGET) -O2 -Wall $(SOURCES)

test: $(TARGET)
	./$(TARGET) p1e1.txt 5 > out-p1e1.txt && diff p1e1-output.txt out-p1e1.txt
	./$(TARGET) p1e2.txt 10 > out-p1e2.txt
	./$(TARGET) p1e3.txt 20 > out-p1e3.txt
	./$(TARGET) p1e4.txt 70 > out-p1e4.txt
