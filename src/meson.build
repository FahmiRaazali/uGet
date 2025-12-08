subdir('uglib')
subdir('uget')

# Build UI based on gtk_version option
gtk_version = get_option('gtk_version')

if gtk_version == '3' or gtk_version == 'both'
  subdir('ui-gtk')
endif

if gtk_version == '4' or gtk_version == 'both'
  subdir('ui-gtk4')
endif
