<a name="readme-top"></a>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h1 align="center">The Binding Of Isaac</h1>

  <p align="center">
    It is a roguelike game whose story is imspired by the Biblical story of the same name.
    It take a lot of inspiration from The legend of Zelda, but everything is procedurally generated.
    <br />
    <strong>Original game : </strong>
    <a href="https://bindingofisaacrebirth.fandom.com/wiki/Binding_of_Isaac:_Rebirth_Wiki"><strong>General info »</strong></a>
    ·
    <a href="https://youtu.be/QjK0qeu6Xpk"><strong>Youtube video »<strong></a>
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

![screenshot of the project running](<Screenshot 2024-06-09 221306.png>)

Here's why:
* reason 1
It looked like something I could recreate.
* reason 2
I had never played it before and it has very good reviews so I wanted to try it.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
* A player character.
* An enemy
* an item
* The random generation of the level.
### What I will probably make as well:
* More enemies
* More items
* A boss.

### What I plan to create if I have enough time left:
* The shop mechanic.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
Detailed instructions on how to run your game project are in this section.

### Prerequisites

* Visual Studio 2022:
You can download this online from Microsoft.

### How to run the project

You download the latest version and set it to the startup project, you can do this by right clicking on TheBindingOfIsaac on the side of your screen.
After this you just hit the green playbutton on the top and you can play.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- HOW TO PLAY -->
## How to play

### Controls
* keys:
W, A, S and D to go up, left, down and right respectively.
Up, left down and right arrows to shoot up, left, down and right respectively.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 

The player class owns a bullet class that is used in a vector to make the multiple bullets the palyer can shoot, I also use this vector to pass on to other classes for hit detection.

### Inheritance 
Inheritance is used in the classes of the enemies, the classes of the items and the classes for the rooms, this is for future proofing and to only need one data member to store all these things.

For the enemies, they would be stored in the Room struct so that every room can open and close based on if the enemies are alive or not.

The Items are stored in the game class itself and passed to the Map for drawing and to the player for altering there stats.

The rooms are managed by the map class, this way the Map class only makes a grid and assigns the room to it. Afterwards, it's just used for passing data.

### ..

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

Wout Claes - wout.claes@student.howest.be

Project Link: [https://github.com/HowestDAE/DAE13-WoutClaes](https://github.com/HowestDAE/DAE13-WoutClaes)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. 

* [The Website where the ripped srites are from](https://www.spriters-resource.com/pc_computer/bindingofisaacrebirth/)
* [The website that helped me create the algorithm for the random map generation](https://www.boristhebrave.com/2020/09/12/dungeon-generation-in-binding-of-isaac/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

