%ifndef CLASS_VIEW_1234
    %define CLASS_VIEW_1234

%include 'class/class_ref.inc'

    def_class view, ref
	def_method_override view, create, class/view/create
	def_method_override view, new, class/view/new
    def_method_override view, init, class/view/init
    def_method_override view, deinit, class/view/deinit
    def_method view, add, class/view/add
    def_method view, sub, class/view/sub

	struc VIEW
		VIEW_PARENT:	resb REF_SIZE
		VIEW_SIZE:
	endstruc

%endif