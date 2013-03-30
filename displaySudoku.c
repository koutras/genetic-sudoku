#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"displaySudoku.h"
#include"sudoku.h"




void getSudokuFromVisual(int ***template)
{
	*template=globalTemplate;
}



 gboolean delete_event(GtkWidget*window,GdkEvent *event,gpointer data)
{
	printf("delete_event called\n");

	return FALSE;

}

 void destroy(GtkWidget* window,GdkEvent *event,gpointer data)
{
	printf("destroy called\n");

	gtk_main_quit();
}

 void changeDisplay(GtkWidget *numButton,data *aPack)
{
	int i,j;
	gchar str[40];

	strcpy(str,gtk_button_get_label(GTK_BUTTON(numButton)));

	gtk_button_set_label(GTK_BUTTON(aPack->button),str);


	for(i=0;i<dimension;i++)
		for(j=0;j<dimension;j++)
			if(buttonTable[i][j]==(aPack->button))
				globalTemplate[i][j]=atoi(str);



	gtk_widget_destroy(aPack->dialog);
	

}

void clear(GtkWidget *button,data *aPack)
{
	int i,j;
	char str[3];
	strcpy(str,"");
	gtk_button_set_label(GTK_BUTTON(aPack->button),"");

	for(i=0;i<dimension;i++)
		for(j=0;j<dimension;j++)
			if(buttonTable[i][j]==(aPack->button))
				globalTemplate[i][j]=0;



	gtk_widget_destroy(aPack->dialog);
	
}

void generation(GtkWindow *window)
{
	printf("in generation window=%X\n",(unsigned int)window);

	sudokuGame(window,seed,dimension,tournamentSize,popSize,pc,stoppingGen);


	
}	

void seedSpinChng(GtkSpinButton *widget)
{
	seed=gtk_spin_button_get_value_as_int(widget);
}

void tournamentChng(GtkSpinButton *widget)
{
	tournamentSize=gtk_spin_button_get_value_as_int(widget);
}

void pcSpinChng(GtkSpinButton *widget)
{
	pc=gtk_spin_button_get_value_as_float(widget);
}

void populationChng(GtkHScale *widget)
{
	popSize=gtk_range_get_value(GTK_RANGE(widget));

}

void stoppingChng(GtkHScale *widget)
{
	stoppingGen=gtk_range_get_value(GTK_RANGE(widget));
}

void displaySorry(GtkWindow *parent)
{
	GtkWidget *dialog,*label,*image,*hbox;

	printf("dialogs sorry parent %X\n",(unsigned int)parent);

	dialog=gtk_dialog_new_with_buttons("CANT FIND SOLUTION",parent,
			GTK_DIALOG_MODAL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,
			NULL);

	label=gtk_label_new("YOU 'VE BEEN UNLUCKY TODAY");

	image=gtk_image_new_from_stock(GTK_STOCK_DIALOG_INFO,
			GTK_ICON_SIZE_DIALOG);
	hbox=gtk_hbox_new(FALSE,5);
	gtk_container_set_border_width(GTK_CONTAINER(hbox),10);


	gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),image);
	gtk_box_pack_start_defaults(GTK_BOX(hbox),label);

	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox);
	gtk_widget_show_all(dialog);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
	



	
void displaySolution(GtkWindow *parent,int **Solution,int dimension)
{
	GtkWidget *label;
	GtkWidget *dialog;
	GtkWidget *table;
	GtkWidget *box;
	int i,j;
	gchar str[40];
	GtkWidget *image;

	table=gtk_table_new(dimension,dimension,TRUE);
	dialog=gtk_dialog_new_with_buttons("I HAVE JUST FOUND THE SOLUTION!!!",parent,
			GTK_DIALOG_MODAL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);

	gtk_dialog_set_has_separator(GTK_DIALOG(dialog),FALSE);
	

	image=gtk_image_new_from_file("funny.gif");

	for(i=0;i<dimension;i++)
		for(j=0;j<dimension;j++){

			sprintf(str,"%d",Solution[i][j]);
			label=gtk_label_new(str);


			
			gtk_table_attach(GTK_TABLE(table),label,j,j+1,i,i+1,
					GTK_EXPAND,GTK_SHRINK,0,0);
	}


	gtk_widget_set_size_request(table,180,-1);
	
	box=gtk_hbox_new(TRUE,0);
	gtk_box_pack_start_defaults(GTK_BOX(box),image);
	gtk_box_pack_start_defaults(GTK_BOX(box),table);

	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),box);

	gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


	




 void enterItem(GtkWidget *button,GtkWindow *parent)
{
	
	printf("enterItem called\n");	
	gint i,j;
	gchar str[40];
	int counter=1;

	
	GtkWidget *table,*numButton;
	GtkWidget *dialog;
	GtkWidget *box;
	GtkWidget *clearButton;

	data aPack;

	

	printf("in enter item button=%X,parent=%X\n",(unsigned int)button,(unsigned int)parent);
	
	table=gtk_table_new(cellSize,cellSize,TRUE);
	dialog=gtk_dialog_new_with_buttons("SELECT",parent,
			GTK_DIALOG_MODAL,NULL);

	aPack.dialog=dialog;
	aPack.button=button;
	clearButton=gtk_button_new_with_mnemonic("_clear");


	for(i=0;i<cellSize;i++)
		for(j=0;j<cellSize;j++,counter++){
			

			sprintf(str,"%d",counter);
			numButton=gtk_button_new_with_label(str);


			g_signal_connect(G_OBJECT(numButton),"clicked",G_CALLBACK(changeDisplay),(gpointer)&aPack);

			gtk_table_attach_defaults(GTK_TABLE(table),numButton,j,j+1,i,i+1
);
		}

	box=gtk_hbox_new(TRUE,0);
	

	gtk_box_pack_start_defaults(GTK_BOX(box),table);

	gtk_window_set_decorated(GTK_WINDOW(dialog),FALSE);


	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox),box);
	gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->action_area),clearButton);

	
	g_signal_connect(G_OBJECT(clearButton),"clicked",G_CALLBACK(clear),
			(gpointer)&aPack);
	


	

	gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));


 	

	
}



void makeGlobalTemplate(int dimension)
{
	int k,j;
		globalTemplate=(int**)malloc(sizeof(int*)*dimension);

			puts("i grammi auti prepei na ektypwthei mono mia fora ");



			for(k=0;k<dimension;k++){
				globalTemplate[k]=(int *)malloc(sizeof(int)*dimension);
				check(globalTemplate[k]);

				for(j=0;j<dimension;j++)
					globalTemplate[k][j]=0;  //thewrw to 0 mi egyri timi sudoku	
				
			}
}





	







	
	
