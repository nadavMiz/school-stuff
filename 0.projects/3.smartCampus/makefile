

all:
	make -C common
	make -C communication
	make -C smartHouse
	make -C devices
	
	mkdir -p sharedObjects
	mkdir -p log

	mv devices/nadavElectric.so sharedObjects
	mv devices/nadavSensors.so sharedObjects

	mv smartHouse/smartHouse.out ./ 
	
clean:
	make -C common clean
	make -C communication clean
	make -C smartHouse clean
	make -C devices clean
	rm smartHouse.out
