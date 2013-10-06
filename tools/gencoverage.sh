#!/bin/bash -x
test -f CMakeLists.txt || 
	echo You wanna execute this from the directory containing CMakeLists.txt.
test -f CMakeLists.txt || 
	exit
test -f  CMakeCache.txt && rm CMakeCache.txt

BUILDDIR=coveragebuild
mkdir -p "${BUILDDIR}" 
cd "${BUILDDIR}"

# make alterations for older versions of lcov
if `lcov -rc bla=bla 2>&1 | grep -q "lcov: Unknown option: rc"`
then
LCOV="lcov --quiet"
else
LCOV="lcov --quiet --rc lcov_branch_coverage=1"
fi

GENHTML=genhtml
# make alterations for older versions of lcov
genhtml --demangle-cpp -v && GENHTML="${GENHTML} --demangle-cpp"
genhtml --branch-coverage -v && GENHTML="${GENHTML} --branch-coverage"


cmake -D"CMAKE_CXX_FLAGS:string=-g -fprofile-arcs -ftest-coverage -DNDEBUG" ..

# clean up previous coverage files
find . -type f -iname \*.gcno -exec rm -f {} \;
make clean

# compile
make

# Get all unit tests
TESTCASES=$(ls "../test/" | grep -Go ".*Test" | sort | uniq)

# override with command line argument test when given
if test -n "$1"
then
TESTCASES="$1"
fi

# run all tests separately
for TEST in ${TESTCASES};
do
        $LCOV -z --directory "." -o coverage${TEST}.info
        ./cppunittest ${TEST} 2>&1 | grep -v "^[[:space:]]*$"
        $LCOV -c -t ${TEST} --directory "." -o coverage${TEST}.info 2>&1 |
			grep -v "geninfo: WARNING: no data found for .*usr.*include.*"
        $LCOV -r coverage${TEST}.info "*usr*include*" -o codecoverage${TEST}.info
        #$LCOV -e coverage${TEST}.info "`realpath ..`" -o codecoverage${TEST}.info
        #cp coverage${TEST}.info codecoverage${TEST}.info
done

# combine the coverage data
$LCOV -o codecoverage.info -a codecoverage`echo ${TESTCASES} | sed "s/ /.info -a codecoverage/g"`.info

# remove stuff outside the sourcedir.
$LCOV -r codecoverage.info "/usr*/include/*" -o coverage.info

# create html page
$GENHTML --legend --show-details --title "Vegastrike Economy" codecoverage.info --output-directory "./coverage/"

# report a summary
lcov --summary codecoverage.info 2>&1 | grep lines | grep -Go "[0-9]\+\.[0-9]%"

