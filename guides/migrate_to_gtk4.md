# Migrating uGet to GTK4

This guide outlines the steps needed to migrate uGet from GTK3 to GTK4.

## Overview

GTK4 is a major version upgrade from GTK3 with significant API changes and improvements. This migration will require substantial code changes throughout the UI layer.

## Prerequisites

- GTK4 development libraries
- Understanding of GTK3 to GTK4 migration differences
- Time for testing and debugging

## Step 1: Update Dependencies

### Update `meson.build`

Change the GTK dependency from GTK3 to GTK4:

```meson
# Old
gtk_dep = dependency('gtk+-3.0', version : '>= 3.4')

# New
gtk_dep = dependency('gtk4', version : '>= 4.0')
```

### Update AppIndicator (if used)

GTK4 requires a different appindicator library:

```meson
# Old
appindicator_dep = dependency('appindicator3-0.1', required : get_option('appindicator'))

# New
appindicator_dep = dependency('ayatana-appindicator3-0.1', required : get_option('appindicator'))
```

## Step 2: Major API Changes to Address

### 2.1 Widget Hierarchy Changes

GTK4 removed `GtkBox` packing functions. Update all instances:

```c
// Old GTK3
gtk_box_pack_start(GTK_BOX(box), widget, TRUE, TRUE, 0);

// New GTK4
gtk_box_append(GTK_BOX(box), widget);
gtk_widget_set_hexpand(widget, TRUE);
gtk_widget_set_vexpand(widget, TRUE);
```

### 2.2 GtkDialog Changes

`gtk_dialog_run()` was removed. Use async patterns:

```c
// Old GTK3
result = gtk_dialog_run(GTK_DIALOG(dialog));

// New GTK4
g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), data);
gtk_window_present(GTK_WINDOW(dialog));
```

### 2.3 Stock Items Removed

Replace all `GTK_STOCK_*` constants with icon names or labels:

```c
// Old GTK3
gtk_button_new_from_stock(GTK_STOCK_OK);

// New GTK4
gtk_button_new_with_label("OK");
// or
gtk_button_new_from_icon_name("dialog-ok");
```

### 2.4 GtkWidget Show/Hide

Replace `gtk_widget_show_all()`:

```c
// Old GTK3
gtk_widget_show_all(window);

// New GTK4
gtk_widget_show(window);  // Shows widget and children by default
```

### 2.5 Event Handling

GTK4 uses `GtkEventController` instead of signal-based events:

```c
// Old GTK3
g_signal_connect(widget, "button-press-event", G_CALLBACK(on_button_press), NULL);

// New GTK4
GtkGesture *gesture = gtk_gesture_click_new();
g_signal_connect(gesture, "pressed", G_CALLBACK(on_button_pressed), NULL);
gtk_widget_add_controller(widget, GTK_EVENT_CONTROLLER(gesture));
```

### 2.6 GdkWindow Removed

Replace `GdkWindow` operations with `GdkSurface`:

```c
// Old GTK3
GdkWindow *window = gtk_widget_get_window(widget);
gdk_cairo_create(window);

// New GTK4
GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(widget));
// Use snapshot API instead of Cairo directly
```

### 2.7 Menu Changes

`GtkMenu` was removed. Use `GtkPopoverMenu` with `GMenu`:

```c
// Old GTK3
GtkWidget *menu = gtk_menu_new();
gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);

// New GTK4
GMenu *menu = g_menu_new();
GtkWidget *popover = gtk_popover_menu_new_from_model(G_MENU_MODEL(menu));
gtk_popover_popup(GTK_POPOVER(popover));
```

### 2.8 GtkImageMenuItem Removed

Replace with custom widgets or `GtkBox` with icon and label:

```c
// Old GTK3
GtkWidget *item = gtk_image_menu_item_new_with_label("Open");

// New GTK4
// Use GtkPopoverMenu with GMenu instead
```

## Step 3: Files to Update

Based on the current codebase, these files will need significant changes:

### UI Layer (`src/ui-gtk/`)
- `UgtkApp.c` - Main application window
- `UgtkMenubar.c` - Menu system (major rewrite needed)
- `UgtkTrayIcon.c` - System tray integration
- `UgtkNodeDialog.c` - Dialog handling
- `UgtkBatchDialog.c` - Batch operations dialog
- `UgtkSettingDialog.c` - Settings dialog
- `UgtkConfirmDialog.c` - Confirmation dialogs
- `UgtkAboutDialog.c` - About dialog
- `UgtkScheduleForm.c` - Schedule form (uses deprecated Cairo functions)
- All form files (`*Form.c`) - Form widgets

## Step 4: Testing Strategy

1. **Compile incrementally**: Fix one file at a time
2. **Test each component**: Verify functionality after each major change
3. **Visual testing**: Check UI appearance and behavior
4. **Functionality testing**: Ensure all features work correctly

## Step 5: Build and Test

After making changes:

```bash
meson setup --reconfigure build
meson compile -C build
./build/src/ui-gtk/uget-gtk
```

## Resources

- [GTK4 Migration Guide](https://docs.gtk.org/gtk4/migrating-3to4.html)
- [GTK4 API Reference](https://docs.gtk.org/gtk4/)
- [GTK4 Widget Gallery](https://docs.gtk.org/gtk4/visual_index.html)

## Estimated Effort

This is a **major migration** that will require:
- Significant code changes across all UI files
- Extensive testing
- Potential redesign of some UI components
- Several weeks to months of development time

## Alternative Approach

Consider maintaining GTK3 support while gradually adding GTK4 support:
1. Create a separate UI layer for GTK4
2. Use build options to choose between GTK3 and GTK4
3. Migrate incrementally over time

## Notes

- GTK4 is more modern but requires substantial code changes
- Some features may need complete rewrites
- Performance and appearance improvements in GTK4 are significant
- Consider user base and distribution support before migrating
