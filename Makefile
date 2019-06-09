.PHONY: build
build:
	g++ include/services/adopter.h \
	include/services/animal.h \
	include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_db.h \
	include/services/sqlite3_interface.h \
	include/services/table_return.h \
	include/services/user.h \
	src/services/adopter.cpp \
	src/services/animal.cpp \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	src/services/user.cpp \
	main.cpp \
	-w \
	-lsqlite3

.PHONY: debug-build
debug-build:
	g++ include/services/adopter.h \
	include/services/animal.h \
	include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_db.h \
	include/services/sqlite3_interface.h \
	include/services/table_return.h \
	include/services/user.h \
	src/services/adopter.cpp \
	src/services/animal.cpp \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	src/services/user.cpp \
	main.cpp \
	-lsqlite3 \
	-g

.PHONY: run
run: 
	./a.out

.PHONY: debug
debug: 
	gdb ./a.out

	