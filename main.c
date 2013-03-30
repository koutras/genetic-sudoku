#include<gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

#include"sudoku.h"
#include"displaySudoku.h"



int main(int argc,char **argv)
{
	gint i,j;
	GtkWidget *window,*hbox,*vbox,*menuHbox,*generateButton,*generationLabel,*hBoxUpMenu,*closeButton,*optionsMenu,
				 *popLabel,*seedLabel,*tourLabel,*pcLabel,*stoppingLabel;

	GtkSpinButton *pcSpin,*seedSpin,*tournament;
	GtkHScale *population,*stopping;
	char str[31];

	GtkAdjustment *seedAdj,*tournamentAdj,*pcAdj,*popAdj,*stoppingAdj;


	gtk_init(&argc,&argv);
	
	seedAdj=GTK_ADJUSTMENT(gtk_adjustment_new(3,1,10000,1,1,1));
	tournamentAdj=GTK_ADJUSTMENT(gtk_adjustment_new(3,1,30,1,1,1));
	pcAdj=GTK_ADJUSTMENT(gtk_adjustment_new(0.3,0.1,1.0,0.1,0.1,0.1));
	popAdj=GTK_ADJUSTMENT(gtk_adjustment_new(400,1,15000,1,1,1));
	stoppingAdj=GTK_ADJUSTMENT(gtk_adjustment_new(2000,1,15000,1,1,1));

	popLabel=gtk_label_new("POPULATION");
	seedLabel=gtk_label_new("seed");
	tourLabel=gtk_label_new("trnmt");
	pcLabel=gtk_label_new("pc");
	stoppingLabel=gtk_label_new("stop geneneration");
	
	


	

	 if(argc!=1)
		 dimension=atoi(argv[1]);
	 else dimension=9;
	 cellSize=sqrt(dimension);
	 printf("argc==%d\n",argc);


	 makeGlobalTemplate(dimension);

	 printf("dimensnion=%d cellSize=%d\n",(unsigned int)dimension,(unsigned int)cellSize);

	 


		buttonTable=(GtkWidget***)malloc(sizeof(GtkWidget**)*dimension);
		if(buttonTable==NULL){printf("Error\n");exit(-1);}


		for(i=0;i<dimension;i++){
			buttonTable[i]=(GtkWidget**)malloc(sizeof(GtkWidget*)*dimension);
			if(buttonTable[i]==NULL){printf("Error\n");exit(-1);}
		}
			

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"SUDOKU");
	gtk_container_set_border_width(GTK_CONTAINER(window),2);
	gtk_widget_set_size_request(window,380,450);


	closeButton=gtk_button_new_from_stock(GTK_STOCK_CLOSE);
	g_signal_connect(G_OBJECT(closeButton),"clicked",
			G_CALLBACK(destroy),
			NULL);



	hBoxUpMenu=gtk_hbox_new(TRUE,2);



	generationLabel=gtk_label_new("GENERATION:  ");
	
	gtk_box_pack_start_defaults(GTK_BOX(hBoxUpMenu),generationLabel);

	vbox=gtk_vbox_new(FALSE,0);
	
	optionsMenu=gtk_hbox_new(TRUE,1);


	seedSpin=GTK_SPIN_BUTTON(gtk_spin_button_new(seedAdj,1,0));
	tournament=GTK_SPIN_BUTTON(gtk_spin_button_new(tournamentAdj,1,0));
	pcSpin=GTK_SPIN_BUTTON(gtk_spin_button_new(pcAdj,0.1,1));
	population=GTK_HSCALE(gtk_hscale_new(popAdj));
	stopping=GTK_HSCALE(gtk_hscale_new(stoppingAdj));


	g_signal_connect(seedSpin,"value_changed",G_CALLBACK(seedSpinChng),NULL);
	g_signal_connect(tournament,"value_changed",G_CALLBACK(tournamentChng),NULL);
	g_signal_connect(pcSpin,"value_changed",G_CALLBACK(pcSpinChng),NULL);
	g_signal_connect(population,"value_changed",G_CALLBACK(populationChng),NULL);

	g_signal_connect(stopping,"value_changed",G_CALLBACK(stoppingChng),NULL);

	g_signal_emit_by_name(seedSpin,"value_changed");
	g_signal_emit_by_name(tournament,"value_changed");
	g_signal_emit_by_name(pcSpin,"value_changed");
	g_signal_emit_by_name(GTK_WIDGET(population),"value_changed");
	g_signal_emit_by_name(GTK_WIDGET(stopping),"value_changed");
	

	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),GTK_WIDGET(seedLabel));

	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),GTK_WIDGET(seedSpin));

	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),GTK_WIDGET(tourLabel));
	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),GTK_WIDGET(tournament));



	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),pcLabel);
	gtk_box_pack_start_defaults(GTK_BOX(optionsMenu),GTK_WIDGET(pcSpin));


	
	
	gtk_box_pack_start_defaults(GTK_BOX(vbox),hBoxUpMenu);

	for(i=0;i<dimension;i++){

		hbox=gtk_hbox_new(TRUE,0);
		for(j=0;j<dimension;j++){

			sprintf(str,"%d %d",i,j);


			GtkWidget *button=gtk_button_new_with_label("");
			buttonTable[i][j]=button;




			gtk_box_pack_start_defaults(GTK_BOX(hbox),button);




			g_signal_connect(G_OBJECT(button),"clicked",
										G_CALLBACK(enterItem),
												(gpointer)window);

		}
			gtk_box_pack_start_defaults(GTK_BOX(vbox),hbox);
	}



			printf("button 0,0:%X,window:%X\n",(unsigned int)buttonTable[0][0],(unsigned int)window);
		generateButton=gtk_button_new_with_label("GENERATE-SOLVE");
		menuHbox=gtk_hbox_new(TRUE,2);
		gtk_box_pack_start_defaults(GTK_BOX(menuHbox),generateButton);
		gtk_box_pack_start_defaults(GTK_BOX(menuHbox),closeButton);


		

		gtk_box_pack_start_defaults(GTK_BOX(vbox),optionsMenu);

		gtk_box_pack_start_defaults(GTK_BOX(vbox),popLabel);


		gtk_box_pack_start_defaults(GTK_BOX(vbox),GTK_WIDGET(population));
		gtk_box_pack_start_defaults(GTK_BOX(vbox),stoppingLabel);
		gtk_box_pack_start_defaults(GTK_BOX(vbox),GTK_WIDGET(stopping));
		gtk_box_pack_start_defaults(GTK_BOX(vbox),menuHbox);


		
		g_signal_connect(G_OBJECT(window),"delete_event",
				G_CALLBACK(delete_event),NULL);

		g_signal_connect(G_CALLBACK(window),"destroy",
				G_CALLBACK(destroy),NULL);

		g_signal_connect_swapped(G_OBJECT(generateButton),"clicked",
				G_CALLBACK(generation),window);
		

			


		gtk_container_add(GTK_CONTAINER(window),vbox);
	
		gtk_widget_show_all(window);
		gtk_main();







		
		
		return 0;

}
