#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include "game.h"

typedef struct 
{
    WordList* word_list;
    GameState* game_state;
    GtkWidget *window, *button, *input_entry, *grid, *box, *status_label ;

} GameUI;

GameUI* create_game_gui(GtkApplication* app, WordList* word_list, GameState* game_state);
void update_grid_ui(GameUI* gui);
static void activate(GtkApplication* app, gpointer user_data);
void on_submit(GtkWidget* button, gpointer data);
#endif