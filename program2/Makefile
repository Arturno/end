# Mój plik makefile - wpisz 'make all' aby skompilować cały program
# (właściwie wystarczy wpisać 'make' - all jest domyślny jako pierwszy cel)
CC = g++

a.out: main.o transmitter.o receiver.o TransmissionArrangement.o adaptation.o PID.o sendingPackets.o ControlTX.o receiving.o Check.o savetofile.o ControlRX.o position.o serial.o
	$(CC) main.o transmitter.o receiver.o TransmissionArrangement.o adaptation.o PID.o sendingPackets.o ControlTX.o receiving.o Check.o savetofile.o ControlRX.o position.o serial.o -pthread

main.o: main.cpp  TX/headers/transmitter.hpp RX/headers/receiver.hpp 
	$(CC) -c -Wall -pedantic main.cpp 

TransmissionArrangement.o: TransmissionArrangement.cpp TransmissionArrangement.hpp
	$(CC) -c -Wall -pedantic TransmissionArrangement.cpp
	
transmitter.o: TX/src/transmitter.cpp TX/headers/transmitter.hpp TransmissionArrangement.hpp TX/headers/adaptation.hpp TX/headers/sendingPackets.hpp ControlTX.o
	$(CC) -c -Wall -pedantic TX/src/transmitter.cpp 

adaptation.o: TX/src/adaptation.cpp TX/headers/adaptation.hpp TX/headers/PID.hpp
	$(CC) -c -Wall -pedantic TX/src/adaptation.cpp

PID.o: TX/src/PID.cpp TX/headers/PID.hpp
	$(CC) -c -Wall -pedantic TX/src/PID.cpp

sendingPackets.o: TX/src/sendingPackets.cpp TX/headers/sendingPackets.hpp
	$(CC) -c -Wall -pedantic TX/src/sendingPackets.cpp

ControlTX.o: TX/src/ControlTX.cpp TX/headers/ControlTX.hpp
	$(CC) -c -Wall -pedantic TX/src/ControlTX.cpp




receiver.o: RX/src/receiver.cpp RX/headers/receiver.hpp TransmissionArrangement.hpp RX/headers/receiving.hpp
	$(CC) -c -Wall -pedantic RX/src/receiver.cpp

receiving.o: RX/src/receiving.cpp RX/headers/receiving.hpp TransmissionArrangement.hpp RX/headers/Check.hpp RX/headers/savetofile.hpp 
	$(CC) -c -Wall -pedantic RX/src/receiving.cpp

Check.o: RX/src/Check.cpp RX/headers/Check.hpp RX/headers/savetofile.hpp TransmissionArrangement.hpp
	$(CC) -c -Wall -pedantic RX/src/Check.cpp

savetofile.o: RX/src/savetofile.cpp RX/headers/savetofile.hpp TransmissionArrangement.hpp RX/headers/position.hpp
	$(CC) -c -Wall -pedantic RX/src/savetofile.cpp

ControlRX.o: RX/src/ControlRX.cpp RX/headers/ControlRX.hpp 
	$(CC) -c -Wall -pedantic RX/src/ControlRX.cpp
position.o: RX/src/position.cpp RX/headers/position.hpp RX/headers/serial.hpp 
	$(CC) -c -Wall -pedantic RX/src/position.cpp
serial.o: RX/src/serial.cpp RX/headers/serial.hpp 
	$(CC) -c -Wall -pedantic RX/src/serial.cpp

clean:
	rm -rf *.o add

