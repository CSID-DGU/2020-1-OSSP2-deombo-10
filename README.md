# 2020-1-OSSP2-deombo-10
************변경사항************
쉴드 아이템을 추가함 쉴드를 먹으면 잠시 적 총알로부터 무적이 됩니다.
(충돌 판정에는 데미지를 입습니다.)
레이저 보스의 공격을 자연스럽게 수정했습니다.
몇가지 잡 버그를 수정했습니다.
********************************

SPACE 2143

Space Shooting game (Developed by team "deombo")

* Description

    An enhanced version of the MSG project
    Original Open Source : https://github.com/CSID-DGU/2018-1-OSSP-MSG-7
    Written in C++
    
* * *
* How To Run

1. Install SDL library
<pre><code>
sudo apt-get install libsdl1.2-dev

sudo apt-get install libsdl-image1.2-dev
    
sudo apt-get install libsdl-ttf2.0-dev
    
sudo apt-get install libsdl-mixer1.2-dev
</code></pre>
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

scale surface 함수에 대한 레퍼런스
http://www.sdltutorials.com/sdl-scale-surface

http://cse.csusb.edu/tongyu/courses/cs420/notes/sdl.php

https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface

obstacle.png source
The molten rock planet PNG was designed by 千图网, and originated from 千图网 and downloaded from pngtree.com.
https://kor.pngtree.com/freepng/cartoon-lava-rock-planet-is-a-commercial-element_4074202.html

