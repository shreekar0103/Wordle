#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include "game.h"

typedef struct {
    GtkWidget *window, *login_button, *login_entry, *password_entry, *login_label, *password_label, *status_label, *box;
    char* username, password;
} LoginUI;

static void create_login_gui(GtkApplication* app, gpointer user_data);
void on_login_clicked(GtkWidget* login_button, gpointer data);

typedef struct 
{
    WordList* word_list;
    GameState* game_state;
    GtkWidget *window, *button, *input_entry, *grid, *box, *status_label ;
    LoginUI* login_ui;
    GtkApplication* app;

} GameUI;

GameUI* create_game_gui(GtkApplication* app, WordList* word_list, GameState* game_state);
static void create_wordle_gui(GtkApplication* app, gpointer data);
void update_grid_ui(GameUI* gui);
static void activate(GtkApplication* app, gpointer user_data);
void on_submit(GtkWidget* button, gpointer data);
#endif