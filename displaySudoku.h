#include<gtk/gtk.h>
#ifndef DISPLAY_H
#define DISPLAY_H 3

typedef	struct {GtkWidget *dialog;
				GtkWidget *button;
	}data;

int **globalTemplate;
GtkWidget ***buttonTable;
int dimension;
int cellSize;
int seed;
int tournamentSize;
int popSize;
float pc;
int stoppingGen;


void getSudokuFromVisual(int ***template);
void changeDisplay(GtkWidget *numButton,data *aPack);
void generation(GtkWindow *window);
void displaySolution(GtkWindow *parent,int **Solution,int dimension);
void makeGlobalTemplate(int dimension);

void enterItem(GtkWidget *button,GtkWindow *parent);
void destroy(GtkWidget* window,GdkEvent *event,gpointer data);
gboolean delete_event(GtkWidget* window,GdkEvent *event,gpointer data);
void seedSpinChng(GtkSpinButton *widget);
void tournamentChng(GtkSpinButton *widget);
void pcSpinChng(GtkSpinButton *widget);
void populationChng(GtkHScale *widget);
void stoppingChng(GtkHScale *widget);
void displaySorry(GtkWindow *parent);
#endif
