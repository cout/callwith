require 'with_ext'

def with(*objs, &block)
  last = nil
  objs.each do |obj|
    p = With.create(obj, self)
    last = p.__instance_eval__(&block)
  end
  return last
end

class With
  def method_missing(method, *args, &block)
    obj = __with__obj__()
    self_obj = __with__self_obj__()

    if obj.respond_to?(method)
      obj.__send__(method, *args, &block)
    else
      self_obj.__send__(method, *args, &block)
    end
  end
end

