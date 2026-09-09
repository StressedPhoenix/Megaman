<a name="readme-top"></a>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h2 align="center">Mega Man X</h2>

  <p align="center">
    Mega Man X is the first of the Mega Man X series. It was originally released in 1993 for the SNES. Mega Man X is an action-platform game where the player takes control of the eponymous character and must complete a set of eight, initial stages in any order desired. Defeating the boss character at the end of each stage grants the player one new weapon that can then be toggled and used at will for the remainder of the game. And throughout the levels, more body upgrades can be found as well.
    <br />
    <strong>Original game : </strong>
    <a href="https://megaman.fandom.com/wiki/Mega_Man_X_(video_game)"><strong>General info »</strong></a>
    ·
    <a href="https://www.youtube.com/watch?v=KDciDXnm3ek"><strong>Youtube video »<strong></a>
    <br />
    <br />
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#my-version">My version</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#how-to-play">How To Play</a></li>
    <li><a href="#class-structure">Class structure</a></li>
    <li><a href="#checklist">Checklist</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

![screenshot of the original game](<images_&_spritesheets/README/DAE15_Wout_Claes_GameProposal_ScreenShot.jpg>)

Here's why:
* Reason 1: It looked like a fun side scroler that I could recreate

* Reason 2: I had heard a lot about the megaman series but never played any of the games, so this is a good excuse to play one of them

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
* The player character X
* Some basic enemies
* Charge shot mechanic

### What I will probably make as well:
* Level destruction
* Wall jump mechanic

### What I plan to create if I have enough time left:
* More of the level than is seen in the proposal video
* The final boss of the level

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)

### How to run the project

Explain which project (version) must be run.
* Download the latest version of the project and open the .sln file in visual studio, set the startup project to MegaManX. This is done by right clicking on MegaManX in the solution explorer and selecting "set as startup project". Pressing the green arrow now at the top of visual studio should run the game (or press F5).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- HOW TO PLAY -->
## How to play

### Controls
Universal:
* Page up to turn the volume up
* Page down to turn the volume down

In the menu:
* Up and down arow keys to select a different option
* Spacebar to select

![screenshot of the menu](<images_&_spritesheets/README/Menu.png>)

In the game:
* a & d to move left and right respectivly.
* Click and hold to shoot and charge the shot.
* Spacebar to jump.
* Backspace to reset the game to the menu
* k to reset the level

![screenshot of the menu](<images_&_spritesheets/README/Game.png>)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 
* The Bullet manager class contains a std::vector that contains Bullet* objects, while these objects are created on the heap they are still managed by the manager class.
* The Enemy manager class contains a std::vector that contains Enemy* objects, while these objects are created on the heap they are still managed by the manager class.

### Inheritance 
* The bullets all inherit from a base Bullet class, this base Bullet class is then called in a bullet manager and the correct bullets are used because of polymorphism.
* The enemies all inherit from a base Enemy class, this base Enemy class is then called in a enemy manager and the correct enemies are used because of polymorphism.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [x] week 01 topics applied
    - [x] const keyword applied proactively (variables, functions,..)
    - [x] static keyword applied proactively (class variables, static functions,..)
    - [x] object composition (optional)
- [x] week 02 topics applied
- [x] week 03 topics applied
- [x] week 04 topics applied
- [x] week 05 topics applied
- [x] week 06 topics applied
- [x] week 07 topics applied
- [x] week 08 topics applied
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Wout Claes - Wout.Claes@student.howest.be

Project Link: [https://github.com/HowestDAE/dae15-WoutClaes](https://github.com/HowestDAE/dae15-WoutClaes)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Spritesheet slicing tool](https://www.gamedeveloperstudio.com/tools/spritesheet_slicer.php)
* [Spritesheet Resource](https://www.spriters-resource.com/snes/mmx/)
* [Sounds Resource](https://www.sounds-resource.com/snes/megamanx/sound/8913/)
* [wikki](https://megaman.fandom.com/wiki/Mega_Man_X_(video_game))

<p align="right">(<a href="#readme-top">back to top</a>)</p>

