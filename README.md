# 2020-1-OSSP2-deombo-10
# SPACE 2143

********************************

SPACE 2143

Space Shooting game (Developed by team "deombo")

* Description

    An enhanced version of the MSG project
    Original Open Source : https://github.com/CSID-DGU/2018-1-OSSP-MSG-7
    Platform : Linux, Ubuntu
    IDE : visual studio code
    Tool & Library : SDL1.2, SDL1.2 mixer(오디오 관련 라이브러리), Aseprite(간단한 이미지 편집)
    Programming Language : C++

* Roles of each member

    Jaeho Jang : writing report, adding audio, adding new damage role(when player character is out of screen), adding new enemies and items
    Yeonji Lim : writing report, adding new boss and obstacles
    Yongheon Jeong : making presentation power point, adding enemies, improving graphics
    All members do : analyzing code and SDL library, fixing bugs, finding assets
    
* * *
* How To Run

1. Install SDL library
<pre><code>
sudo apt-get install libsdl1.2-dev

sudo apt-get install libsdl-image1.2-dev
    
sudo apt-get install libsdl-ttf2.0-dev
    
sudo apt-get install libsdl-mixer1.2-dev
</code></pre>
You can try 'apt' instead of 'apt-get'

2. Install g++
<pre><code>
sudo apt-get install g++
</code></pre>

3. Pull or clone our github
<pre><code>
git clone https://github.com/CSID-DGU/2020-1-OSSP2-deombo-10.git
</code></pre>

4. Type the things in "make" file and compile
<pre><code>
g++ -o main main.cpp helpers.h helpers.cpp AirPlane.cpp AirPlane.h define.h -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -std=c++14
</code></pre>

5. Run the "main"
<pre><code>
./main
</code></pre>
* * *
* using some code from SDL_gfx

reference of scale surface function
http://www.sdltutorials.com/sdl-scale-surface

http://cse.csusb.edu/tongyu/courses/cs420/notes/sdl.php

https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface

obstacle.png source
The molten rock planet PNG was designed by 千图网, and originated from 千图网 and downloaded from pngtree.com.
https://kor.pngtree.com/freepng/cartoon-lava-rock-planet-is-a-commercial-element_4074202.html

