/*
 * ----------------------------------------------------------------------------
 * "LICENCE BEERWARE" (Révision 42):
 * Red-J a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour.
   __________           .___              ____.
   \______   \ ____   __| _/             |    |
	|       _// __ \ / __ |   ______     |    |
	|    |   \  ___// /_/ |  /_____/ /\__|    |
	|____|_  /\___  >____ |          \________|
		   \/     \/     \/                    
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <ppu-lv2.h>
#include <io/pad.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sysutil/msg.h>
#include <sysutil/sysutil.h>

#include "copy.h"
#include "syscalls.h"
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <io/pad.h>



#define SUCCESS 0
#define FAILED -1

#define SC_SYS_POWER 					(379)
#define SYS_REBOOT				 		0x8201


#define	MENU 	"/dev_hdd0/game/COBJ75511/USRDIR/menu.bmp"


int sys_get_version(u32 *version)
{
	lv2syscall2(8, 0x7000, (u64) version);//////////////////////////////////////////
	return_to_user_prog(int);
}
s32 lv2_get_target_type(u64 *type)
{
	lv2syscall1(985, (u64) type);
	return_to_user_prog(s32);
}

s32 main(s32 argc, char* argv[])
{ 
	u64 type;
	lv2_get_target_type(&type);

    char version= 0;
	char version2= 0;
	char version3=0;
	

    FILE *f = fopen("/dev_flash/vsh/etc/version.txt", "r");
	
	fseek(f, 9, SEEK_SET);
	fscanf(f, "%c", &version);
	fseek(f, 11, SEEK_SET);
	fscanf(f, "%c", &version2);
	fseek(f, 12, SEEK_SET);
	fscanf(f, "%c", &version3);
	

		
	padInfo2 joypadInfo;    //initialisation des parametres de la manette
	padData joypadData;
	ioPadInit(7);       
	
	
  ////////////////////////////////////////////
 //           Partie graphique			   //
////////////////////////////////////////////
	SDL_Surface *ecran = NULL,*imagedefond = NULL,*imagedefond2 = NULL,*imagedefond3 = NULL,*aboutfnd = NULL,*about = NULL,*about2 = NULL,*about3 = NULL,*about4 = NULL,*about5 = NULL,*about6 = NULL,*aboutls = NULL,*TITLE = NULL,*texteUse = NULL,*texteUse2 = NULL,*ttype = NULL,*texteCROSS1 = NULL,*texteSQUARE1 = NULL,*texteCIRCLE1 = NULL,*texteTRIANGLE1 = NULL,*texteLR = NULL,*texteLR2 = NULL,*CROSS1 = NULL,*SQUARE1 = NULL,*CIRCLE1 = NULL,*TRIANGLE1 = NULL,*LR = NULL;
	 /* initialisation des variables SDL à 0*/
	
	SDL_Rect position;
	
	TTF_Font *font = NULL;	// déclaration de la variable police de caractère 1
	TTF_Font *font2 = NULL;	// déclaration de la variable police de caractère 2
	SDL_Color colorwhite = { 255, 255, 255}; // déclaration de la variable couleur blanche SDL
	SDL_Color colorred = { 255, 0, 0}; // déclaration de la variable couleur rouge SDL
	//SDL_Color colorblue = { 0, 0, 255}; // déclaration de la variable couleur bleue SDL
    SDL_Init( SDL_INIT_EVERYTHING );// déclaration et Initialisation de la SDL principal
	TTF_Init();// déclaration et Initialisation de la SDL ttf
	ecran = SDL_SetVideoMode(1200,700,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN); //1200 ok
//ecran = SDL_SetVideoMode(1024, 720, 32, SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN); 	// definition de la resolution 
    imagedefond = SDL_LoadBMP(MENU);// déclaration de la variable imagedefond
	imagedefond2 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/menu2.bmp");
	imagedefond3 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/menu3.bmp");
	aboutfnd = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/about.bmp");
	CROSS1 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/CROSS.bmp");// déclaration de la variable CROSS1
	SQUARE1 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/SQUARE.bmp");// déclaration de la variable SQUARE1
	CIRCLE1 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/CIRCLE.bmp");// déclaration de la variable CIRCLE1
	TRIANGLE1 = SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/TRIANGLE.bmp");// déclaration de la variable TRIANGLE1
	LR= SDL_LoadBMP("/dev_hdd0/game/COBJ75511/USRDIR/LR.bmp");
	font = TTF_OpenFont("/dev_hdd0/game/COBJ75511/USRDIR/PS3.TTF", 24);// déclaration de la variable police de caractère "font" et de sa taille
	font2 = TTF_OpenFont("/dev_hdd0/game/COBJ75511/USRDIR/PS3.TTF", 32);// déclaration de la variable police de caractère "font2" et de sa taille
	
	////////////TYPE DE CONSOLE//////
	if(type==1)
		{
		
		ttype = TTF_RenderText_Blended(font, " FW: CEx", colorwhite);
		}
	else if(type==2)
		{
		
		ttype = TTF_RenderText_Blended(font, " FW: DEx", colorwhite);
		}
	else
		{
		
		ttype = TTF_RenderText_Blended(font, " FW: DECR", colorwhite);
		}

	//////////////////////////////////////////////////////////////////
	
	TITLE = TTF_RenderText_Blended(font2, "COBRA INStALLER 7.55 By Red-J", colorwhite);// déclaration de la variable TITLE
	texteCROSS1 = TTF_RenderText_Blended(font, "INStALLER LES FICHIERS", colorwhite);// déclaration de la variable texteCROSS1
	texteSQUARE1 = TTF_RenderText_Blended(font, "REStAURER LES FICHIERS", colorwhite);// déclaration de la variable texteSQUARE1
	texteTRIANGLE1 = TTF_RenderText_Blended(font, "ABOUt", colorwhite);// déclaration de la variable texteTRIANGLE1
	texteCIRCLE1 = TTF_RenderText_Blended(font, "QUIttER", colorwhite);// déclaration de la variable texteCIRCLE1
	texteLR = TTF_RenderText_Blended(font, "CHANGER BACkGROUND", colorwhite);
	texteLR2 = TTF_RenderText_Blended(font, "RETOUR", colorwhite);
	texteUse = TTF_RenderText_Blended(font, "FIRMWARE rEBUG 4.82 UNIQUEMENt!!!", colorwhite);// déclaration de la variable texteUse
	//texteUse2 = TTF_RenderText_Blended(font, "'custom' sur votre clef USB", colorwhite);// déclaration de la variable texteUse
	about = TTF_RenderText_Blended(font2, "ABOUt", colorwhite);// déclaration de la variable texteUse
	about2 = TTF_RenderText_Blended(font, "HOMEBREW CREE AVEC PSL1GHt V2", colorwhite);// déclaration de la variable texteUse
	about3 = TTF_RenderText_Blended(font, "REMERCIEMENtS AUx MEMBRES QUI FONt ", colorwhite);// déclaration de la variable texteUse
	about4 = TTF_RenderText_Blended(font, "BOUGER LA SCENE PS3 AINSI QUE COOL72 ", colorwhite);// déclaration de la variable texteUse
	about5 = TTF_RenderText_Blended(font, "0_obeWAN BIQUET Et BIEN D'AUtRES", colorwhite);// déclaration de la variable texteUse
	about6 = TTF_RenderText_Blended(font, "LA SEULE LIMItE DU DEv ESt L'IMAGINAtION...", colorwhite);// déclaration de la variable texteUse
	aboutls = TTF_RenderText_Blended(font, "WWW.MODCONSOLES.FR", colorwhite);// déclaration de la variable texteUse
	
	
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
// boucle de contrôle des actions de la manette


        position.x = 0;  //position horizontale de imagedefond
		position.y = 0; //position verticale de imagedefond
		SDL_BlitSurface(imagedefond, NULL, ecran, &position); 

		//usleep(200);

		position.x = 160; //position horizontale de	TITLE	
        position.y = 20; //position verticale de TITLE
		SDL_BlitSurface(TITLE, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		////////
		position.x = 50; //position horizontale de	type	
        position.y = 100; //position verticale de type
		SDL_BlitSurface(ttype, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		
		position.x = 200; //position horizontale de	texteUse						///////////////////		
        position.y = 440; //position verticale de texteUse
		SDL_BlitSurface(texteUse, NULL, ecran, &position); //transfert de la surface de texteUse sur la surface ecran
		
		position.x = 140; //position horizontale de	texteUse2								
        position.y = 480; //position verticale de texteUse2
		SDL_BlitSurface(texteUse2, NULL, ecran, &position); //transfert de la surface de texteUse2 sur la surface ecran
		
        position.x = 50; //position horizontale de CROSS1
        position.y = 570; //position verticale de CROSS1
		SDL_BlitSurface(CROSS1, NULL, ecran, &position);  //transfert de la surface de CROSS1 sur la surface ecran
        
		position.x = 100; //position horizontale de	texteCROSS1								
        position.y = 580; //position verticale de texteCROSS1
		SDL_BlitSurface(texteCROSS1, NULL, ecran, &position); //transfert de la surface de texteCROSS1 sur la surface ecran
		
		
		position.x = 110; //position horizontale de SQUARE1
		position.y = 610; //position verticale de SQUARE1
		SDL_BlitSurface(SQUARE1, NULL, ecran, &position); //transfert de la surface de SQUARE1 sur la surface ecran
        
		position.x = 160; //position horizontale de texteSQUARE1
		position.y = 620; //position verticale de texteSQUARE1
		SDL_BlitSurface(texteSQUARE1, NULL, ecran, &position); //transfert de la surface de texteSQUARE1 sur la surface ecran
		
		
        position.x = 900; //position horizontale de CIRCLE1
		position.y = 570; //position verticale de CIRCLE1
		SDL_BlitSurface(CIRCLE1, NULL, ecran, &position); //transfert de la surface de CIRCLE1 sur la surface ecran
        
		
		position.x = 950; //position horizontale de texteCIRCLE1
        position.y = 580; //position verticale de texteCIRCLE1
		SDL_BlitSurface(texteCIRCLE1, NULL, ecran, &position); //transfert de la surface de texteCIRCLE1 sur la surface ecran
		
		
        position.x = 840; //position horizontale de TRIANGLE1
		position.y = 610; //position verticale de TRIANGLE1
		SDL_BlitSurface(TRIANGLE1, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 900; //position horizontale de texteTRIANGLE1
		position.y = 620; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteTRIANGLE1, NULL, ecran, &position); //transfert de la surface de texteTRIANGLE1 sur la surface ecran
		
		position.x = 260; //position horizontale de	texteCROSS1								
        position.y = 655; //position verticale de texteCROSS1
		SDL_BlitSurface(LR, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 420; //position horizontale de texteTRIANGLE1
		position.y = 665; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteLR, NULL, ecran, &position);
		
        SDL_Flip(ecran);
		

	
		int manette=1;


   
  ////////////////////////////////////////////////////////
 //           Partie installation et actions		   //
////////////////////////////////////////////////////////
	
	while(manette)// boucle de contrôle des actions de la manette
		{
		
				ioPadGetInfo2(&joypadInfo);
	
				if(joypadInfo.port_status[0])
				{
					ioPadGetData(0, &joypadData);
						if( joypadData.BTN_SQUARE )// si bouton CARRE
							{SDL_Surface *restore = NULL; //initialise la variable restore à 0
							restore = TTF_RenderText_Blended(font2, "REStAURAtION EFFECTUEE", colorred); //défini le contenu de la variable restore
if(type==1)
		{	
			if ((version=='4')&(version2=='8')&(version3=='2'))	
			{					
							{if(is_dev_blind_mounted()!=0); // verifie que dev_blind n'est pas monté
								
									mount_dev_blind();// monte dev_blind   
									
									//restaure les fichiers d'un point "a" à un point "b" 
									FILE* backupf1 = NULL;
									backupf1 = fopen("/dev_hdd0/game/COBJ75511/USRDIR/BACKUP/stage2.cex", "r");
									
									if(backupf1 == NULL)
										{
										fclose(backupf1);
										
										
										SDL_Surface *nofiles = NULL; //initialise la variable restore à 0
									nofiles = TTF_RenderText_Blended(font2, "PAS DE BACKUP !!!", colorred); //défini le contenu
								
									position.x = 280; //position horizontale de nofiles  et isntall???
									position.y = 512; //position verticale de nofiles
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(nofiles, NULL, ecran, &position);//transfert de la surface de nofiles sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(nofiles); //le programme détruit la surface nofiles
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
										
								
										{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console
										}	
									
									CopyFile("/dev_hdd0/game/COBJ75511/USRDIR/BACKUP/stage2.cex","/dev_blind/Rebug/cobra/stage2.cex");
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(restore, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(restore);
									SDL_FreeSurface(ecran);//le programme détruit la surface restore
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
							}
			}
			else
		{

									SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
								
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
		}
}
else if(type==2)
		{	
			if ((version=='4')&(version2=='8')&(version3=='2'))
			{					
							{
								
								
								SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
								
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
								
								}
		}

else
		{

									SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
								
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
		}
							
							
}
}				
				
						
						if( joypadData.BTN_TRIANGLE )// si bouton TRIANGLE
						{
					
						 
						position.x = 0;  //position horizontale de imagedefond
						position.y = 0; //position verticale de imagedefond
						SDL_BlitSurface(aboutfnd, NULL, ecran, &position); //transfert de la surface de imagedefond sur la surface ecran
						
						
						position.x = 530; //position horizontale de	about	
						position.y = 50; //position verticale de about
						SDL_BlitSurface(about, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran	
						
						position.x = 220; //position horizontale de	about2	
						position.y = 150; //position verticale de about2
						SDL_BlitSurface(about2, NULL, ecran, &position); //transfert de la surface de about2 sur la surface ecran	
						
						position.x = 120; //position horizontale de	about3	
						position.y = 190; //position verticale de about3
						SDL_BlitSurface(about3, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran	
												
						position.x = 120; //position horizontale de	about4	
						position.y = 220; //position verticale de about4
						SDL_BlitSurface(about4, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran	
												
						position.x = 120; //position horizontale de	about5	
						position.y = 260; //position verticale de about5
						SDL_BlitSurface(about5, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran

						position.x = 100; //position horizontale de about6	
						position.y = 340; //position verticale de about5
						SDL_BlitSurface(about6, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran						
						
						position.x = 50; //position horizontale de aboutls	
						position.y = 640; //position verticale de aboutls
						SDL_BlitSurface(aboutls, NULL, ecran, &position); //transfert de la surface de about sur la surface ecran	
						
						position.x = 680; //position horizontale de	texteCROSS1								
						position.y = 655; //position verticale de texteCROSS1
						SDL_BlitSurface(LR, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
						position.x = 840; //position horizontale de texteTRIANGLE1
						position.y = 665; //position verticale de texteTRIANGLE1
						SDL_BlitSurface(texteLR2, NULL, ecran, &position);
						
						SDL_Flip(ecran);
							//SDL_Surface *about = NULL;//initialise la variable about à 0
							//about=SDL_LoadBMP("/dev_hdd0/game/REDJ00011/USRDIR/about.bmp");//défini le contenu de la variable about
							//SDL_BlitSurface(about, NULL, ecran, NULL);//transfert de la surface de about sur la surface ecran
							//SDL_Flip(ecran);//mise à jour de l'écran
						}
						
						if( joypadData.BTN_L1 )// si bouton TRIANGLE
						{
		position.x = 0;  //position horizontale de imagedefond
		position.y = 0; //position verticale de imagedefond
		SDL_BlitSurface(imagedefond2, NULL, ecran, &position); 

		//usleep(200);

		position.x = 160; //position horizontale de	TITLE	
        position.y = 20; //position verticale de TITLE
		SDL_BlitSurface(TITLE, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		////////
		position.x = 50; //position horizontale de	type	
        position.y = 100; //position verticale de type
		SDL_BlitSurface(ttype, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		
		position.x = 200; //position horizontale de	texteUse						///////////////////		
        position.y = 440; //position verticale de texteUse
		SDL_BlitSurface(texteUse, NULL, ecran, &position); //transfert de la surface de texteUse sur la surface ecran
		
		position.x = 140; //position horizontale de	texteUse2								
        position.y = 480; //position verticale de texteUse2
		SDL_BlitSurface(texteUse2, NULL, ecran, &position); //transfert de la surface de texteUse2 sur la surface ecran
		
        position.x = 50; //position horizontale de CROSS1
        position.y = 570; //position verticale de CROSS1
		SDL_BlitSurface(CROSS1, NULL, ecran, &position);  //transfert de la surface de CROSS1 sur la surface ecran
        
		position.x = 100; //position horizontale de	texteCROSS1								
        position.y = 580; //position verticale de texteCROSS1
		SDL_BlitSurface(texteCROSS1, NULL, ecran, &position); //transfert de la surface de texteCROSS1 sur la surface ecran
		
		
		position.x = 110; //position horizontale de SQUARE1
		position.y = 610; //position verticale de SQUARE1
		SDL_BlitSurface(SQUARE1, NULL, ecran, &position); //transfert de la surface de SQUARE1 sur la surface ecran
        
		position.x = 160; //position horizontale de texteSQUARE1
		position.y = 620; //position verticale de texteSQUARE1
		SDL_BlitSurface(texteSQUARE1, NULL, ecran, &position); //transfert de la surface de texteSQUARE1 sur la surface ecran
		
		
        position.x = 900; //position horizontale de CIRCLE1
		position.y = 570; //position verticale de CIRCLE1
		SDL_BlitSurface(CIRCLE1, NULL, ecran, &position); //transfert de la surface de CIRCLE1 sur la surface ecran
        
		
		position.x = 950; //position horizontale de texteCIRCLE1
        position.y = 580; //position verticale de texteCIRCLE1
		SDL_BlitSurface(texteCIRCLE1, NULL, ecran, &position); //transfert de la surface de texteCIRCLE1 sur la surface ecran
		
		
        position.x = 840; //position horizontale de TRIANGLE1
		position.y = 610; //position verticale de TRIANGLE1
		SDL_BlitSurface(TRIANGLE1, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 900; //position horizontale de texteTRIANGLE1
		position.y = 620; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteTRIANGLE1, NULL, ecran, &position); //transfert de la surface de texteTRIANGLE1 sur la surface ecran
		
		position.x = 260; //position horizontale de	texteCROSS1								
        position.y = 655; //position verticale de texteCROSS1
		SDL_BlitSurface(LR, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 420; //position horizontale de texteTRIANGLE1
		position.y = 665; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteLR, NULL, ecran, &position);
		
        SDL_Flip(ecran);

							
						}
						
						
						if( joypadData.BTN_R1 )// si bouton TRIANGLE
						{
		position.x = 0;  //position horizontale de imagedefond
		position.y = 0; //position verticale de imagedefond
		SDL_BlitSurface(imagedefond3, NULL, ecran, &position); 

		//usleep(200);

		position.x = 160; //position horizontale de	TITLE	
        position.y = 20; //position verticale de TITLE
		SDL_BlitSurface(TITLE, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		////////
		position.x = 50; //position horizontale de	type	
        position.y = 100; //position verticale de type
		SDL_BlitSurface(ttype, NULL, ecran, &position); //transfert de la surface de TITLE sur la surface ecran
		
		
		position.x = 200; //position horizontale de	texteUse						///////////////////		
        position.y = 440; //position verticale de texteUse
		SDL_BlitSurface(texteUse, NULL, ecran, &position); //transfert de la surface de texteUse sur la surface ecran
		
		position.x = 140; //position horizontale de	texteUse2								
        position.y = 480; //position verticale de texteUse2
		SDL_BlitSurface(texteUse2, NULL, ecran, &position); //transfert de la surface de texteUse2 sur la surface ecran
		
        position.x = 50; //position horizontale de CROSS1
        position.y = 570; //position verticale de CROSS1
		SDL_BlitSurface(CROSS1, NULL, ecran, &position);  //transfert de la surface de CROSS1 sur la surface ecran
        
		position.x = 100; //position horizontale de	texteCROSS1								
        position.y = 580; //position verticale de texteCROSS1
		SDL_BlitSurface(texteCROSS1, NULL, ecran, &position); //transfert de la surface de texteCROSS1 sur la surface ecran
		
		
		position.x = 110; //position horizontale de SQUARE1
		position.y = 610; //position verticale de SQUARE1
		SDL_BlitSurface(SQUARE1, NULL, ecran, &position); //transfert de la surface de SQUARE1 sur la surface ecran
        
		position.x = 160; //position horizontale de texteSQUARE1
		position.y = 620; //position verticale de texteSQUARE1
		SDL_BlitSurface(texteSQUARE1, NULL, ecran, &position); //transfert de la surface de texteSQUARE1 sur la surface ecran
		
		
        position.x = 900; //position horizontale de CIRCLE1
		position.y = 570; //position verticale de CIRCLE1
		SDL_BlitSurface(CIRCLE1, NULL, ecran, &position); //transfert de la surface de CIRCLE1 sur la surface ecran
        
		
		position.x = 950; //position horizontale de texteCIRCLE1
        position.y = 580; //position verticale de texteCIRCLE1
		SDL_BlitSurface(texteCIRCLE1, NULL, ecran, &position); //transfert de la surface de texteCIRCLE1 sur la surface ecran
		
		
        position.x = 840; //position horizontale de TRIANGLE1
		position.y = 610; //position verticale de TRIANGLE1
		SDL_BlitSurface(TRIANGLE1, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 900; //position horizontale de texteTRIANGLE1
		position.y = 620; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteTRIANGLE1, NULL, ecran, &position); //transfert de la surface de texteTRIANGLE1 sur la surface ecran
		
		position.x = 260; //position horizontale de	texteCROSS1								
        position.y = 655; //position verticale de texteCROSS1
		SDL_BlitSurface(LR, NULL, ecran, &position); //transfert de la surface de TRIANGLE1 sur la surface ecran
		
        position.x = 420; //position horizontale de texteTRIANGLE1
		position.y = 665; //position verticale de texteTRIANGLE1
		SDL_BlitSurface(texteLR, NULL, ecran, &position);
		
        SDL_Flip(ecran);
						 
							
						}
							
						if( joypadData.BTN_CROSS )// si bouton Croix
							{SDL_Surface *install = NULL; //initialise la variable restore à 0
							install = TTF_RenderText_Blended(font2, "INStALLAtion EFFECTUEE", colorred); //défini le contenu de la variable restore
if(type==1)
		{	
			if ((version=='4')&(version2=='8')&(version3=='2'))	
			{											
							{if(is_dev_blind_mounted()!=0); // verifie que dev_blind n'est pas monté
								
									mount_dev_blind();// monte dev_blind   
									
									//restaure les fichiers d'un point "a" à un point "b" 
									CopyFile("/dev_blind/Rebug/cobra/stage2.cex","/dev_hdd0/game/COBJ75511/USRDIR/BACKUP/stage2.cex");
									CopyFile("/dev_hdd0/game/COBJ75511/USRDIR/stage2.cex","/dev_blind/Rebug/cobra/stage2.cex");
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(install, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(install);
									SDL_FreeSurface(ecran);//le programme détruit la surface restore
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
							}
			}
			else
		{

									SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
								
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
		}
}
else if(type==2)
		{	
			if ((version=='4')&(version2=='8')&(version3=='2'))
			{							
							{SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
								
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
								}
			}

else
		{

									SDL_Surface *incompatible = NULL; //initialise la variable restore à 0
									incompatible = TTF_RenderText_Blended(font2, "CONSOLE INCOMPAtIBLE", colorred); //défini le contenu
									
						
									position.x = 200; //position horizontale de restore
									position.y = 512; //position verticale de restore
									{ lv2syscall3(392, 0x1004, 0x4, 0x6); } //émet un bip sonore
									SDL_BlitSurface(incompatible, NULL, ecran, &position);//transfert de la surface de restore sur la surface ecran
									SDL_Flip(ecran); //mise a jour de l'écran
									SDL_Delay(5000); // le programme fait une pause 5 secondes
									SDL_FreeSurface(incompatible); //le programme détruit la surface restore
									SDL_FreeSurface(ecran);
									unmount_dev_blind();
									fclose(f);// annule le montage de dev_blind
									sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							
									{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

									return 0;
		}
							
							
}
}
				
						if( joypadData.BTN_CIRCLE ) //si rond
						{SDL_FreeSurface(ecran);//le programme détruit la surface install
							
							sysLv2FsUnlink("/dev_hdd0/tmp/turnoff");// quitte le programme de la bonne manière
							{lv2syscall3(SC_SYS_POWER, SYS_REBOOT, 0, 0); return_to_user_prog(int);}// Reboot la console

										
							return 0;
						}
				
									
				}
		
		
		SDL_Flip(ecran);//mise à jour de l'écran
		


		}
		
		
		
		TTF_CloseFont(font);//le programme ferme la police d'ecriture font
		TTF_CloseFont(font2);//le programme ferme la police d'ecriture font2
		SDL_FreeSurface(texteSQUARE1);//le programme détruit la surface texteSQUARE1
		SDL_FreeSurface(texteTRIANGLE1);//le programme détruit la surface TRIANGLE1
		SDL_FreeSurface(texteCROSS1);//le programme détruit la surface texteCROSS1
		SDL_FreeSurface(texteCIRCLE1);//le programme détruit la surface texteCIRCLE1
		SDL_FreeSurface(TITLE);//le programme détruit la surface TITLE
		SDL_FreeSurface(about);//le programme détruit la surface about

		TTF_Quit();// quite le contexte TTF de SDL
		

	SDL_FreeSurface(imagedefond);//le programme détruit la surface imagedefond
	SDL_FreeSurface(SQUARE1);//le programme détruit la surface SQUARE1
	SDL_FreeSurface(TRIANGLE1);//le programme détruit la surface TRIANGLE1
	SDL_FreeSurface(CROSS1);//le programme détruit la surface CROSS1
	SDL_FreeSurface(CIRCLE1);//le programme détruit la surface CIRCLE1

	
	SDL_Quit();// quite le contexte SDL
	
	return 0;
}