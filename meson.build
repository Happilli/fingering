project(
  'fingering',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)
raylib_dep = dependency('raylib')

dependencies = [
  raylib_dep,
]

sources = [
  'fingering.c',
]

exe = executable(
  'fingering',
  sources,
  dependencies : dependencies,
  install : true,
)

test('basic', exe)
