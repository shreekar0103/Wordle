#include "../include/gui.h"
#include <ctype.h>
GdkRGBA color_incorrect = {0.5, 0.5, 0.5, 1.0}; // Gray
GdkRGBA color_present = {0.9, 0.9, 0.0, 1.0};   // Yellow
GdkRGBA color_correct = {0.0, 0.8, 0.0, 1.0};  // Green
GdkRGBA color_no_entry = {1.0, 1.0, 1.0, 1.0};

int default_color[3]  = {250, 249, 209};
int successs_color[3]  = {164, 255, 119};

void status_label_style(GtkWidget* label, int rgb[]) {
     GtkStyleContext *context = 
    gtk_widget_get_style_context(label);
    gtk_style_context_add_class(context, "letter-tile");
            
    // Apply color
    GtkCssProvider *provider = gtk_css_provider_new();
    gchar *css = g_strdup_printf(
        ".letter-tile { "
        "background-color: rgb(%d, %d, %d); "
        "padding: 5px;"
        "font-weight: bold; "
        "}", 
        rgb[0], rgb[1], rgb[2]
    );
    
    GError *error = NULL;
    gtk_css_provider_load_from_data(provider, css, -1, &error);
    if (error) {
        g_print("CSS Error: %s\n", error->message);
        g_error_free(error);
    }
    
    gtk_style_context_add_provider(
        context, 
        GTK_STYLE_PROVIDER(provider), 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    
    g_object_unref(provider);
    g_free(css);
}

static void create_login_gui(GtkApplication* app, gpointer user_data) {

    
    GameUI* game_gui = (GameUI*) user_data;
    game_gui->login_ui = (LoginUI*)malloc(sizeof(LoginUI));
    LoginUI* gui = game_gui->login_ui;
    
    gui->window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (gui->window), "Login Wordle");
    gtk_window_set_default_size (GTK_WINDOW (gui->window), 200, 200);
    gtk_window_present (GTK_WINDOW (gui->window));
    
    gui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER(gui->window), gui->box);


    gui->login_button = gtk_button_new_with_label("Login");
    gtk_box_pack_end(GTK_BOX (gui->box), gui->login_button, 0, 0, 0);
    
    g_signal_connect(gui->login_button, "clicked", G_CALLBACK(on_login_clicked), game_gui);

    gui->login_label = gtk_label_new("LOGIN ID");
    gtk_box_pack_start(GTK_BOX(gui->box), gui->login_label, 0, 0, 0);

    gui->login_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(gui->login_entry), 3);
    gtk_box_pack_start(GTK_BOX (gui->box), gui->login_entry, 0, 0, 0); 

    gui->password_label = gtk_label_new("PASSWORD");
    gtk_box_pack_start(GTK_BOX(gui->box), gui->password_label, 0, 0, 0);

    gui->password_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(gui->password_entry), 3);
    gtk_box_pack_start(GTK_BOX (gui->box), gui->password_entry, 0, 0, 0);     

    gtk_widget_show_all(gui->window);
}

static void create_wordle_window(GtkApplication* app, gpointer data) {
    GameUI* gui = (GameUI*) data;
    //gtk_window_set_application(GTK_WINDOW(gui->window), app);
    gui->window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (gui->window), "W-O-R-D-L-E");
    gtk_window_set_default_size (GTK_WINDOW (gui->window), 200, 200);
    gtk_window_present (GTK_WINDOW (gui->window));
    gui->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_container_add (GTK_CONTAINER(gui->window), gui->box);

    gui->status_label = gtk_label_new("Guess The 5 Letter Word");
    const char *str = "Guess The 5 Letter Word";
    const char *format = "<span style=\"italic\">\%s</span>";
    char *markup;

    markup = g_markup_printf_escaped (format, str);
    gtk_label_set_markup(GTK_LABEL(gui->status_label), markup);
    g_free (markup);
    status_label_style(gui->status_label, default_color);
    gtk_box_pack_start(GTK_BOX (gui->box), gui->status_label, 0, 0, 0);

    gui->grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(gui->grid), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(gui->grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(gui->grid), TRUE);
    gtk_box_pack_start(GTK_BOX (gui->box), gui->grid, FALSE, FALSE, 0);



    gui->input_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(gui->input_entry), MAX_WORD_LENGTH);
    gtk_box_pack_start(GTK_BOX (gui->box), gui->input_entry, 0, 0, 0); 

    gui->button = gtk_button_new_with_label("Guess");
    gtk_box_pack_end(GTK_BOX (gui->box), gui->button, 0, 0, 0);

    g_signal_connect(gui->button, "clicked", G_CALLBACK(on_submit), gui);


    update_grid_ui(gui);  


   gtk_widget_show_all(gui->window);
}

void on_login_clicked(GtkWidget* login_button, gpointer data) {
    GameUI* game_gui = (GameUI*) data;
    const gchar* username = gtk_entry_get_text(GTK_ENTRY(game_gui->login_ui->login_entry));

    const gchar* password = gtk_entry_get_text(GTK_ENTRY(game_gui->login_ui->password_entry));

    if (strcmp(username, "abc") == 0 && strcmp(password, "aaa") == 0) {
        gtk_widget_destroy(GTK_WIDGET(game_gui->login_ui->window));
        create_wordle_window(game_gui->app, game_gui);
    } else {
        //dialogue box
        GtkWidget *dialog ;
        GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
        dialog = gtk_dialog_new_with_buttons("Invalid Credentials",GTK_WINDOW(game_gui->login_ui->window),  flags , "_OK",
                                       GTK_RESPONSE_ACCEPT,NULL);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }
}


static void activate(GtkApplication* app, gpointer user_data) {
    create_login_gui(app, user_data);
}

void on_submit(GtkWidget* button, gpointer data) {
    GameUI* gui = (GameUI*) data;

    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(gui->input_entry));

    int curr_attempt = gui->game_state->current_attempt; 
    Word entry_word;
    strcpy(entry_word.letter, input_text);

    if (make_guess(gui->game_state, &entry_word)) {
        gui->game_state->current_attempt++;
        update_grid_ui(gui);
        if (gui->game_state->game_over) {

            if (gui->game_state->game_win) {
                // Updated Game Won
                gtk_label_set_text(GTK_LABEL(gui->status_label), "CONGRATULATIONS YOU WON !!!!");
                status_label_style(gui->status_label, successs_color);
            }  else {
                // max attempts over target string is : 
                char buf[100];
                snprintf(buf, 100, "You Have Reached Max attempts!!\n The Correct Word is: %s\n", gui->game_state->target_word);
                gtk_label_set_text(GTK_LABEL(gui->status_label), buf);

            }
        }
        


    }

}

void update_grid_ui(GameUI* gui) {

    gtk_container_foreach(GTK_CONTAINER(gui->grid), (GtkCallback) gtk_widget_destroy, NULL);
    for(int attempt=0; attempt < MAX_ATTEMPTS; attempt++){
        for(int l=0; l <MAX_WORD_LENGTH; l++){
            GtkWidget* label = gtk_label_new(" ");
            gtk_grid_attach(GTK_GRID(gui->grid), label, l, attempt, 1 , 1);
            GdkRGBA color = color_no_entry;
            if (attempt < gui->game_state->current_attempt) {
                char letter[2] = { gui->game_state->guesses[attempt].letter[l], '\0' };
                gtk_label_set_text(GTK_LABEL(label), letter);
                switch(gui->game_state->guess_status[attempt][l]) {
                    case INCORRECT:
                        color = color_incorrect;
                        break;
                    case PRESENT:
                        color = color_present;
                        break;
                    case CORRECT:
                        color = color_correct;
                        break;
                    default:
                        color = color_no_entry;
                        break;
                }
            }

            GtkStyleContext *context = 
                gtk_widget_get_style_context(label);
            gtk_style_context_add_class(context, "letter-tile");
            
            // Apply color
            GtkCssProvider *provider = gtk_css_provider_new();
            gchar *css = g_strdup_printf(
                ".letter-tile { "
                "background-color: rgba(%d, %d, %d, %f); "
                "color: white; "
                "min-width: 50px; "
                "min-height: 50px; "
                "font-size: 24px; "
                "font-weight: bold; "
                "border: 1px solid gray; "
                "}", 
                (int)(color.red * 255), 
                (int)(color.green * 255), 
                (int)(color.blue * 255), 
                color.alpha
            );
            
            GError *error = NULL;
            gtk_css_provider_load_from_data(provider, css, -1, &error);
            if (error) {
                g_print("CSS Error: %s\n", error->message);
                g_error_free(error);
            }
            
            gtk_style_context_add_provider(
                context, 
                GTK_STYLE_PROVIDER(provider), 
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
            );
            
            g_object_unref(provider);
            g_free(css);

            
            gtk_widget_show(label);
        }
    }
}


GameUI* create_game_gui(GtkApplication* app, WordList* word_list, GameState* game_state) {
    GameUI *gui;
    gui = (GameUI *) malloc(sizeof(GameUI));
    gui->word_list = word_list;
    gui->game_state = game_state;
    gui->app = app;

    return gui;
    
}