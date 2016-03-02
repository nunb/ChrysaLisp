%ifndef CODE_1234
	%define CODE_1234

%include "inc/vp.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;
; some NASM codeing macros
;;;;;;;;;;;;;;;;;;;;;;;;;;

	%macro loop_start 0
			%push loop_begin
		%$loop_begin:
	%endmacro

	%macro loop_end 0
			continue
		%$loop_exit:
			%pop
	%endmacro

	%macro break 0
			vp_jmp %$loop_exit
	%endmacro

	%macro continue 0
			vp_jmp %$loop_begin
	%endmacro

	%macro continueif 3
			cmp %1, %3
			%ifidn %2, ==
				je %$loop_begin
			%elifidn %2, !=
				jne %$loop_begin
			%elifidn %2, <
				jl %$loop_begin
			%elifidn %2, >
				jg %$loop_begin
			%elifidn %2, <=
				jle %$loop_begin
			%elifidn %2, >=
				jge %$loop_begin
			%else
				j%+2 %$loop_begin
			%endif
	%endmacro

	%macro breakif 3
			cmp %1, %3
			%ifidn %2, ==
				je %$loop_exit
			%elifidn %2, !=
				jne %$loop_exit
			%elifidn %2, <
				jl %$loop_exit
			%elifidn %2, >
				jg %$loop_exit
			%elifidn %2, <=
				jle %$loop_exit
			%elifidn %2, >=
				jge %$loop_exit
			%else
				j%+2 %$loop_exit
			%endif
	%endmacro

	%macro jmpif 4
			cmp %1, %3
			%ifidn %2, ==
				je %4
			%elifidn %2, !=
				jne %4
			%elifidn %2, <
				jl %4
			%elifidn %2, >
				jg %4
			%elifidn %2, <=
				jle %4
			%elifidn %2, >=
				jge %4
			%else
				j%+2 %4
			%endif
	%endmacro

	%macro loop_until 3
				cmp %1, %3
			%ifidn %2, ==
				jne %$loop_begin
			%elifidn %2, !=
				je %$loop_begin
			%elifidn %2, <
				jge %$loop_begin
			%elifidn %2, >
				jle %$loop_begin
			%elifidn %2, <=
				jg %$loop_begin
			%elifidn %2, >=
				jl %$loop_begin
			%else
				j%-2 %$loop_begin
			%endif
		%$loop_exit:
			%pop
	%endmacro

	%macro loop_while 3
			%push loop_begin
		%$loop_begin:
				cmp %1, %3
			%ifidn %2, ==
				jne %$loop_exit
			%elifidn %2, !=
				je %$loop_exit
			%elifidn %2, <
				jge %$loop_exit
			%elifidn %2, >
				jle %$loop_exit
			%elifidn %2, <=
				jg %$loop_exit
			%elifidn %2, >=
				jl %$loop_exit
			%else
				j%-2 %$loop_exit
			%endif
	%endmacro

	%macro if 3
			%push if
				cmp %1, %3
			%ifidn %2, ==
				jne %$ifnot
			%elifidn %2, !=
				je %$ifnot
			%elifidn %2, <
				jge %$ifnot
			%elifidn %2, >
				jle %$ifnot
			%elifidn %2, <=
				jg %$ifnot
			%elifidn %2, >=
				jl %$ifnot
			%else
				j%-2 %$ifnot
			%endif
	%endmacro

	%macro else 0
		%ifctx if
				%repl else
				vp_jmp %$ifend
			%$ifnot:
		%else
			%error "expected `if' before `else'"
		%endif
	%endmacro

	%macro endif 0
		%ifctx if
			%$ifnot:
				%pop
		%elifctx else
			%$ifend:
				%pop
		%else
			%error "expected `if' or `else' before `endif'"
		%endif
	%endmacro

	%macro for 4
			vp_cpy %2, %1
			loop_start
				%define %$__reg %1
				%define %$__step %4
				breakif %1, ge, %3
	%endmacro

	%macro next 0
				vp_add %$__step, %$__reg
			loop_end
	%endmacro

	%macro switch 0
			%push switch
			%assign %$__curr 1
	%endmacro

	%macro case 3
		%$loc%$__curr:
			%assign %$__curr %$__curr+1
			cmp %1, %3
			%ifidn %2, ==
				jne %$loc%$__curr
			%elifidn %2, !=
				je %$loc%$__curr
			%elifidn %2, <
				jge %$loc%$__curr
			%elifidn %2, >
				jle %$loc%$__curr
			%elifidn %2, <=
				jg %$loc%$__curr
			%elifidn %2, >=
				jl %$loc%$__curr
			%else
				j%-2 %$loc%$__curr
			%endif
	%endmacro

	%macro default 0
		%$loc%$__curr:
	%endmacro

	%macro endswitch 0
		%$loop_exit:
			%pop
	%endmacro

%endif