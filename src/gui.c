#include "../include/gui.h"
#include <ctype.h>
#include <stdio.h>
GdkRGBA color_incorrect = {0.5, 0.5, 0.5, 1.0}; // Gray
GdkRGBA color_present = {0.9, 0.9, 0.0, 1.0};   // Yellow
GdkRGBA color_correct = {0.0, 0.8, 0.0, 1.0};  // Green
GdkRGBA color_no_entry = {1.0, 1.0, 1.0, 1.0};

int default_color[3]  = {250, 249, 209};
int custom_color[3] = {249, 215, 119};
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
    gtk_entry_set_visibility(GTK_ENTRY(gui->password_entry), FALSE);

    gtk_widget_show_all(gui->window);
}

void formatString(char *buffer, const char *format, ...) {
   va_list args;
   va_start(args, format);
   vsprintf(buffer, format, args);
   va_end(args);
}

void convert_to_local_time(time_t t, char *buff){
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
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

    char details[50], local_date[20] ;
    convert_to_local_time(gui->login_ui->last_login, local_date);
    formatString(details, "Welcome %s\nstreak : %d \t LL : %s",gui->login_ui->username, gui->login_ui->streak, local_date);
    gui->details_label = gtk_label_new(details);
    status_label_style(gui->details_label, custom_color);

    gtk_box_pack_start(GTK_BOX (gui->box), gui->details_label, 0, 0, 0);

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

long int conversion_to_int (char *token){
    long int num = 0;
    int n = strlen(token);
    for(int i = 0; i<n-1 ; i++){
        num = num * 10 + (token[i] - '0');
    }
    return num;
}


bool validate_user(GameUI* game_gui) {
    // open file user_data in read mode 
    FILE *file_csv ;
    char file_username[MAX_USERNAME_LEN]; 
    char file_password[MAX_USERPASS_LEN];
    int  file_streak;
    int  file_id;
    time_t file_last_login;
    file_csv = fopen ("D:/shreekar files/cProgramming/wordle_project_1/user_data.csv", "r");
    char line[200];
    bool is_header = true;
    while (fgets(line, sizeof(line), file_csv)){
        if (is_header){
            is_header = false;  //next lines are not headers 
            continue;
        }
        char *token ;
        token = strtok(line, ",");
        if(token!=NULL){
            file_id = conversion_to_int(token);
            token = strtok(NULL, ",");
        }
        if(token!=NULL){
            strcpy(file_username,token);
            token = strtok(NULL, ",");
        }
        if(token!=NULL){
            strcpy(file_password,token);
            token = strtok(NULL, ",");
        }
        if(token!=NULL){
            file_streak = conversion_to_int(token);
            token = strtok(NULL, ",");
        }
        if(token!=NULL){
            file_last_login = (time_t) conversion_to_int (token);
            token = strtok(NULL, ",");
        }
        
    const gchar* username = gtk_entry_get_text(GTK_ENTRY(game_gui->login_ui->login_entry));
    const gchar* password = gtk_entry_get_text(GTK_ENTRY(game_gui->login_ui->password_entry));
    printf("%s %s %d %ld\n",file_username,file_password, file_streak, file_last_login);
    
    if(strcmp(username , file_username) == 0 && strcmp(password,file_password) == 0){
        game_gui->login_ui->streak = file_streak;
        game_gui->login_ui->last_login = file_last_login;
        strcpy(game_gui->login_ui->username,file_username);
        return true;
    }
    }
    return false;
    
    // read line by line and extract user name and password streak and last login into separate variables 

    // check if username and password mathches 

    // if matches copy the data into loginui user data and return true 

    // else return false 
}


void on_login_clicked(GtkWidget* login_button, gpointer data) {
    GameUI* game_gui = (GameUI*) data;
    // search for username and paassword in user_data 

    if (validate_user(game_gui)) { 
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
            // update streak and last login of user 
            time_t current_time = time(NULL);
            char local_date[50];
            long int differences_time = difftime(current_time,gui->login_ui->last_login);
            if(differences_time>86400){
                gui->login_ui->streak = 1;
                printf("%d\n",gui->login_ui->streak);
                convert_to_local_time(gui->login_ui->last_login, local_date);
                printf("%s\n",local_date);
            }else{
                gui->login_ui->streak ++ ;
                printf("%d",gui->login_ui->streak);
            }
        gui->login_ui->last_login = time(NULL);

    char details[50];
    convert_to_local_time(gui->login_ui->last_login, local_date);
    formatString(details, "Welcome %s\nstreak : %d \t LL : %s",gui->login_ui->username, gui->login_ui->streak, local_date);
    gtk_label_set_text(GTK_LABEL(gui->details_label), details);

            // if user last login is more than a day before update streak to 1.

            // else increase current streak and last login to current time 
            
            // open the user data file in write modde and search user with user id and update streak and last login.

            // search for id and apply changes.
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
    gui->login_ui = (LoginUI*) malloc(sizeof(LoginUI));

    return gui;
    
}