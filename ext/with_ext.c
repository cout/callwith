#include <ruby.h>
#include <st.h>

static VALUE rb_cWith = Qnil;

static VALUE with_s_create(VALUE klass, VALUE obj, VALUE self_obj)
{
  NEWOBJ(with, struct RObject);
  OBJSETUP(with, klass, T_OBJECT);
  VALUE self = (VALUE)with;

  VALUE s = rb_singleton_class(self);
  rb_iv_set(s, "__with_obj__", obj);
  rb_iv_set(s, "__with_self_obj__", self_obj);

  struct RBasic basic = *(RBASIC(self));
  *(ROBJECT(self)) = *(ROBJECT(self_obj));
  *(RBASIC(self)) = basic;

  return self;
}

static VALUE with_obj(VALUE self)
{
  return rb_iv_get(rb_singleton_class(self), "__with_obj__");
}

static VALUE with_self_obj(VALUE self)
{
  return rb_iv_get(rb_singleton_class(self), "__with_self_obj__");
}

void Init_with_ext()
{
  VALUE super = rb_class_boot(0);
  rb_cWith = rb_class_boot(super);
  rb_name_class(rb_cWith, rb_intern("With"));
  rb_const_set(rb_cObject, rb_intern("With"), rb_cWith);
  rb_global_variable(&rb_cWith);

  rb_undef_alloc_func(rb_cWith);
  rb_define_singleton_method(rb_cWith, "create", with_s_create, 2);
  rb_define_method(rb_cWith, "__instance_eval__", rb_obj_instance_eval, -1);
  rb_define_method(rb_cWith, "__with__obj__", with_obj, 0);
  rb_define_method(rb_cWith, "__with__self_obj__", with_self_obj, 0);
}

