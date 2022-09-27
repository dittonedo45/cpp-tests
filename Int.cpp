
#include <iostream>
extern "C" {
#include <ruby/ruby.h>
};

using namespace std;

struct shame_t {
	int n;
};

const rb_data_type_t sshme = {
	"sshame",
	{0, [](void *ptr){
			ruby_xfree (ptr);
		}, [](const void*) {
			    return sizeof (struct shame_t);
		    }
	}
};

VALUE sshame_alloc (VALUE a)
{
	VALUE b;
	struct shame_t *s;

	b=TypedData_Make_Struct (a, struct shame_t, &sshme, s);

	return b;
}
VALUE sshame_init (VALUE a)
{
	VALUE b;
	struct shame_t *s;

	TypedData_Get_Struct (a, struct shame_t, &sshme, s);
	s->n=2<<23;
	return a;
}
VALUE sshame_n (VALUE k)
{
	VALUE b;
	struct shame_t *s;

	TypedData_Get_Struct (k, struct shame_t, &sshme, s);
	return rb_funcall (LONG2NUM (s->n),
			rb_intern ("<<"), 1,
			LONG2NUM (899999l));
}

int main (int argsc, char **args)
{
	ruby_init ();
	ruby_init_loadpath ();

	VALUE vs;

	vs=rb_define_class ("Shame", rb_cObject);
	rb_define_alloc_func (vs, [](VALUE a)->VALUE
{
	VALUE b;
	struct shame_t *s;

	b=TypedData_Make_Struct (a, struct shame_t, &sshme, s);

	return b;
});
	rb_define_method (vs, "initialize",(VALUE(*)(...)) sshame_init, 0);
	rb_define_method (vs, "n", (VALUE(*)(...))sshame_n, 0);

	rb_funcall (rb_mKernel, rb_intern ("puts"), 1,
		rb_funcall (rb_funcall (vs, rb_intern ("new"), 0),
			rb_intern ("n"), 0)
		);

	ruby_finalize ();
	return( 0 );
}
