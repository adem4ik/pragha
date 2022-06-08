/*************************************************************************/
/* Copyright (C) 2009-2018 matias <mati86dl@gmail.com>                   */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#include "pragha-simple-widgets.h"

#if defined(GETTEXT_PACKAGE)
#include <glib/gi18n-lib.h>
#else
#include <glib/gi18n.h>
#endif

/*
 * PraghaHeader:
 */
#define PRAGHA_TYPE_HEADER (pragha_header_get_type())
#define PRAGHA_HEADER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_HEADER, PraghaHeader))
#define PRAGHA_HEADER_CONST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_HEADER, PraghaHeader const))
#define PRAGHA_HEADER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PRAGHA_TYPE_HEADER, PraghaHeaderClass))
#define PRAGHA_IS_HEADER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRAGHA_TYPE_HEADER))
#define PRAGHA_IS_HEADER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PRAGHA_TYPE_HEADER))
#define PRAGHA_HEADER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PRAGHA_TYPE_HEADER, PraghaHeaderClass))

typedef struct _PraghaHeaderClass PraghaHeaderClass;

struct _PraghaHeaderClass {
	GtkBoxClass parent_class;
};
struct _PraghaHeader {
	GtkBox    _parent;

	GtkWidget *image;

	GtkWidget *vbox;
	GtkWidget *title;
	GtkWidget *subtitle;
};
G_DEFINE_TYPE(PraghaHeader, pragha_header, GTK_TYPE_BOX)

void
pragha_header_set_icon_name (PraghaHeader *header,
                             const gchar  *icon_name)
{
	GdkPixbuf *icon;
	gint width = 1, height = 1;

	gtk_icon_size_lookup (GTK_ICON_SIZE_DIALOG, &width, &height);
	icon = gtk_icon_theme_load_icon (gtk_icon_theme_get_default (),
	                                 icon_name ? icon_name : "dialog-information",
	                                 width,
	                                 GTK_ICON_LOOKUP_FORCE_SIZE, NULL);
	gtk_image_set_from_pixbuf (GTK_IMAGE(header->image), icon);
	g_object_unref (icon);
}

void
pragha_header_set_title (PraghaHeader *header,
                         const gchar  *title)
{
	gchar *markup = NULL;
	markup = g_markup_printf_escaped("<span size='large' weight='bold'>%s</span>", title);
	gtk_label_set_markup(GTK_LABEL(header->title), markup);
	g_free(markup);
}

void
pragha_header_set_subtitle (PraghaHeader *header,
                            const gchar  *subtitle)
{
	GtkWidget *subtitlew = NULL;
	gchar *markup = NULL;

	if (!header->subtitle) {
		subtitlew = gtk_label_new (NULL);
		gtk_label_set_line_wrap (GTK_LABEL(subtitlew), TRUE);
		gtk_widget_set_halign (subtitlew, GTK_ALIGN_START);
		g_object_set (subtitlew, "xalign", 0.0, NULL);
		gtk_box_pack_start(GTK_BOX(header->vbox), subtitlew, FALSE, FALSE, 0);
		gtk_widget_show (GTK_WIDGET(subtitlew));
		header->subtitle = subtitlew;
	}

	markup = g_markup_printf_escaped ("<span size='large'>%s</span>", subtitle);
	gtk_label_set_markup (GTK_LABEL(header->subtitle), markup);
	g_free(markup);
}

static void
pragha_header_class_init (PraghaHeaderClass *class)
{
}

static void
pragha_header_init (PraghaHeader *header)
{
	GtkWidget *hbox, *vbox;
	GtkWidget *title;
	GtkWidget *separator;

	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
	gtk_container_set_border_width(GTK_CONTAINER(hbox), 6);

	header->image = gtk_image_new ();

	title = gtk_label_new (NULL);
	gtk_label_set_line_wrap(GTK_LABEL(title), TRUE);
	gtk_widget_set_halign (title, GTK_ALIGN_START);
	g_object_set (title, "xalign", 0.0, NULL);
	header->title = title;

	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_valign (vbox, GTK_ALIGN_CENTER);
	header->vbox = vbox;

	gtk_box_pack_start(GTK_BOX(vbox), title, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(hbox), header->image, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

	separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);

	gtk_orientable_set_orientation (GTK_ORIENTABLE (header), GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start (GTK_BOX(header), hbox, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(header), separator, FALSE, FALSE, 0);

	gtk_style_context_add_class (gtk_widget_get_style_context (GTK_WIDGET(header)),
	                             "view");
	gtk_style_context_add_class (gtk_widget_get_style_context (GTK_WIDGET(header)),
	                             "XfceHeading");
}

PraghaHeader *
pragha_header_new (void)
{
	return g_object_new (PRAGHA_TYPE_HEADER, NULL);
}

/*
 * PraghaToolbarButton
 */
#define PRAGHA_TYPE_TOOLBAR_BUTTON (pragha_toolbar_button_get_type())
#define PRAGHA_TOOLBAR_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_TOOLBAR_BUTTON, PraghaToolbarButton))
#define PRAGHA_TOOLBAR_BUTTON_CONST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_TOOLBAR_BUTTON, PraghaToolbarButton const))
#define PRAGHA_TOOLBAR_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PRAGHA_TYPE_TOOLBAR_BUTTON, PraghaToolbarButtonClass))
#define PRAGHA_IS_TOOLBAR_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRAGHA_TYPE_TOOLBAR_BUTTON))
#define PRAGHA_IS_TOOLBAR_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PRAGHA_TYPE_TOOLBAR_BUTTON))
#define PRAGHA_TOOLBAR_BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PRAGHA_TYPE_TOOLBAR_BUTTON, PraghaToolbarButtonClass))

typedef struct _PraghaToolbarButtonClass PraghaToolbarButtonClass;

struct _PraghaToolbarButtonClass {
	GtkButtonClass parent_class;
};

struct _PraghaToolbarButton {
	GtkButton   __parent;

	gchar       *icon_name;
	GtkIconSize  icon_size;
};

enum
{
	PROP_0,
	PROP_ICON_NAME,
	PROP_ICON_SIZE
};

G_DEFINE_TYPE(PraghaToolbarButton, pragha_toolbar_button, GTK_TYPE_BUTTON)

static void
pragha_toolbar_button_update_icon (PraghaToolbarButton *button)
{
	gtk_button_set_image (GTK_BUTTON(button),
		gtk_image_new_from_icon_name (button->icon_name,
		                              button->icon_size));
}

void
pragha_toolbar_button_set_icon_name (PraghaToolbarButton *button, const gchar *icon_name)
{
	if (g_strcmp0(button->icon_name, icon_name)) {
		if (button->icon_name)
			g_free (button->icon_name);
		button->icon_name = g_strdup (icon_name);

		pragha_toolbar_button_update_icon (button);
	}
}

void
pragha_toolbar_button_set_icon_size (PraghaToolbarButton *button, GtkIconSize icon_size)
{
	if (button->icon_size != icon_size) {
		button->icon_size = icon_size;
		pragha_toolbar_button_update_icon (button);
	}
}

static void
pragha_toolbar_button_set_property (GObject       *object,
                                    guint          prop_id,
                                    const GValue  *value,
                                    GParamSpec    *pspec)
{
	PraghaToolbarButton *button = PRAGHA_TOOLBAR_BUTTON (object);

	switch (prop_id)
	{
		case PROP_ICON_NAME:
			pragha_toolbar_button_set_icon_name (button, g_value_get_string (value));
			break;
		case PROP_ICON_SIZE:
			pragha_toolbar_button_set_icon_size (button, g_value_get_enum (value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
pragha_toolbar_button_get_property (GObject     *object,
                                    guint        prop_id,
                                    GValue      *value,
                                    GParamSpec  *pspec)
{
	PraghaToolbarButton *button = PRAGHA_TOOLBAR_BUTTON (object);
	switch (prop_id)
	{
		case PROP_ICON_NAME:
			g_value_set_string (value, button->icon_name);
			break;
		case PROP_ICON_SIZE:
			g_value_set_enum (value, button->icon_size);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
pragha_toolbar_button_finalize (GObject *object)
{
	PraghaToolbarButton *button = PRAGHA_TOOLBAR_BUTTON (object);
	if (button->icon_name) {
		g_free (button->icon_name);
		button->icon_name = NULL;
	}
	(*G_OBJECT_CLASS (pragha_toolbar_button_parent_class)->finalize) (object);
}

static void
pragha_toolbar_button_class_init (PraghaToolbarButtonClass *class)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  	gobject_class->set_property = pragha_toolbar_button_set_property;
	gobject_class->get_property = pragha_toolbar_button_get_property;
	gobject_class->finalize = pragha_toolbar_button_finalize;

	g_object_class_install_property (gobject_class, PROP_ICON_NAME,
	                                 g_param_spec_string ("icon-name",
	                                                      "Icon Name",
	                                                      "The name of the icon from the icon theme",
	                                                      NULL,
	                                                      G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (gobject_class, PROP_ICON_SIZE,
	                                 g_param_spec_enum ("icon-size",
	                                                    "Icon size",
	                                                     "The icon size",
	                                                     GTK_TYPE_ICON_SIZE,
	                                                     GTK_ICON_SIZE_SMALL_TOOLBAR,
	                                                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
}

static void
pragha_toolbar_button_init (PraghaToolbarButton *widget)
{
	gtk_button_set_relief (GTK_BUTTON(widget), GTK_RELIEF_NONE);
	gtk_widget_show_all (GTK_WIDGET(widget));
}

PraghaToolbarButton *
pragha_toolbar_button_new (const gchar *icon_name)
{
	PraghaToolbarButton *button;
	GtkWidget *image;

	image = gtk_image_new_from_icon_name (icon_name, GTK_ICON_SIZE_LARGE_TOOLBAR);
	button =  g_object_new (PRAGHA_TYPE_TOOLBAR_BUTTON,
	                        "image", image,
	                        "icon-name", icon_name,
	                        "icon-size", GTK_ICON_SIZE_LARGE_TOOLBAR,
	                        "valign", GTK_ALIGN_CENTER,
	                        NULL);

	return button;
}

/*
 * PraghaTogleButton
 */
#define PRAGHA_TYPE_TOGGLE_BUTTON (pragha_toggle_button_get_type())
#define PRAGHA_TOGGLE_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_TOGGLE_BUTTON, PraghaToggleButton))
#define PRAGHA_TOGGLE_BUTTON_CONST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRAGHA_TYPE_TOGGLE_BUTTON, PraghaToggleButton const))
#define PRAGHA_TOGGLE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), PRAGHA_TYPE_TOGGLE_BUTTON, PraghaToggleButtonClass))
#define PRAGHA_IS_TOGGLE_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRAGHA_TYPE_TOGGLE_BUTTON))
#define PRAGHA_IS_TOGGLE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PRAGHA_TYPE_TOGGLE_BUTTON))
#define PRAGHA_TOGGLE_BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), PRAGHA_TYPE_TOGGLE_BUTTON, PraghaToggleButtonClass))

typedef struct _PraghaToggleButtonClass PraghaToggleButtonClass;

struct _PraghaToggleButtonClass {
	GtkToggleButtonClass parent_class;
};

struct _PraghaToggleButton {
	GtkToggleButton   __parent;

	gchar       *icon_name;
	GtkIconSize  icon_size;
};

G_DEFINE_TYPE(PraghaToggleButton, pragha_toggle_button, GTK_TYPE_TOGGLE_BUTTON)

static void
pragha_toggle_button_update_icon (PraghaToggleButton *button)
{
	gtk_button_set_image (GTK_BUTTON(button),
		gtk_image_new_from_icon_name (button->icon_name,
		                              button->icon_size));
}

void
pragha_toggle_button_set_icon_name (PraghaToggleButton *button, const gchar *icon_name)
{
	if (g_strcmp0(button->icon_name, icon_name)) {
		if (button->icon_name)
			g_free (button->icon_name);
		button->icon_name = g_strdup (icon_name);

		pragha_toggle_button_update_icon (button);
	}
}

void
pragha_toggle_button_set_icon_size (PraghaToggleButton *button, GtkIconSize icon_size)
{
	if (button->icon_size != icon_size) {
		button->icon_size = icon_size;
		pragha_toggle_button_update_icon (button);
	}
}

static void
pragha_toggle_button_set_property (GObject       *object,
                                   guint          prop_id,
                                   const GValue  *value,
                                   GParamSpec    *pspec)
{
	PraghaToggleButton *button = PRAGHA_TOGGLE_BUTTON (object);

	switch (prop_id)
	{
		case PROP_ICON_NAME:
			pragha_toggle_button_set_icon_name (button, g_value_get_string (value));
			break;
		case PROP_ICON_SIZE:
			pragha_toggle_button_set_icon_size (button, g_value_get_enum (value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
pragha_toggle_button_get_property (GObject     *object,
                                   guint        prop_id,
                                   GValue      *value,
                                   GParamSpec  *pspec)
{
	PraghaToggleButton *button = PRAGHA_TOGGLE_BUTTON (object);
	switch (prop_id)
	{
		case PROP_ICON_NAME:
			g_value_set_string (value, button->icon_name);
			break;
		case PROP_ICON_SIZE:
			g_value_set_enum (value, button->icon_size);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
pragha_toggle_button_finalize (GObject *object)
{
	PraghaToggleButton *button = PRAGHA_TOGGLE_BUTTON (object);
	if (button->icon_name) {
		g_free (button->icon_name);
		button->icon_name = NULL;
	}
	(*G_OBJECT_CLASS (pragha_toggle_button_parent_class)->finalize) (object);
}

static void
pragha_toggle_button_class_init (PraghaToggleButtonClass *class)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  	gobject_class->set_property = pragha_toggle_button_set_property;
	gobject_class->get_property = pragha_toggle_button_get_property;
	gobject_class->finalize = pragha_toggle_button_finalize;

	g_object_class_install_property (gobject_class, PROP_ICON_NAME,
	                                 g_param_spec_string ("icon-name",
	                                                      "Icon Name",
	                                                      "The name of the icon from the icon theme",
	                                                      NULL,
	                                                      G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (gobject_class, PROP_ICON_SIZE,
	                                 g_param_spec_enum ("icon-size",
	                                                    "Icon size",
	                                                     "The icon size",
	                                                     GTK_TYPE_ICON_SIZE,
	                                                     GTK_ICON_SIZE_SMALL_TOOLBAR,
	                                                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
}

static void
pragha_toggle_button_init (PraghaToggleButton *widget)
{
	gtk_button_set_relief (GTK_BUTTON(widget), GTK_RELIEF_NONE);
	gtk_widget_show_all (GTK_WIDGET(widget));
}

PraghaToggleButton *
pragha_toggle_button_new (const gchar *icon_name)
{
	PraghaToggleButton *button;
	GtkWidget *image;

	image = gtk_image_new_from_icon_name (icon_name, GTK_ICON_SIZE_LARGE_TOOLBAR);
	button =  g_object_new (PRAGHA_TYPE_TOGGLE_BUTTON,
	                        "image", image,
	                        "icon-name", icon_name,
	                        "icon-size", GTK_ICON_SIZE_LARGE_TOOLBAR,
	                        "valign", GTK_ALIGN_CENTER,
	                        NULL);

	return button;
}
