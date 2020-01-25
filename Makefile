
MAKE = make

.PHONY: all
all:
	$(MAKE) -j -C rose_sketch all
	$(MAKE) -j -C tensorflow-microlite all
	$(MAKE) -j -C free_rtos all
	$(MAKE) -j -C hello_world all
	$(MAKE) -j -C magic_wand all
	$(MAKE) -j -C micro_speech all
	$(MAKE) -j -C person_detection all

.PHONY: clean
clean:
	$(MAKE) -j -C rose_sketch clean
	$(MAKE) -j -C tensorflow-microlite clean
	$(MAKE) -j -C free_rtos clean
	$(MAKE) -j -C hello_world clean
	$(MAKE) -j -C magic_wand clean
	$(MAKE) -j -C micro_speech clean
	$(MAKE) -j -C person_detection clean
