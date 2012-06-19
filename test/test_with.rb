require 'test/unit'
require 'with'

class WithTest < Test::Unit::TestCase
  class SelfObj
    def initialize
      @ivar = "self_obj_ivar"
    end

    def self_obj_method
      return "self_obj_method"
    end
  end

  class DelegateObj
    def initialize
      @ivar = "delegate_obj_ivar"
    end

    def delegate_obj_method
      return "delegate_obj_method"
    end
  end

  def test_with_can_call_self_obj
    self_obj = SelfObj.new
    delegate_obj = DelegateObj.new
    result = self_obj.instance_eval do
      with(delegate_obj) do
        self_obj_method()
      end
    end
    assert_equal "self_obj_method", result
  end

  def test_with_can_call_delegate_obj
    self_obj = SelfObj.new
    delegate_obj = DelegateObj.new
    result = self_obj.instance_eval do
      with(delegate_obj) do
        delegate_obj_method()
      end
    end
    assert_equal "delegate_obj_method", result
  end

  def test_with_can_access_self_ivars
    self_obj = SelfObj.new
    delegate_obj = DelegateObj.new
    result = self_obj.instance_eval do
      with(delegate_obj) do
        @ivar
      end
    end
    assert_equal "self_obj_ivar", result
  end
end

