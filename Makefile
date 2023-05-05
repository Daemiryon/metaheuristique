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
main: build/main.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o build/verbose.o build/pizza.o build/population.o build/recuit.o
	gcc build/main.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o build/verbose.o build/pizza.o build/population.o build/recuit.o -o main -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -pthread -lm

build/main.o: build/ src/main.c src/io.h
	gcc -c src/main.c -o build/main.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

# TESTS
test_io: build/test_io.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o
	gcc build/test_io.o build/io.o build/list.o build/hashmap.o build/hash.o build/clients.o -o test_io -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/test_io.o: build/ src/tests/test_io.c src/io.h
	gcc -c src/tests/test_io.c -o build/test_io.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

# IO
build/io.o: build/ src/io.c src/io.h
	gcc -c src/io.c -o build/io.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

#SD
build/list.o: build/ src/hm/list.c src/hm/list.h
	gcc -c src/hm/list.c -o build/list.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/hashmap.o: build/ src/hm/hashmap.c src/hm/hashmap.h
	gcc -c src/hm/hashmap.c -o build/hashmap.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/hash.o: build/ src/hm/hash.c src/hm/hash.h
	gcc -c src/hm/hash.c -o build/hash.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/clients.o: build/ src/sd/clients.c src/sd/clients.h
	gcc -c src/sd/clients.c -o build/clients.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/pizza.o: build/ src/sd/pizza.c src/sd/pizza.h
	gcc -c src/sd/pizza.c -o build/pizza.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm

build/population.o: build/ src/sd/population.c src/sd/population.h
	gcc -c src/sd/population.c -o build/population.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -pthread -lm

build/recuit.o: build/ src/recuit.c src/recuit.h
	gcc -c src/recuit.c -o build/recuit.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -pthread -lm

#VERBOSE
build/verbose.o: build/ src/verbose.c src/verbose.h
	gcc -c src/verbose.c -o build/verbose.o -std=c99 -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -lm


######## ######## ########
########  CLEAN   ########
######## ######## ########
clean:
	rm -rf build/ main test_io