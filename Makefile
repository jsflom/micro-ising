#Makefile for building esp-idf projects

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
