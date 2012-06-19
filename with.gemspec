spec = Gem::Specification.new do |s|
  s.name = 'with'
  s.version = '0.0.1'
  s.summary = 'With'
  s.homepage = 'http://github.com/cout/with/'
  s.author = 'Paul Brannan'
  s.email = 'curlypaul924@gmail.com'
  s.description = <<-END_DESCRIPTION
Object#with is like instance_eval, but can still delegate back to the
original object if a method is not found.  Also unlike instance_eval,
all instance variables accessed within the block reference the original
self object.
  END_DESCRIPTION

  s.files = [
    'ext/extconf.rb',
    'ext/with_ext.c',
    'lib/with.rb',
    'test/test_with.rb',
    ]

  s.extra_rdoc_files = 'README.md'
  s.extensions = [ 'ext/extconf.rb' ]
  s.test_files = Dir.glob('test/test_*.rb')
end

