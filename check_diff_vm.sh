#!/bin/bash

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
	echo "Compiling champions..."
	for champ in resources/champs/*.s; do
		compiled_champ="${champ/%.s/.cor}"
		$ZAZ_ASM $champ > /dev/null 2>&1
		mv $compiled_champ resources/compiled_champs > /dev/null 2>&1
	done
	echo "Champions compiled !"
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

for champ_1 in resources/compiled_champs/*.cor; do
	PLAYER_1="$champ_1"
	p1_name="$(basename $PLAYER_1)"
	if [ $NBR_OF_CHAMPS == 1 ]; then
		check_diff_for_dump
	else
		for champ_2 in resources/compiled_champs/*.cor; do
			PLAYER_2="$champ_2"
			p2_name="$(basename $PLAYER_2)"
			if [ $NBR_OF_CHAMPS == 2 ]; then
				if [ "$champ_2" != "$champ_1" ]; then
					check_diff_for_dump
				fi
			elif [ "$champ_2" != "$champ_1" ]; then
				for champ_3 in resources/compiled_champs/*.cor; do
					PLAYER_3="$champ_3"
					p3_name="$(basename $PLAYER_3)"
					if [ $NBR_OF_CHAMPS == 3 ]; then
						if [ "$champ_3" != "$champ_2" ] && [ "$champ_3" != "$champ_1" ]; then
							check_diff_for_dump
						fi
					elif [ "$champ_3" != "$champ_2" ] && [ "$champ_3" != "$champ_1" ]; then
						for champ_4 in resources/compiled_champs/*.cor; do
							PLAYER_4="$champ_4"
							p4_name="$(basename $PLAYER_4)"
							if [ "$champ_4" != "$champ_3" ] && [ "$champ_4" != "$champ_2" ] && [ "$champ_4" != "$champ_1" ]; then
								check_diff_for_dump
							fi
						done
					fi
				done
			fi
		done
	fi
done
