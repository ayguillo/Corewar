.name	"Corruption"

.comment "Pour la horde"

zjmp	%0
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1

fork %:secondattack
begin:
	lfirst:	sti r1, %:lf, %1
	lf:		live %1
	l1:		sti r1, %:live, %1

firstattack:
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	ld	%190055683, r2
	ld	%118030341, r3
	ld	%150, r5
	ld	%50, r6
	loop:
		live: live %1
		sti	r2, %2, r5
		sti r3, %0, r5
		add r5, r6, r5
		add	r16, r16, r16
		zjmp %:loop

secondattack:
		here:	sti r1, %:bouh, %1
		live	%1
		live	%1
		live	%1
		bouh:	live	%1
		fork	%:load
		ld		%190055683, r5
		ld		%0, r3
		ld		%10, r7
		add	r16, r16, r16
		live	%1
		zjmp	%366
	load:
		ld		%117506048, r5
		ld		%0, r3
		ld		%14, r7
		add	r16, r16, r16
		live %1
		zjmp	%332
