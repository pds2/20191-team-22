.PHONY: build
build:
	g++ include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_interface.h \
	include/services/sqlite3_db.h \
	include/services/table_return.h \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	main.cpp \
	-lsqlite3

.PHONY: debug-build
debug-build:
	g++ include/services/controller.h \
	include/services/http_server.h \
	include/services/sqlite3_interface.h \
	include/services/sqlite3_db.h \
	include/services/table_return.h \
	src/services/controller.cpp \
	src/services/http_server.cpp \
	src/services/sqlite3_db.cpp \
	main.cpp \
	-lsqlite3 \
	-g

.PHONY: run
run: 
	./a.out

.PHONY: debug
debug: 
	gdb ./a.out

	