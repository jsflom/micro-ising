#Makefile for building esp-idf projects

#The main tools are Docker and esptool 

#Resources:
#	Docker installation (for linux and WSL):
#		https://docs.docker.com/get-started/get-docker/
#
#	Colima installation (prerequisite for docker for MacOS):
#		https://github.com/abiosoft/colima
#		
#	espressif documentation:
#		esp-idf: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html
#		esp-idf docker image: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/tools/idf-docker-image.html
#		esptool and server: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/tools/idf-docker-image.html#using-remote-serial-port
#
#

#PORT_NAME:
#	find the right port name using the method described here: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/establish-serial-connection.html#check-port-on-linux-and-macos
#	
#	Once found, export the variable with: export PORT_NAME=<port name here>

#In order to start the server to flash, an environment variable name PORT_NAME must be exported
.PHONY: server
server: 
	@if [ -z "$$PORT_NAME" ]; then \
		echo "Please set the environment variable PORT_NAME to absolute path of the desired port"; \
	else \
		if ! pip show esptool &> /dev/null; then \
			echo "Please install esptool with: \$$pip install esptool (preferably in a virtual environment)"; \
		else \
			esp_rfc2217_server -v -p 4000 $$PORT_NAME &> /dev/null & \
		fi; \
	fi 

.PHONY: interactive
interactive:
	@docker run --rm -v $$PWD:/project -w /project -u $$UID -e HOME=/tmp -it espressif/idf		

.PHONY: set-target
set-target:
	@read -p "Enter a board type (e.g. esp32c6): " board_type; \
	docker run --rm -v $$PWD:/project -w /project -u $$UID -e HOME=/tmp espressif/idf idf.py set-target $${board_type}

.PHONY: build
build:
	@docker run --rm -v $$PWD:/project -w /project -u $$UID -e HOME=/tmp espressif/idf idf.py build

.PHONY: flash 
flash:
	@docker run --rm -v $$PWD:/project -w /project espressif/idf idf.py --port 'rfc2217://host.docker.internal:4000?ign_set_control' flash	

.PHONY: erase-flash
erase-flash:
	@docker run --rm -v $$PWD:/project -w /project espressif/idf idf.py --port 'rfc2217://host.docker.internal:4000?ign_set_control' erase-flash	

.PHONY: monitor
monitor:
	@if [ -z "$$PORT_NAME" ]; then \
		echo "Please set the environment variable PORT_NAME to absolute path of the desired port"; \
	else \
		if ! pip show esptool &> /dev/null; then \
			echo "Please install esptool with: \$$pip install esptool (preferably in a virtual environment)"; \
		else \
	docker run --rm -v $$PWD:/project -w /project -it espressif/idf idf.py monitor -p 'rfc2217://host.docker.internal:4000?ign_set_control'; \
		fi; \
	fi 
