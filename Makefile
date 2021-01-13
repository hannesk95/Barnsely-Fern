all:
	@echo "This is a dummy to prevent running make without explicit target!"

clean: remove_srcfiles
	rm -f barnsley_farn

compile: clean
	mkdir -p src/build/
	cd src/build/ && cmake -DCMAKE_BUILD_TYPE=Release ..
	$(MAKE) -C src/build/
	mv src/build/barnsley_fern barnsley_fern
