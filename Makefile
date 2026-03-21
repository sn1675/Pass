BUILD_DIR = build

all:
	cd $(BUILD_DIR) && qmake cestionaire.pro && make

run: all
	./$(BUILD_DIR)/cestionaire

clean:
	cd $(BUILD_DIR) && make clean
	rm -f $(BUILD_DIR)/Makefile $(BUILD_DIR)/*.o

.PHONY: all run clean
