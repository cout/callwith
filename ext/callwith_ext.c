#include <ruby.h>
#include <st.h>

static VALUE rb_cCallWith = Qnil;

static VALUE callwith_s_create(VALUE klass, VALUE obj, VALUE self_obj)
{
  /* Create a new CallWith object, bypassing the usual object creation,
   * because the CallWith class is not a normal class. */
  NEWOBJ(with, struct RObject);
  OBJSETUP(with, klass, T_OBJECT);
  VALUE self = (VALUE)with;

  /* Place our delegate objects into the singleton class so we can
   * access them later */
  VALUE s = rb_singleton_class(self);
  rb_iv_set(s, "__with_obj__", obj);
  rb_iv_set(s, "__with_self_obj__", self_obj);

  /* Copy the pointer to the instance variable table from self_obj.  As
   * long as we hold a reference to self_obj, this pointer should be
   * valid. */
  struct RBasic basic = *(RBASIC(self));
  *(ROBJECT(self)) = *(ROBJECT(self_obj));
  *(RBASIC(self)) = basic;

  return self;
}

static VALUE callwith_obj(VALUE self)
{
  return rb_iv_get(rb_singleton_class(self), "__with_obj__");
}

static VALUE callwith_self_obj(VALUE self)
{
  return rb_iv_get(rb_singleton_class(self), "__with_self_obj__");
}

static VALUE callwith_cleanup(VALUE self)
{
  /* We don't want to keep the ivar table pointer around indefinitely,
   * because if we do, the GC will free the ivar table, which is
   * undesirable, since the original object still references it.  So we
   * set the ivar table back to something that won't get freed, instead.
   */

  NEWOBJ(dummy, struct RObject);
  OBJSETUP(dummy, rb_cCallWith, T_OBJECT);

  struct RBasic basic = *(RBASIC(self));
  *(ROBJECT(self)) = *(ROBJECT(dummy));
  *(RBASIC(self)) = basic;
}

void Init_with_ext()
{
  VALUE super = rb_class_boot(0);
  rb_cCallWith = rb_class_boot(super);
  rb_name_class(rb_cCallWith, rb_intern("CallWith"));
  rb_const_set(rb_cObject, rb_intern("CallWith"), rb_cCallWith);
  rb_global_variable(&rb_cCallWith);

  rb_undef_alloc_func(rb_cCallWith);
  rb_define_singleton_method(rb_cCallWith, "create", callwith_s_create, 2);
  rb_define_method(rb_cCallWith, "__instance_eval__", rb_obj_instance_eval, -1);
  rb_define_method(rb_cCallWith, "__with__obj__", callwith_obj, 0);
  rb_define_method(rb_cCallWith, "__with__self_obj__", callwith_self_obj, 0);
  rb_define_method(rb_cCallWith, "__with__cleanup__", callwith_cleanup, 0);
}

