
MAKE = make

ROSE_SKETCH = rose_sketch/Debug/rose_sketch.a
TENSORFLOW_MICROLITE = tensorflow-microlite/Debug/tensorflow-microlite.a
FREE_RTOS = free_rtos/Debug/free_rtos.elf
HELLO_WORLD = hello_world/Debug/hello_world.elf
MAGIC_WAND = magic_wand/Debug/magic_wand.elf
MICRO_SPEECH = micro_speech/Debug/micro_speech.elf
PERSON_DETECTION = person_detection/Debug/person_detection.elf

$(ROSE_SKETCH): rose_sketch/Makefile
	$(MAKE) -j -C rose_sketch all

$(TENSORFLOW_MICROLITE): tensorflow-microlite/Makefile
	$(MAKE) -j -C tensorflow-microlite all

$(FREE_RTOS): rose_sketch/Makefile $(ROSE_SKETCH)
	$(MAKE) -j -C free_rtos all

$(HELLO_WORLD): hello_world/Makefile $(ROSE_SKETCH) $(TENSORFLOW_MICROLITE)
	$(MAKE) -j -C hello_world all

$(MAGIC_WAND): magic_wand/Makefile $(ROSE_SKETCH) $(TENSORFLOW_MICROLITE)
	$(MAKE) -j -C magic_wand all

$(MICRO_SPEECH): micro_speech/Makefile $(ROSE_SKETCH) $(TENSORFLOW_MICROLITE)
	$(MAKE) -j -C micro_speech all

$(PERSON_DETECTION): person_detection/Makefile $(ROSE_SKETCH) $(TENSORFLOW_MICROLITE)
	$(MAKE) -j -C person_detection all

.PHONY: refresh
refresh:
	rm -f $(FREE_RTOS) $(HELLO_WORLD) $(MAGIC_WAND) $(MICRO_SPEECH) $(PERSON_DETECTION)

.PHONY: all
all: refresh $(FREE_RTOS) $(HELLO_WORLD) $(MAGIC_WAND) $(MICRO_SPEECH) $(PERSON_DETECTION)

.PHONY: clean
clean:
	$(MAKE) -j -C rose_sketch clean
	$(MAKE) -j -C tensorflow-microlite clean
	$(MAKE) -j -C free_rtos clean
	$(MAKE) -j -C hello_world clean
	$(MAKE) -j -C magic_wand clean
	$(MAKE) -j -C micro_speech clean
	$(MAKE) -j -C person_detection clean
