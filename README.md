callwith
========

Synopsis
--------

`Object#callwith` is like `instance_eval`, but can still delegate back to the
original object if a method is not found.  Also unlike `instance_eval`,
all instance variables accessed within the block reference the original
self object.

    gem install callwith

    callwith(obj) do
      # stuff
    end

(this method was originally called `with` when it was part of
RubyTreasures, but has been renamed to `callwith` to avoid conflict with
the `with` gem).

Background
----------

One common problem with using `instance_eval` as a tool for brevity is
that it can easily become unclear which object is `self`.  For example,
the Tk library that comes with Ruby makes heavy use of `instance_eval`:

    class MyApplication
      def initialize
        @root = TkRoot.new
        TkFrame.new do
          TkButton.new do
            text "Ok"

            # The action() method will never be called, because this
            # block was called with instance_eval, so `self` is not
            # the MyApplication instance.
            command proc { action() }

            pack
          end
          pack
        end
      end

      def action()
        puts "Hello, world"
      end
    end

The `callwith` method will delegate method calls to the passed object;
however, if the passed object does not have such a method, `callwith` will
fall back onto calling on `self`.  For example:

    class HelloWorld
      def initialize
        @hello_count = 0
      end

      def hello(file)
        callwith(file) do
          write("Hello world") # writes "Hello world" to file
          increment()          # calls increment on the HelloWorld instance
        end
      end

      def increment
        @hello_count += 1
      end
    end

All accessed instance variables are in the `self` object, so we could
have written hello() like this:

    def hello(file)
      callwith(file) do
        write("Hello world")
        increment()
      end
    end

The `callwith` method can also iterate over multiple objects, e.g.:

    def hello(*files)
      callwith(*files) do
        write("Hello world")
        increment()
      end
    end

License
-------

License is the MIT License (http://www.opensource.org/licenses/mit-license.html) 

