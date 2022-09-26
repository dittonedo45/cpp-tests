#include <iostream>
extern "C" {
#include <ruby/ruby.h>
};

using namespace std;

int main (int argsc, char **args)
{
	ruby_init ();
	ruby_init_loadpath ();

	rb_define_global_function ("fun",(VALUE(*)(...))
			+[](int argsc,  const VALUE* args,VALUE self) -> VALUE
{
	if (argsc==0)
		rb_raise (rb_eException, "!args not enough");
	cout << string (RSTRING_PTR (rb_obj_as_string (args[0]))) << endl;
	return Qnil;
}, -1);

	int s;
	rb_load_protect (rb_str_new_cstr (args[1]),
			0, &s);

	ruby_finalize ();
	return( 0 );
}
