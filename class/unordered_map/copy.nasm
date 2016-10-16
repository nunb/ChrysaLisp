%include 'inc/func.inc'
%include 'class/class_unordered_map.inc'
%include 'class/class_vector.inc'
%include 'class/class_pair.inc'

	def_function class/unordered_map/copy
		;inputs
		;r0 = unordered_map object
		;r1 = num buckets
		;outputs
		;r0 = unordered_map object
		;r1 = unordered_map copy
		;trashes
		;all but r0, r4

		def_structure local
			ptr local_inst
			ptr local_obj
		def_structure_end

		;save inputs
		vp_sub local_size, r4
		set_src r0
		set_dst [r4 + local_inst]
		map_src_to_dst

		s_call unordered_map, create, {[r0 + unordered_set_key_callback], r1}, {[r4 + local_obj]}
		s_call unordered_map, for_each, {[r4 + local_inst], $callback, r4}, {_, _}

		vp_cpy [r4 + local_obj], r1
		vp_add local_size, r4
		vp_ret

	callback:
		;inputs
		;r0 = predicate data pointer
		;r1 = element iterator
		;outputs
		;r1 = 0 if break, else not

		vp_cpy r0, r2
		s_call ref, ref, {[r1]}
		vp_push r0
		s_call unordered_map, get_bucket, {[r2 + local_obj], [r0 + pair_first]}, {r0}
		vp_pop r1
		s_call vector, push_back, {r0, r1}
		vp_cpy 1, r1
		vp_ret

	def_function_end
