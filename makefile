CC = g++
FLAGS = -std=c++11 -g -o3

all:generate_stream stream_processing

generate_stream: generate_stream.cpp
			$(CC) $(FLAGS) generate_stream.cpp -o generate_stream

stream_processing: stream_processing.cpp
			$(CC) $(FLAGS) stream_processing.cpp -o stream_processing


clean:
	rm -rf *.o
