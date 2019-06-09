.PHONY: build
build:
	g++ include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_interface.h \
	include/services/sqlite3_db.h \
	include/services/table_return.h \
	include/services/adopter.h \
	include/services/animal.h \
	include/services/user.h \
	include/services/dsl.h \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	src/services/adopter.cpp \
	src/services/animal.cpp \
	src/services/user.cpp \
	src/services/dsl.cpp \
	main.cpp \
	-w \
	-lsqlite3

.PHONY: debug-build
debug-build:
	g++ include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_interface.h \
	include/services/sqlite3_db.h \
	include/services/table_return.h \
	include/services/adopter.h \
	include/services/animal.h \
	include/services/user.h \
	include/services/dsl.h \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	src/services/dsl.cpp \
	main.cpp \
	-lsqlite3 \
	-g

.PHONY: run
run: 
	./a.out

.PHONY: debug
debug: 
	gdb ./a.out

	