%include 'class/class_view.inc'

	fn_function 'class/view/deinit'
		;inputs
		;r0 = object

		;deinit myself

		;deinit parent
		function_call ref, deinit
		vp_ret

	fn_function_end