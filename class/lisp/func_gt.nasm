%include 'inc/func.inc'
%include 'class/class_vector.inc'
%include 'class/class_boxed_long.inc'
%include 'class/class_error.inc'
%include 'class/class_lisp.inc'

;gt monotonically decreasing

def_func class/lisp/func_gt
	;inputs
	;r0 = lisp object
	;r1 = args
	;outputs
	;r0 = lisp object
	;r1 = value

	def_struct pdata
		ptr pdata_this
		ptr pdata_value
		long pdata_num
	def_struct_end

	ptr this, value
	long num

	ptr args, first
	ulong length

	push_scope
	retire {r0, r1}, {this, args}

	devirt_call vector, get_length, {args}, {length}
	if {length > 1}
		func_call vector, get_element, {args, 0}, {first}
		if {first->obj_vtable == @class/class_boxed_long}
			func_call boxed_long, get_value, {first}, {num}
			assign {this->lisp_sym_t}, {value}
			func_call ref, ref, {value}
			func_call vector, for_each, {args, 1, length, $callback, &this}, {_}
		else
			func_call error, create, {"(gt num num ...) not all numbers", first}, {value}
		endif
	else
		func_call error, create, {"(gt num num ...) wrong number of args", args}, {value}
	endif

	eval {this, value}, {r0, r1}
	pop_scope
	return

callback:
	;inputs
	;r0 = predicate data pointer
	;r1 = element iterator
	;outputs
	;r1 = 0 if break, else not

	pptr iter
	ptr pdata
	long num

	push_scope
	retire {r0, r1}, {pdata, iter}

	if {(*iter)->obj_vtable == @class/class_boxed_long}
		func_call boxed_long, get_value, {*iter}, {num}
		if {pdata->pdata_num > num}
			assign {num}, {pdata->pdata_num}
			eval {1}, {r1}
			return
		else
			func_call ref, deref, {pdata->pdata_value}
			assign {pdata->pdata_this->lisp_sym_nil}, {pdata->pdata_value}
			func_call ref, ref, {pdata->pdata_value}
		endif
	else
		func_call ref, deref, {pdata->pdata_value}
		func_call error, create, {"(gt num num ...) not all numbers", *iter}, {pdata->pdata_value}
	endif

	eval {0}, {r1}
	pop_scope
	return

def_func_end