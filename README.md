# CS 539 - Real-time Rendering


Code Style
--------

- Naming:
  - The private property:
    e.g:
    _myProperty

- The public property:
  - e.g:
    myProperty

- The private function:
  - e.g:
    MyFuction();

- The public function:
  - e.g:
    MyFuction();

- The class:
  - e.g:
    MyClass
    {
    }
- Generic variables should have the same name as their type
  - e.g:
    SetDrawable(IDrawable * drwable);

- Iterator variables should be called i, j, k ,
  - e.g:
    for(int i=0 ,i<length,i++)

Features
--------
- Water Simulation
- Heightmap Generated Terrain
- Sound Effect
- Shadows
- Lighting
- Skybox
- Textured 3D Models
- Quaternions Camera
- Bump Mapping 
- Environment Mapping

Library dependencies - SDL
--------
- [SDL-Simple DirectMedia Layer](http://www.libsdl.org/)
  - Used for window and renderer, image and sound loading

- [Assimp - Open Asset Import Library ](http://assimp.sourceforge.net/)
  - Used for window and renderer, image and sound loading

- [GLM]
  - Used for linear math 

- [SOIL - Simple OpenGL Image Library](http://www.lonesock.net/soil.html)
  - Used for loading images

Authors
--------
Shuai Song
Wan-Ting Chang