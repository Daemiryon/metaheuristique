######## ######## ########
########   MAIN   ########
######## ######## ########
MAIN: main

recompile: clean MAIN

######## ######## ########
########  BUILD   ########
######## ######## ########
build/:
	mkdir -p build/

# MAIN
main: build/main.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o
	gcc build/main.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o -o main -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

build/main.o: build/ src/main.c src/io.h
	gcc -c src/main.c -o build/main.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

# TESTS
test_io: build/test_io.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o
	gcc build/test_io.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o -o test_io -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

build/test_io.o: build/ src/tests/test_io.c src/io.h
	gcc -c src/tests/test_io.c -o build/test_io.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

# IO
build/io.o: build/ src/io.c src/io.h
	gcc -c src/io.c -o build/io.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

#HM
build/list.o: build/ src/hm/list.c src/hm/list.h
	gcc -c src/hm/list.c -o build/list.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

build/hashmap.o: build/ src/hm/hashmap.c src/hm/hashmap.h
	gcc -c src/hm/hashmap.c -o build/hashmap.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

build/hash.o: build/ src/hm/hash.c src/hm/hash.h
	gcc -c src/hm/hash.c -o build/hash.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

build/clients.o: build/ src/sd/clients.c src/sd/clients.h
	gcc -c src/sd/clients.c -o build/clients.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

######## ######## ########
########  CLEAN   ########
######## ######## ########
clean:
	rm -rf build/ main test_io