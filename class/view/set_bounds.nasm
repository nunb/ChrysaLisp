%include 'inc/func.inc'
%include 'class/class_view.inc'

	fn_function class/view/set_bounds
		;inputs
		;r0 = view object
		;r8 = x
		;r9 = y
		;r10 = width
		;r11 = height

		vp_cpy r8, [r0 + view_x]
		vp_cpy r9, [r0 + view_y]
		vp_cpy r10, [r0 + view_w]
		vp_cpy r11, [r0 + view_h]
		vp_ret

	fn_function_end