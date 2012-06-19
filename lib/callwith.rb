require 'with_ext'

# Iterate over the given objects and delegate all instance method calls
# in the block to the object.  Instance variables accessed from inside
# the block are delegated to the receiver of the method.  Returns the
# result of the last expression evaluated.
#
# Example:
#
#     callwith(file1, file2) do
#       write("this is a test")
#     end
#
def callwith(*objs, &block)
  last = nil
  objs.each do |obj|
    p = CallWith.create(obj, self)
    last = p.__instance_eval__(&block)
  end
  return last
end

class CallWith
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

