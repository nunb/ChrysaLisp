%include 'class/class_obj.inc'

	fn_function 'class/obj/new'
		;outputs
		;r0 = 0 if error, else object

		;allways error
		vp_xor r0, r0
		vp_ret

	fn_function_end