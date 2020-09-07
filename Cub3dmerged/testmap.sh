TEST_COUNT=10
CUB3D=./a.out
MAPS_FOLDER=./maps/

MAIN_BG="\033[46;30m"
ALERT_BG="\033[41;4;30m"
SUCCESS_BG="\033[42;1;37m"
EXAMPLE_BG="\033[32m"
FAIL_BG="\033[41;5;11m"
END_BG="\033[41;5;30m"
CLEAR_COLOR="\033[m"

echo -e "${MAIN_BG}--------------TEST START----------------${CLEAR_COLOR}"
sleep 1

echo -e "COMPILING CUB3D"
make compile

IFS='
'

for i in $(ls ${MAPS_FOLDER})
do
	TEST_MAP=${i}
	echo -e "\n\t\t${MAIN_BG}${TEST_MAP}${CLEAR_COLOR}\n"
	${CUB3D} ${MAPS_FOLDER}${TEST_MAP}
	if [ $? ]
	then
		echo -e "\n${SUCCESS_BG}-->PASS${CLEAR_COLOR}"
	else
		echo -e "\n${FAIL_BG}-->FAIL${CLEAR_COLOR}"
	fi
done