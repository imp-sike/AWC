# AWC Example Project 
`You Will Eveuntally Die` is a Android Game created with C Programming language and a beautiful library `rawdraw`.  

## Screenshots
![alt text](https://raw.githubusercontent.com/imp-sike/ednp_fake/main/ezgif-2-17b5b53ef1.gif)

## Demo
[demo](https://github.com/imp-sike/AWC/raw/main/demo.apk)


## THANKS!

[rawdraw](https://github.com/cnlohr/rawdraw)

[VadimBoev/CyberBird_unfinished](https://github.com/VadimBoev/CyberBird_unfinished)

## AUDIO CREDITS

1. Background Music
Run Amok by Kevin MacLeod | https://incompetech.com/
Music promoted by https://www.chosic.com/free-music/all/
Creative Commons CC BY 3.0
https://creativecommons.org/licenses/by/3.0/

## Requirements
- Android Studio 
- NDK

## Todo Checkbox

- [X] Manage Folder Structure
- [X] Sepearte Game code from rawdraw in `lib` folder
- [x] Add `init` and `game_loop` functions
- [X] Load images from assets
- [X] Create Menu Based Navigation
- [x] Open link in external apps
- [X] Create complete game
- [X] Add collision Detection
- [X] Add Sound in Game with libbass
- [ ] Make Sound Stop when HOME button or NAVIGATE Button is pressed


 
## Folder Structure and Code Description
> The base game folder and assets folder is seperated from the base rawdrawandroid folder(renamed as giga due to submodule issue)
1. All the game codes must/should/are placed inside the `lib` folder.
2. All the images and assets should be placed in `assets` folder.
3. There must be one `launch.c` file inside the `lib` folder as it is the entry point of application.
4. The basic launch.c code looks like this.
```c
#include "framework.c" // contains all the helper functions for loading images, buttons, etc.

void init() {
    // code that must be called once before the game enters the gameloop
    // for example, loading all the textures, etc
}

void gameloop() {
    // the actual gameloop, do all the game stuffs here, 
    // this is just passed to a while loop that runs continuously
    // until program is exited.
}


void HandleResume()
{
    suspended = 0;
    // things you want to do when the app reesumes, like reinitialize/reload the images from assets 
}

void HandleSuspend()
{
    suspended = 1;
    // things you want to do when the app is suspended 
}


// Entry Point of the Game
int main()
{
    // must pass the two functions to the run function in order to work
    // run function is inside giga/framework.c file.
    run(init, gameloop);
    return 0;
}
```   
5. To run the project first generate the keystroke by  ``` make keystore  ``` command and run ```./build.sh``` for building the apk na drunning in your phone.

## Some Basic Functions that may come handy
 1. Create a text at specified coordinate
```c
    CNFGPenX = 100;
    CNFGPenY = 100;
    CNFGSetLineWidth(10);
    CNFGDrawText("YOU WILL EVENTUALLY DIE!", 15);
```
2. Open a url in external app 
```
    OpenUrl("http://facebook.com);
```

3. Image button
```c 
    ImageButton(void onClick(), image *img, short xmin, short ymin, short width, short height);
```

4. Button
```
    Button(void onClick(), const char *title, int backgroundcolor, int textcolor, int xmin, int ymin,int xmax, int ymax);
```

5. Rendering Images
```c
image *backgroud1;

void init() {
    backgroud1 = loadimagefromapk("sky.png");
    backgroud1->tex = CNFGTexImage(backgroud1->rdimg, backgroud1->w, backgroud1->h);
}

void gameloop() {
    RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
}
```


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)