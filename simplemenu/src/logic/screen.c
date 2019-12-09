#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_video.h>

#include "../headers/constants.h"
#include "../headers/definitions.h"
#include "../headers/globals.h"
#include "../headers/graphics.h"
#include "../headers/input.h"
#include "../headers/logic.h"
#include "../headers/string_utils.h"
#include "../headers/opk.h"

char buf[300];

void showErrorMessage(char *errorMessage) {
	int width = (((strlen(errorMessage))*(180))/calculateProportionalSizeOrDistance(18));
	int height = calculateProportionalSizeOrDistance(40);
	if(strchr(errorMessage,'-')!=NULL) {
		height = calculateProportionalSizeOrDistance(60);
		width = (((strlen(errorMessage)/2)*calculateProportionalSizeOrDistance(200))/calculateProportionalSizeOrDistance(18))+calculateProportionalSizeOrDistance(20);
	}
	int filling[3];
	int borderColor[3];
	borderColor[0]=255;
	borderColor[1]=0;
	borderColor[2]=0;
	filling[0]=100;
	filling[1]=0;
	filling[2]=0;
	SDL_Color textColor;
	textColor.r=255;
	textColor.g=0;
	textColor.b=0;
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width+10), calculateProportionalSizeOrDistance(height+10), SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2)-calculateProportionalSizeOrDistance(5),SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(height/2)-calculateProportionalSizeOrDistance(5), borderColor);
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width), calculateProportionalSizeOrDistance(height), SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2),SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(height/2), filling);
	drawError(errorMessage, textColor);
	itsStoppedBecauseOfAnError=1;
}

void showLetter() {
	int width = 80;
	int filling[3];
	int borderColor[3];
	borderColor[0]=CURRENT_SECTION.headerAndFooterBackgroundColor.r+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.r+45;
	borderColor[1]=CURRENT_SECTION.headerAndFooterBackgroundColor.g+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.g+45;
	borderColor[2]=CURRENT_SECTION.headerAndFooterBackgroundColor.b+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.b+45;
	filling[0]=CURRENT_SECTION.headerAndFooterBackgroundColor.r;
	filling[1]=CURRENT_SECTION.headerAndFooterBackgroundColor.g;
	filling[2]=CURRENT_SECTION.headerAndFooterBackgroundColor.b;
	SDL_Color textColor = CURRENT_SECTION.headerAndFooterTextColor;
	if (pictureMode) {
		filling[0] = 21;
		filling[1] = 18;
		filling[2] = 26;
		borderColor[0]=255;
		borderColor[1]=255;
		borderColor[2]=255;
		textColor.r=255;
		textColor.g=255;
		textColor.b=255;
	}
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width+10), calculateProportionalSizeOrDistance(width+10), SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2)-calculateProportionalSizeOrDistance(5),SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(width/2)-calculateProportionalSizeOrDistance(5), borderColor);
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width), calculateProportionalSizeOrDistance(width), SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2),SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(width/2), filling);
	char letter[2]="";
	char *currentGame = malloc(500);
	currentGame=getFileNameOrAlias(CURRENT_GAME);
	letter[0]=toupper(currentGame[0]);
	letter[1]='\0';
	if(isdigit(letter[0])) {
		letter[0]='#';
	}
	drawCurrentLetter(letter, textColor);
	free(currentGame);
}

void showCurrentEmulator() {
	int height = 30;
	int filling[3];
	int borderColor[3];
	borderColor[0]=CURRENT_SECTION.headerAndFooterBackgroundColor.r+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.r+45;
	borderColor[1]=CURRENT_SECTION.headerAndFooterBackgroundColor.g+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.g+45;
	borderColor[2]=CURRENT_SECTION.headerAndFooterBackgroundColor.b+45>255?255:CURRENT_SECTION.headerAndFooterBackgroundColor.b+45;
	filling[0]=CURRENT_SECTION.headerAndFooterBackgroundColor.r;
	filling[1]=CURRENT_SECTION.headerAndFooterBackgroundColor.g;
	filling[2]=CURRENT_SECTION.headerAndFooterBackgroundColor.b;
	SDL_Color textColor = CURRENT_SECTION.headerAndFooterTextColor;
	if (pictureMode) {
		filling[0] = 21;
		filling[1] = 18;
		filling[2] = 26;
		borderColor[0]=255;
		borderColor[1]=255;
		borderColor[2]=255;
		textColor.r=255;
		textColor.g=255;
		textColor.b=255;
	}
//	char *tempString = malloc(strlen(CURRENT_SECTION.emulatorDirectories[CURRENT_SECTION.activeEmulatorDirectory])+strlen(CURRENT_SECTION.executables[CURRENT_SECTION.activeExecutable])+1);
	char *tempString = malloc(strlen(CURRENT_SECTION.executables[CURRENT_SECTION.activeExecutable])+1);
//	strcpy(tempString,CURRENT_SECTION.emulatorDirectories[CURRENT_SECTION.activeEmulatorDirectory]);
	strcpy(tempString,CURRENT_SECTION.executables[CURRENT_SECTION.activeExecutable]);
	strcat(tempString,"\0");
	int width = strlen(tempString)*11;
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width+10), calculateProportionalSizeOrDistance(height+10), SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2)-calculateProportionalSizeOrDistance(5),SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(height/2)-calculateProportionalSizeOrDistance(5)  , borderColor);
	drawRectangleOnScreen(calculateProportionalSizeOrDistance(width)   , calculateProportionalSizeOrDistance(height)   , SCREEN_WIDTH/2-calculateProportionalSizeOrDistance(width/2)                                       ,SCREEN_HEIGHT/2-calculateProportionalSizeOrDistance(height/2)                                         , filling);
	drawCurrentExecutable(tempString, textColor);
	free(tempString);
}


void showConsole() {
	displayImageOnScreen(CURRENT_SECTION.consolePicture, "PICTURE NOT FOUND");
}

void displayGamePicture() {
	int rgbColor[] = {21, 18, 26};
	char *pictureWithFullPath=malloc(600);
	char *tempGameName=malloc(300);
	if (favoritesSectionSelected) {
		if (favoritesSize == 0) {
			return;
		}
		struct Favorite favorite = favorites[CURRENT_GAME_NUMBER];
		strcpy(pictureWithFullPath, favorite.filesDirectory);
		tempGameName=getGameName(favorite.name);
	} else {
		strcpy(pictureWithFullPath, CURRENT_GAME->directory);
		tempGameName=getGameName(CURRENT_GAME_NAME);
	}
	strcat(pictureWithFullPath,"media/");
	tempGameName=getNameWithoutExtension(tempGameName);
	strcat(pictureWithFullPath,tempGameName);
	strcat(pictureWithFullPath,".png");
	drawRectangleOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, rgbColor);
	displayImageOnScreen(pictureWithFullPath, "NO SCREENSHOT");
	stripGameNameLeaveExtension(tempGameName);
	drawRectangleOnScreen(SCREEN_WIDTH, calculateProportionalSizeOrDistance(18), 0, 222, rgbColor);
	if (strlen(CURRENT_SECTION.aliasFileName)>1||currentSectionNumber==favoritesSectionNumber) {
		char* displayName=getFileNameOrAlias(CURRENT_GAME);
		if (stripGames||strlen(CURRENT_SECTION.aliasFileName)>1) {
			drawPictureTextOnScreen(displayName);
		} else {
			if (currentSectionNumber==favoritesSectionNumber) {
				if (strlen(CURRENT_GAME->alias)<2) {
					char tmp[300];
					strcpy(tmp,getNameWithoutPath(CURRENT_GAME_NAME));
					strcpy(tmp,getNameWithoutExtension(tmp));
					drawPictureTextOnScreen(tmp);
				} else {
					drawPictureTextOnScreen(CURRENT_GAME->alias);
				}
			}
		}
		free(displayName);
	} else {
		if (stripGames) {
			if (strlen(CURRENT_GAME->alias)<2) {
				drawPictureTextOnScreen(tempGameName);
			} else {
				drawPictureTextOnScreen(CURRENT_GAME->alias);
			}
		} else {
			if (strlen(CURRENT_GAME->alias)<2) {
				char tmp[300];
				strcpy(tmp,getNameWithoutPath(CURRENT_GAME_NAME));
				strcpy(tmp,getNameWithoutExtension(tmp));
				drawPictureTextOnScreen(tmp);
			} else {
				drawPictureTextOnScreen(CURRENT_GAME->alias);
			}
		}
	}
	free(pictureWithFullPath);
	free(tempGameName);
}

void displayBackgroundPicture() {
	displayImageOnScreen("./resources/back.png", "NO SCREENSHOT");
}

void drawHeader() {
	char finalString [100];
	char timeString[150];
	int rgbColor[] = {menuSections[currentSectionNumber].headerAndFooterBackgroundColor.r,menuSections[currentSectionNumber].headerAndFooterBackgroundColor.g,menuSections[currentSectionNumber].headerAndFooterBackgroundColor.b};
	drawRectangleOnScreen(SCREEN_WIDTH, calculateProportionalSizeOrDistance(22), 0, 0, rgbColor);
	if (currentCPU==OC_UC) {
		strcpy(finalString,"- ");
		strcat(finalString,menuSections[currentSectionNumber].sectionName);
		strcat(finalString," -");
	} else if (currentCPU==OC_NO) {
		if(currentSectionNumber==favoritesSectionNumber) {
			if(CURRENT_GAME!=NULL) {
				strcpy(finalString,favorites[CURRENT_GAME_NUMBER].section);
			} else {
				strcpy(finalString,CURRENT_SECTION.sectionName);
			}
		} else{
			strcpy(finalString,menuSections[currentSectionNumber].sectionName);
		}
	} else {
		strcpy(finalString,"+ ");
		strcat(finalString,menuSections[currentSectionNumber].sectionName);
		strcat(finalString," +");
	}
//	strcpy(timeString,(asctime(currTime))+11);
//	timeString[strlen(timeString)-9]='\0';
//	drawTimeOnFooter(timeString);
//	char str[20];
//	if (lastChargeLevel==-1) {
//		sprintf(str, "%s", "CHARGING");
//	} else {
//		sprintf(str, "%d%%", lastChargeLevel);
//	}
//	drawBatteryOnFooter(str);
	drawTextOnHeader(finalString);
}

void drawShutDownScreen() {
	int black[] = {0,0,0};
	drawRectangleOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, black);
	drawShutDownText("SHUTTING DOWN");
}

void drawGameList() {
	int rgbColor[] = {menuSections[currentSectionNumber].bodyBackgroundColor.r,menuSections[currentSectionNumber].bodyBackgroundColor.g,menuSections[currentSectionNumber].bodyBackgroundColor.b};
	drawRectangleOnScreen(SCREEN_WIDTH, SCREEN_HEIGHT-calculateProportionalSizeOrDistance(43), 0, calculateProportionalSizeOrDistance(22), rgbColor);
	gamesInPage=0;
	int nextLine = calculateProportionalSizeOrDistance(29);
	char *nameWithoutExtension;
	for (int i=0;i<ITEMS_PER_PAGE;i++) {
		if (CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]!=NULL&&
				CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->name!=NULL) {
			gamesInPage++;
			sprintf(buf,"%s", "");
			if (CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]!=NULL&&
					CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->alias!=NULL&&
					(strlen(CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->alias)>2)) {
				nameWithoutExtension=malloc(strlen(CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->alias)+1);
				strcpy(nameWithoutExtension,CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->alias);
				strcat(nameWithoutExtension,"\0");
			} else {
				nameWithoutExtension=malloc(strlen(CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->name)+1);
				strcpy(nameWithoutExtension,CURRENT_SECTION.romList[menuSections[currentSectionNumber].currentPage][i]->name);
				strcat(nameWithoutExtension,"\0");
				if(stripGames) {
					stripGameName(nameWithoutExtension);
				} else {
					char *tempGame=getNameWithoutPath(nameWithoutExtension);
					strcpy(tempGame,getNameWithoutExtension(tempGame));
					strcpy(nameWithoutExtension,tempGame);
					free(tempGame);
				}
			}
			sprintf(buf,"%s", nameWithoutExtension);
			if (i==menuSections[currentSectionNumber].currentGame) {
				if(strlen(buf)>1) {
					drawShadedGameNameOnScreen(buf, nextLine);
				}
			} else {
				if(strlen(buf)>1) {
					drawNonShadedGameNameOnScreen(buf, nextLine);
				}
			}
			nextLine+=calculateProportionalSizeOrDistance(19);
			free(nameWithoutExtension);
		}
	}
}

void drawFooter(char *text) {
	int rgbColor[] = {menuSections[currentSectionNumber].headerAndFooterBackgroundColor.r,menuSections[currentSectionNumber].headerAndFooterBackgroundColor.g,menuSections[currentSectionNumber].headerAndFooterBackgroundColor.b};
	drawRectangleOnScreen(SCREEN_WIDTH, calculateProportionalSizeOrDistance(22), 0, SCREEN_HEIGHT-calculateProportionalSizeOrDistance(22), rgbColor);
	drawTextOnFooter(text);
}

void setupDecorations() {
	char tempString[200];
	if (CURRENT_GAME==NULL||CURRENT_GAME_NAME==NULL) {
		snprintf(tempString,sizeof(tempString),"GAME %d of %d",CURRENT_SECTION.currentGame+10*CURRENT_SECTION.currentPage, countGamesInSection());
	} else {
		snprintf(tempString,sizeof(tempString),"GAME %d of %d",CURRENT_SECTION.currentGame+1+10*CURRENT_SECTION.currentPage, countGamesInSection());
	}
	drawFooter(tempString);
	drawHeader();
}

void updateScreen() {
//    pthread_mutex_lock(&lock);
	if (!currentlySectionSwitching&&!isUSBMode&&!itsStoppedBecauseOfAnError) {
		drawGameList();
		setupDecorations();
		if (pictureMode) {
			displayGamePicture();
		}
		if (currentlyChoosingEmulator) {
			showCurrentEmulator();
		}
		if (hotKeyPressed) {
			if (CURRENT_GAME_NAME!=NULL) {
				showLetter();
			}
		}
	} else if (isUSBMode) {
		drawUSBScreen();
	} else if (itsStoppedBecauseOfAnError) {
		showErrorMessage(errorMessage);
	}
	refreshScreen();
//    pthread_mutex_unlock(&lock);
}

void setupDisplayAndKeys() {
	//	pumpEvents();
	initializeFonts();
	initializeDisplay();
	initializeKeys();
}
