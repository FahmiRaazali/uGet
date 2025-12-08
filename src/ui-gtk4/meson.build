gnome = import('gnome')

# Compile resources into a C source file
uget_gtk4_resources = gnome.compile_resources('uget_gtk4_resources',
  'resources.xml')

# Add the generated resource file to the list of sources
sources = [
  'main.c',
  uget_gtk4_resources,
]

# GTK4 dependency
gtk4_dep = dependency('gtk4')

uget_gtk4 = executable(
  'uget-gtk4',
  sources,
  dependencies: [gtk4_dep],
  install: true,
)
