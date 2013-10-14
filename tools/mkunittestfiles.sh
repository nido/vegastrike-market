#!/bin/bash

NAME="$1"

if test "${NAME}" = ""
then

FILES=$(ls test/*Test.hpp | sed "s/test\/\([a-zA-Z]*\).hpp/\1/g")


for FILE in ${FILES}
do
	FUNC="`echo "${FILE}" | sed "s/Test$//g"`"

	UNITTESTCODE="${UNITTESTCODE}\n\tif (argc != 1 \&\& strcmp(argv[1], \"${FUNC}\") == 0 ){"
	UNITTESTCODE="${UNITTESTCODE}\n\t\tstd::cout<<argv[1]<<\": \";"
	UNITTESTCODE="${UNITTESTCODE}\n\t}"
	UNITTESTCODE="${UNITTESTCODE}\n\tif (argc == 1 || strcmp(argv[1], \"${FUNC}\") == 0){"
	UNITTESTCODE="${UNITTESTCODE}\n\t\t runner.addTest( ${FILE}::suite());"
	UNITTESTCODE="${UNITTESTCODE}\n\t}"

	INCLUDECODE="${INCLUDECODE}\n#include \"${FILE}.hpp\""
done

cat doc/unittest.template.main.cpp |
	sed "s/@unittestcode@/${UNITTESTCODE}/g" |
	sed "s/@includecode@/${INCLUDECODE}/g" > "test/main.cpp"

else

TESTS=$(cat "src/${NAME}.cpp" | 
	grep -Go "${NAME}::[^(]\+(" |
	grep -Go "${NAME}::[^(\ ]\+" | 
	sed "s/${NAME}::${NAME}//g" |
	sed "s/${NAME}::~${NAME}//g" |
	sed "s/${NAME}::/test/g" |
	sed "s/==/Equals/g" |
	sed "s/</LessThen/g" | 
	sort | uniq)

echo ${TESTS}

TESTCODE=""
SUITECODE=""
HEADERCODE=""
UNITTESTCODE=""
INCLUDECODE=""

for TEST in ${TESTS}
do
	TESTCODE="${TESTCODE}\nvoid ${NAME}Test::${TEST}()\n{"
	TESTCODE="${TESTCODE}\n\t\/\/TODO: Implement test"
	TESTCODE="${TESTCODE}\n\tCPPUNIT_ASSERT(false);"
	TESTCODE="${TESTCODE}\n}\n"

	HEADERCODE="${HEADERCODE}\n\tvoid ${TEST}();"

	SUITECODE="${SUITECODE}\n\tsuiteOfTests->addTest( new CppUnit::TestCaller<${NAME}Test>("
	SUITECODE="${SUITECODE}\n\t\t\t\"${TEST}\", \&${NAME}Test::${TEST}));\n"

done


cat doc/unittest.template.cpp | 
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@suitecode@/${SUITECODE}/g" |
	sed "s/@testcode@/${TESTCODE}/g" > test/${NAME}Test.cpp

cat doc/unittest.template.hpp |
	sed "s/@template@/${NAME}Test/g" |
	sed "s/@headercode@/${HEADERCODE}/g" > test/${NAME}Test.hpp

fi
