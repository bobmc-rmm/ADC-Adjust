# Makefile  to remember platformio commands
# type "make -s" to list options
# 2022.mar.23

# only the last 'BRD' macro applies
BRD    := esp32doit-devkit-v1	# MCU4
BRD    := esp32dev	# MCU5
BRD    := metro		# MCU1 MetroMini328 (enhanced UNO)
BRD    := nano33ble	# MCU2
BRD    := featheresp32	# MCU3

all:
	echo "make s1 .. (init/update the project)\n"
	echo "make s2 .. (compile the project to fix errors)\n"
	echo "make s3 .. (compile and upload the project)\n"
	echo "make clean .. (delete the object files from build)\n"
	echo "make doxy ..(extract documentation to HTML)

s1:
	pio project init -b ${BRD}

s2:
	pio run -e ${BRD}

s3:
	pio run -e ${BRD} --target upload

doxy:
	doxygen Doxyfile

clean:
	pio run -t clean


# picocom -b 115200 /dev/ttyUSB0 -g log1.txt ...(terminal example)
# endfile

