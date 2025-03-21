project('zroc', 'c')

cc = meson.get_compiler('c')

src_files = ['src/zroc.c']

include_files = ['include/zroc.h']

install_headers(include_files, subdir: 'zro_gen')

libzroc = shared_library(
  'zroc',
  src_files,
  version: '1.0.0',
  soversion: '1',
  install: true,
  c_args: ['-std=c99', '-Wall'],
)

pkgconfig = import('pkgconfig')

pkgconfig.generate(
  name: 'zroc',
  filebase: 'zroc',
  version: '1.0.0',
  libraries: libzroc,
  install_dir: '/usr/lib/pkgconfig/',
  description: 'A library of useful C types and functions.',
  subdirs: ['zroc'],
)
