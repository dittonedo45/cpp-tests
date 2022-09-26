#include <iostream>
extern "C" {
#include <ruby/ruby.h>
#include <git2.h>
};

using namespace std;

int main (int argsc, char **args)
{
	ruby_init ();
	git_libgit2_init ();
	ruby_init_loadpath ();

	rb_define_global_function ("fun",(VALUE(*)(...))
			+[](int argsc,  const VALUE* args,VALUE self) -> VALUE
{
	if (argsc==0)
		rb_raise (rb_eException, "!args not enough");
	git_repository *repo=0;
	int ret=0;

	ret = git_repository_open (&repo, RSTRING_PTR (rb_obj_as_string (args[0])));
	if (ret) 
	{
		return Qfalse;
	}
	git_repository_free (repo);
	return true;
}, -1);

	int s=0;
	rb_load_protect (rb_str_new_cstr (args[1]),
			0, &s);
	if (s)
	{
		cout << RSTRING_PTR (rb_obj_as_string (rb_errinfo ())) << endl;
	}
	git_libgit2_shutdown ();
	ruby_finalize ();
	return( 0 );
}
