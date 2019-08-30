#!/bin/bash

PLAYER_1="Gagnant.cor"
PLAYER_2="NoIdea.cor"
ZAZ_VM="./resources/corewar"
MY_VM="./corewar"
ZAZ_ASM="./resources/asm"
CYCLES_TO_CHECK=2300
CYCLES_INTERVAL=50
DIFFS_FILE="vm_diffs.log"

function record_diff
{
	p1_name="$(basename $PLAYER_1)"
	p2_name="$(basename $PLAYER_2)"
	printf "$p1_name against $p2_name\n" > $DIFFS_FILE
	printf "CYCLE $dump_cycle\n" >> $DIFFS_FILE
	diff <(echo "$zaz_out") <(echo "$my_out") >> $DIFFS_FILE
}

function check_diff_for_dump
{
	echo "Checking $PLAYER_1 against $PLAYER_2"
	dump_cycle=$1
	zaz_out="$($ZAZ_VM -d $dump_cycle $PLAYER_1 $PLAYER_2 | awk '$1 ~ /^0x/')"
	my_out="$($MY_VM -dump $((dump_cycle+1)) $PLAYER_1 $PLAYER_2 | awk '$1 ~ /^0x/')"
	if [ "$zaz_out" != "" ] && [ "$zaz_out" != "$my_out" ]; then
		echo "DIFF : $PLAYER_1 against $PLAYER_2 at CYCLE $dump_cycle"
		record_diff
		exit
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

compile_champs

for champ_1 in resources/compiled_champs/*.cor; do
	PLAYER_1="$champ_1"
	for champ_2 in resources/compiled_champs/*.cor; do
		PLAYER_2="$champ_2"
		if [ "$champ_1" != "$champ_2" ]; then
			check_diff_for_dump 1000
		fi;
	done
done

exit

cycles=1
while [ $cycles -le $CYCLES_TO_CHECK ]; do
	check_diff_for_dump $cycles
	printf "$cycles "
	((cycles+=$CYCLES_INTERVAL))
done
echo "$PLAYER_1 against $PLAYER_2 : OK !"
