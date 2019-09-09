#!/bin/bash

#
#	TODO :
#	CHECK LAST CYCLE USING ZAZ -v 2
#	Command line options (-v to check verbose, -d to check dump, both,
#	check diffs with given offset until cycle/end)
#	Verbose diff and recording
#

readonly GREEN="\e[92m"
readonly RED="\e[31m"
readonly CLR="\e[0;m"

PLAYER_1="Gagnant.cor"
PLAYER_2="NoIdea.cor"
ZAZ_VM="./resources/corewar"
MY_VM="./corewar"
ZAZ_ASM="./resources/asm"
CYCLE_TO_CHECK=1000000
DIFFS_FILE="vm_diffs.log"
NBR_OF_CHAMPS=1
CYCLE_OFFSET=1 # Our vm starts at cycle 1 instead of 0
CHAMPS_DIR="resources/test_champs"

function record_diff
{
	printf "#################################################################\n" >> $DIFFS_FILE
	printf "%s %s %s %s\n" $p1_name $p2_name $p3_name $p4_name >> $DIFFS_FILE
	printf "CYCLE $final_cycle\n" >> $DIFFS_FILE
	diff <(echo "$zaz_out") <(echo "$my_out") >> $DIFFS_FILE
}

function get_last_cycle
{
	final_cycle="$(echo "$my_out" | grep 'Dump at cycle' | awk 'NF>1{print $NF}')"
	final_cycle=${final_cycle%?}
	printf " %d " $final_cycle
	((final_cycle-=$CYCLE_OFFSET))
	printf " %d " $final_cycle
}

function check_diff_for_dump
{
	printf "%s %s %s %s\t\t: " $p1_name $p2_name $p3_name $p4_name | expand -t 40
	dump_cycle=$CYCLE_TO_CHECK
	my_out="$($MY_VM -dump $((dump_cycle)) $PLAYER_1 $PLAYER_2)"
	get_last_cycle
	my_out="$($MY_VM -dump $((final_cycle)) $PLAYER_1 $PLAYER_2)"
	my_out="$(echo "$my_out" | awk '$1 ~ /^0x/')"
	zaz_out="$($ZAZ_VM -d $final_cycle $PLAYER_1 $PLAYER_2 | awk '$1 ~ /^0x/')"
	if [ "$zaz_out" != "" ] && [ "$zaz_out" != "$my_out" ]; then
		printf "${RED}%s\n${CLR}" "DIFFERS"
		record_diff
	elif [ "$zaz_out" == "" ]; then
		printf "${RED}%s\n${CLR}" "CYCLE TOO HIGH"
	else
		printf "${GREEN}%s\n${CLR}" "OK"
	fi;
}

function compile_champs
{
	if [ ! -d $CHAMPS_DIR ]; then
		mkdir $CHAMPS_DIR
	fi
	echo "Compiling champions..."
	for champ in $CHAMPS_DIR/*.s; do
		compiled_champ="${champ/%.s/.cor}"
		$ZAZ_ASM $champ > /dev/null 2>&1
	done
	echo "Champions compiled !"
}

function get_target_champ
{
	if [ "$target_champ" == "1" ]; then
		PLAYER_1="$champ"
		p1_name="$(basename $PLAYER_1)"
	elif [ "$target_champ" == "2" ]; then
		PLAYER_2="$champ"
		p2_name="$(basename $PLAYER_2)"
	elif [ "$target_champ" == "3" ]; then
		PLAYER_3="$champ"
		p3_name="$(basename $PLAYER_3)"
	elif [ "$target_champ" == "4" ]; then
		PLAYER_4="$champ"
		p4_name="$(basename $PLAYER_4)"
	fi
}

function loop_over_champions
{
	target_champ=$1
	for champ in $CHAMPS_DIR/*.cor; do
		get_target_champ
		if [[ $target_champ -lt $NBR_OF_CHAMPS ]]; then
			loop_over_champions $((target_champ+1))
		else
			check_diff_for_dump
		fi
	done
}

printf "" > $DIFFS_FILE

compile_champs

PLAYER_1=""
PLAYER_2=""
PLAYER_3=""
PLAYER_4=""
p1_name=""
p2_name=""
p3_name=""
p4_name=""

loop_over_champions 1
