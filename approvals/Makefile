###################################
# Makefile
###################################
CC = g++
INCLUDE = -I ../igloo
CFLAGS = -lpthread -Wall 
CHECK = cppcheck -v --inline-suppr --enable=all
FORMAT = astyle -YfDHUbps4yj -k3 

all: runtest 

runtest: NamerTests StringWriterTests ReporterTests FileApproverTests ApprovalExceptionTests ApprovalsTests
	./test/bin/NamerTests
	./test/bin/StringWriterTests
	./test/bin/ReporterTests
	./test/bin/FileApproverTests
	./test/bin/ApprovalExceptionTests
	./test/bin/ApprovalsTests

ApprovalExceptionTests: test/ApprovalExceptionTests.cpp ApprovalException.h
	$(FORMAT) test/ApprovalExceptionTests.cpp
	$(CHECK) test/ApprovalExceptionTests.cpp
	g++ $(INCLUDE) test/ApprovalExceptionTests.cpp -o test/bin/ApprovalExceptionTests -g $(CFLAGS)

ApprovalsTests: test/ApprovalsTests.cpp Approvals.gch
	$(FORMAT) test/ApprovalsTests.cpp
	$(CHECK) test/ApprovalsTests.cpp
	g++ $(INCLUDE) test/ApprovalsTests.cpp -o test/bin/ApprovalsTests -g $(CFLAGS)

NamerTests: test/NamerTests.cpp Namer.h IglooNamerFactory.h
	$(FORMAT) test/NamerTests.cpp
	$(CHECK) --suppress=unmatchedSuppression test/NamerTests.cpp
	g++ $(INCLUDE) test/NamerTests.cpp -o test/bin/NamerTests -g $(CFLAGS)

StringWriterTests: test/StringWriterTests.cpp StringWriter.h
	$(FORMAT) test/StringWriterTests.cpp
	$(CHECK) test/StringWriterTests.cpp
	g++ $(INCLUDE) test/StringWriterTests.cpp -o test/bin/StringWriterTests -g $(CFLAGS)

ReporterTests: test/reporters/ReporterTests.cpp reporters/Reporter.h
	$(FORMAT) test/reporters/ReporterTests.cpp
	$(CHECK) test/reporters/ReporterTests.cpp
	g++ $(INCLUDE) test/reporters/ReporterTests.cpp -o test/bin/ReporterTests -g $(CFLAGS)

FileApproverTests: test/FileApproverTests.cpp reporters/Reporter.h FileApprover.h
	$(FORMAT) test/FileApproverTests.cpp
	$(CHECK) test/FileApproverTests.cpp
	g++ $(INCLUDE) test/FileApproverTests.cpp -o test/bin/FileApproverTests -g $(CFLAGS)

Approvals.gch: Approvals.h
	$(FORMAT) Approvals.h
	$(CHECK) Approvals.h
	$(CC) $(INCLUDE) -c Approvals.h -O3 -Wall

ApprovalException.h: ApprovalException.gch

ApprovalException.gch:
	$(FORMAT) ApprovalException.h
	$(CHECK) ApprovalException.h
	g++ -c ApprovalException.h -O3 -Wall

CommandLauncher.h: reporters/CommandLauncher.h
	$(FORMAT) reporters/CommandLauncher.h
	$(CHECK) reporters/CommandLauncher.h
	g++ -c reporters/CommandLauncher.h -O3 -Wall

FileApprover.h: FileApprover.gch ApprovalException.h

FileApprover.gch: 
	$(FORMAT) FileApprover.h
	$(CHECK) FileApprover.h
	g++ $(INCLUDE) -c FileApprover.h -O3 -Wall

Reporter.h: reporters/Reporter.h reporters/CommandLauncher.h
	$(FORMAT) reporters/Reporter.h
	$(CHECK) reporters/Reporter.h
	g++ -c reporters/Reporter.h -O3 -Wall

Namer.h: namers/Namer.h
	$(FORMAT) namers/Namer.h
	$(CHECK) namers/Namer.h
	g++ $(INCLUDE) -c namers/Namer.h -O3 -Wall

IglooNamerFactory.h: namers/IglooNamerFactory.h Namer.h
	$(FORMAT) namers/IglooNamerFactory.h
	$(CHECK) --suppress=unmatchedSuppression namers/IglooNamerFactory.h
	$(CC) $(INCLUDE) -c namers/IglooNamerFactory.h -O3 -Wall

StringWriter.h:
	$(FORMAT) StringWriter.h
	$(CHECK) StringWriter.h
	g++ -c StringWriter.h -O3 -Wall

format: 
	astyle -YfDHUbps4yj -k3 $(SRCS)

check: format
	cppcheck -v --inline-suppr --suppress=unmatchedSuppression --enable=all $(SRCS)

clean:
	rm -f *.gch *.orig ./test/*.orig ./test/bin/*Tests namers/*.gch namers/*.orig reporters/*.gch reporters/*.orig

# DO NOT DELETE