#!/bin/bash
REQDOC=doc/reqeng.md
test -n "$1" && REQDOC="$1"

cat $REQDOC | while read line
do

if echo "${line}" | grep -q -- ----
then
	
	test "${RAT}" = "false" && echo "warning: \"${FUNC}\" does not define Rationale"
	test "${FIT}" = "false" && echo "warning: \"${FUNC}\" does not define Fit Criterion"
	#test "${DEPIMP}" = "false" && echo "warning: \"${FUNC}\" does not define Dependency/Implementation"

	FUNC="${lastline}"
	RAT=false
	FIT=false
	DEPIMP=false
	DEP=false
fi

if echo "${line}" | grep -q "^\*Rationale\*:"
then
	test "${RAT}" = "true" && echo "warning: ${FUNC} redefines Rationale"
	RAT=true
fi

if echo "${line}" | grep -q "^\*Fit Criterion\*:"
then
	test "${FIT}" = "true" && echo "warning: ${FUNC} redefines Fit Criterion"
	FIT=true
fi

if echo "${line}" | grep -q "^\*\(Dependencies\|Implementation\)\*:"
then
	test "${DEPIMP}" = "true" && echo "warning: ${FUNC} redefines Dependency/Implementation"
	DEPIMP=true
fi
if echo "${line}" | grep -q "^\*\(Dependencies\)\*:"
then
	DEP=true
fi

lastline="${line}"
done
